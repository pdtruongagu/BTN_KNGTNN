#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include<stdlib.h>
#include <iomanip>
#include <iostream>
using namespace  std;

#define MAX_TEN		50
#define MAX_MASO	10
#define LCB     1150000

//Class Nhanvien
class NhanVien
{	protected: //private:
		char HoTen[MAX_TEN];
		char MaSo[MAX_MASO];
		float Luong;
	public:
		NhanVien();
		virtual void TinhLuong()=0; 
		void Xuat(); 
		virtual void Nhap();
		float getLuong();
};

//Class Bien che
class BienChe: public NhanVien
{	protected: //private:
		float HeSoLuong;
		float HeSoPhuCap;
	public:
		BienChe();
		void TinhLuong();
		void Nhap();
};

class HopDong : public NhanVien
{	protected: //private:
		float TienCong; // 1 ngay
		float NgayCong; // lon hon 24 ngay thi tinh 1.2
	public:
		HopDong();
		void TinhLuong();
};

int main()
{
	NhanVien *Nv[100];	int N=0;
	char Chon,Loai;
	cout<<"Nhap thong tin cho cac Nhan vien"<<endl;
	do
	{	cout<<"Bien che hay Hop dong (B/H)? ";
		cin>>Loai; 	Loai=toupper(Loai);
		if (Loai=='B')
			Nv[N]=new BienChe;
		else
			Nv[N]=new HopDong;
		Nv[N++]->Nhap();
		cout<<"Tiep tuc (C/K)? ";	cin>>Chon;
		Chon=toupper(Chon);
		if ((N==100)||(Chon=='K'))
			break;
	}
	while (1);
	//Xuat
	for(int i=0; i<N; i++)
	{
		cout<<"Thong tin cua nhan vien thu "<<i+1<<": ";
			Nv[i]->TinhLuong();
			Nv[i]->Xuat();
	}
	
	//Tongluong
	float tongluong=0;
	for(int i=0; i<N; i++)
	{
		Nv[i]->TinhLuong();
		tongluong+=Nv[i]->getLuong();
	}
	cout<<"\nTong luong cac nhan vien: "<<tongluong;
	
	//TBCLuong
	float tbcluong=0;
	for(int i=0; i<N; i++)
	{
		Nv[i]->TinhLuong();
		tbcluong+=Nv[i]->getLuong();
	}
	tbcluong/=N;
	cout<<"\nTBC luong cac nhan vien: "<<tbcluong;
	
	//Liet ke luong lon hon 5tr
	cout<<"\nNhung nhan vien co luong > 5tr: ";
	for(int i=0; i<N; i++)
	{
		Nv[i]->TinhLuong();
		if(Nv[i]->getLuong() > 5e+006)
			Nv[i]->Xuat();
	}
	
	getch();
	return 1;
}

//Dinh nghia ham thanh vien cho lop NhanVien
NhanVien::NhanVien()
{
	strcpy(HoTen,""); 
	strcpy(MaSo,"");
	Luong=0;
}

float NhanVien::getLuong()
{
	return Luong;
}

void NhanVien::Nhap()
{
	cout<<"Ma so:";	cin>>MaSo;
	cin.ignore(); //xoa dau Enter trong buffer
	cout<<"Ho va ten:"; 
	cin.getline(HoTen,MAX_TEN);
	//cin>>HoTen;
}

void NhanVien::Xuat() 
{	//setiosflags(ios::fixed)<<setprecision(2);
	cout<<"Ma so:"<<MaSo<<",Ho va ten:"<<HoTen
		 <<",Luong:"<<Luong<<endl;
}

//Cac ham thanh vien trong lop BienChe
BienChe::BienChe()
{
	HeSoLuong=HeSoPhuCap=0;
}

void BienChe::Nhap()
{	
	NhanVien::Nhap();
	cout<<"He so luong: "; cin>>HeSoLuong;
	cout<<"He so phu cap: "; cin>>HeSoPhuCap;
}

void BienChe::TinhLuong()
{
	Luong=LCB*(HeSoLuong+HeSoPhuCap);
}

//Cac ham thanh vien trong lop HopDong
HopDong::HopDong()
{
	TienCong=NgayCong=0;
}

void HopDong::Nhap()
{
	NhanVien::Nhap();
	cout<<"Tien cong: "; cin>>TienCong;
	cout<<"Ngay cong: "; cin>>NgayCong;
}

void HopDong::TinhLuong()
{
	if(NgayCong<24)
		Luong=TienCong*NgayCong;
	else
		Luong=TienCong*1.2*(NgayCong-24);
}
