/*************************************************************************
    > File Name: ls3.cpp
    > Author: zhangke
    > Mail: ch.zhangke@gmail.com 
    > Created Time: 2015年11月29日 星期日 22时39分34秒
 ************************************************************************/

#include<iostream>
#include<vector>
using std::vector;
using std::cin;
using std::cout;
using std::endl;
struct po
{
	int head;
	int tail;
	po(int a,int b)
	{
		head = a;
		tail = b;
	}
	void print()
	{
		cout<<"<"<<head<<", "<<tail<<">";
	}
};
void mod(vector<int> &a,int number);
void poset(vector<po> &a,vector<int> modresult,int size);
void cover(vector<po> &coverresult,vector<po> &a);
bool &patch(vector<int> modresult,int max,bool &patchornot);
int main()
{
	int number;
	cin>>number;
	vector<int> modresult;
	mod(modresult,number);
	int size=modresult.size();
	vector<po> posetresult;
	poset(posetresult,modresult,size);
	vector<po> coverresult;
	cover(coverresult,posetresult);
	for(vector<po>::iterator beg = coverresult.begin(); beg < coverresult.end(); ++beg)
	{
		(*beg).print();
		if(beg < coverresult.end()-1)
			cout<<",";
	}
	cout<<endl;
	bool patchornot;
	patchornot=patch(modresult,number,patchornot);
	if(patchornot)
		cout<<"是补格"<<endl;
	else
		cout<<"不是补格"<<endl;
	return 0;
}
void mod(vector<int> &a,int number)
{
	for(int i=1;i<=number;++i)
	{
		if(number%i==0)
			a.push_back(i);
	}
}
void poset(vector<po> &a,vector<int> modresult,int size)
{
	for(int i=0;i<size-1;++i)
	{
		for(int j=i+1;j<size;++j)
		{
			if(modresult[j]%modresult[i]==0)
			{
				po temp(modresult[i],modresult[j]);
				a.push_back(temp);
			}
		}
	}
}
void cover(vector<po> &coverresult,vector<po> &posetresult)
{
	for(vector<po>::iterator begpos=posetresult.begin();begpos<posetresult.end();++begpos)
	{
		int status=1;
		int headTemp = (*begpos).head;
		int tailTemp = (*begpos).tail;
		for(vector<po>::iterator begpos1=posetresult.begin();begpos1<posetresult.end();++begpos1)
		{
			if ((*begpos1).head == headTemp&&status)
			{
				for(vector<po>::iterator begpos2=begpos1;begpos2<posetresult.end();++begpos2)
				{
					if((*begpos2).tail == tailTemp)
					{
						if((*begpos1).tail == (*begpos2).head)
							status = 0;
					}
				}
			}
		}
		if(status)
			coverresult.push_back(*begpos);
	}
}
bool &patch(vector<int> modresult,int max,bool &patchornot)
{
	vector<int> status;
	for(vector<int>::iterator beg=modresult.begin();beg<modresult.end();++beg)
	{
		int sta=0;
		for(vector<int>::iterator beg1=modresult.begin();beg1<modresult.end();++beg1)
		{	
			int a,b;
			if(*beg>*beg1)
			{
				a=*beg;
				b=*beg1;
			}
			else
			{
				a=*beg1;
				b=*beg;
			}
			int temp = b;
			b = a%b;
			while(b)
			{
				a=temp;
				temp=b;
				b=a%b;
			}
			if(temp==1&&(*beg)*(*beg1)==max)
			{
				sta=1;
			}
			if(sta)
				break;
		}
		if(sta)
			status.push_back(1);
		else
			status.push_back(0);
	}
	 patchornot = true;
	for(vector<int>::iterator be=status.begin();be<status.end();++be)
		if(!(*be))
			patchornot = false;
	return patchornot;
}
/* 假设输入12,因子有1,2,3,4,6,12
 * 偏序关系有:
 * <1,2> <1,3> <1,4> <1,6> <1,12>
 * <2,4> <2,6> <2,12>
 * <3,6> <3,12>
 * <4,12>
 * <6,12>
 */
