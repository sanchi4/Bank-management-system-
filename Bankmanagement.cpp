//*******************************************************
//                  			 HEADER FILE USED IN PROJECT
//*******************************************************

#include<iostream>
#include<fstream>
#include<ctype.h>
#include<iomanip>
#include<conio.h>
#include<stdio.h>
using namespace std;
int k=0;
//************************************************************
//                                           CLASS USED IN PROJECT
//************************************************************

class account
{
    int acno;
	char name[50];
	int deposit;
	char type;
	char mob_no[10];
	public:
	void create_account(); //function to get data from user
	void show_account()const; //function to show data on screen
	void modify();  //function to add new data
	void dep(int); //function to accept amount and add to balance amount
    void draw(int);  //function to accept amount and subtract from balance      amount
	void report()const; //function to show data in tabular format
	int retacno()const; //function to return account number
	int retdeposit()const; //function to return balance amount
	char rettype()const; //function to return type of account
}; //class ends here

int flag=1;

void account::create_account()
{
	acno=++k;
	cout<<"\n\nEnter the name of the account holder : ";
	gets(name);
	gets(name);
	cout<<"\n\nEnter the mobile no. of the account holder : ";
	gets(mob_no);
	cout<<"\nEnter type of the account (C/S) : ";
	cin>>type;
	type=toupper(type);
    cout<<"\nEnter the initial amount(>=500 for Saving and >=1000 for        current) :";
	cin>>deposit;
	if((type=='C' && deposit>=1000)   || (type=='S' && deposit>=500))
	{
	flag=0;
	cout<<"\n\n\nAccount Created..";
	}
	else
	cout<<"account cannot be created....";
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nAccount Holder Mobile no. : "<<mob_no;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}

void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	gets(name);
	gets(name);
	cout<<"\nModify Account Holder Mobile no. : ";
	gets(mob_no);
}

void account::dep(int x)
{
	deposit+=x;
}


void account::draw(int x)
{
	deposit-=x;
}

void account::report() const
{
cout<<acno<<setw(10)<<" "<<name<<setw(10)<<"\t"<<mob_no<<setw(10)<<"\t"<<type<<setw(10)<<deposit<<endl;
}

int account::retacno()const
{
	return acno;
}

int account::retdeposit()const
{
	return deposit;
}

char account::rettype()const
{
	return type;
}

//***********************************************************
//                                  	FUNCTION TO WRITE IN FILE
//***********************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	if(flag==0)
	outFile.write((char *)&ac ,sizeof(account));
	outFile.close();
}

//************************************************************
//    	                          FUNCTION TO READ SPECIFIC RECORD FROM FILE
//************************************************************

void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! ";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
	while(inFile.read((char *)&ac,sizeof(account)))
	{
		if(ac.retacno()== n)
		{
			ac.show_account();
			flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist";
}

//************************************************************
//                                FUNCTION TO MODIFY RECORD OF FILE
//************************************************************

void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! ";
		return;
	}
	while(!File.eof() && found==0)
	{
		File.read((char *)&ac,sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write((char *)&ac,sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
		  }
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}

//************************************************************
//    	                                function to delete record of file
//************************************************************

void delete_account(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! ";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *)&ac,sizeof(account)))
	{
	    int a=ac.retacno();
	    if(a==n) flag=1;
		if(a!=n)
		{
			outFile.write((char *)&ac,sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	if(flag==0)
        cout<<"\n\n\tRecord not found !!";
    else
	cout<<"\n\n\tRecord Deleted ..";
}

//************************************************************
//    				function to display all accounts deposit list
//************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !!";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"===============================================================================\n";
	cout<<"A/c no.     NAME                MOBILE NO.            TYPE    BALANCE\n";
	cout<<"=============================================================================== \n";
	while(inFile.read((char *)&ac,sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//************************************************************
//   			 	function to deposit and withdraw amounts
//************************************************************

void deposit_withdraw(int n,int option)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !!";
		return;
	}

	while(!File.eof() && found==0)
	{
		File.read((char *)&ac,sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited : ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
			  cout<<"\n\n\tTO WITHDRAW AMOUNT ";
			  cout<<"\n\nEnter The amount to be withdraw : ";
			  cin>>amt;
			  int bal=ac.retdeposit()-amt;
if((bal<500 && ac.rettype()=='S')||(bal<1000 && (ac.rettype()=='C')))
			  cout<<"Insufficience balance";
			  else
			  ac.draw(amt);
			}
			int pos=(-1)*(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write((char *)&ac,sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
	       }
	 }
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}

//***********************************************************
//    				THE MAIN FUNCTION OF PROGRAM
//***********************************************************

int main()
{
	char ch;
	int num;

    cout<<"\n\n\t\t**** WELCOME   TO   S.D.J   INTERNATIONAL   BANK     ***** \n";
    cout<<"\n \n \t \t     ***** BANK      MANAGEMENT     SYSTEM *****\n";

    do
	{
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;

		switch(ch)
		{
		case '1':
			write_account();
			break;


		case '2':
			cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			deposit_withdraw(num, 1);
			break;

		case '3':
			cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			deposit_withdraw(num, 2);
			break;

		case '4':
			cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			display_sp(num);
			break;

		case '5':
			display_all();
			break;




case '6':
			cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			delete_account(num);
			break;

		case '7':
			cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			modify_account(num);
			break;

		case '8':
			cout<<"\n\n\tThanks for using bank management system !!!\n";
			break;

		default :cout<<"\ninvalid entry !!";
		}

	}while(ch!='8');
	return 0;
}

//************************************************************
//    							END OF PROJECT
//************************************************************

