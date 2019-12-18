#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {unsigned long* iO1iw4; int /*<<< orphan*/  h2LrH3; TYPE_9__* YRHFy; TYPE_4__* oXafA1; TYPE_2__* v6D2d3; TYPE_6__*** hRUi43; TYPE_1__* fV7o35; } ;
typedef  TYPE_5__ kWMzp1 ;
struct TYPE_18__ {unsigned char* BC6Zd3; int fVNme; int ELKAp3; int /*<<< orphan*/ * PnawH; } ;
typedef  TYPE_6__ iOPn3 ;
struct TYPE_19__ {int /*<<< orphan*/  (* yjdp7 ) (TYPE_9__*,int,unsigned int) ;TYPE_3__* io7IZ3; } ;
struct TYPE_16__ {unsigned int H4ghS2; } ;
struct TYPE_15__ {int smyqr; unsigned int QV1Pb3; unsigned int mZSLK1; unsigned int zwLFt3; unsigned int H4ghS2; int /*<<< orphan*/  lpVV64; int /*<<< orphan*/  ounCU4; int /*<<< orphan*/  _xj3V4; } ;
struct TYPE_14__ {unsigned int jf4g9; unsigned int* FNU7M3; unsigned int Q1iXV3; unsigned int DvwSz1; } ;
struct TYPE_13__ {unsigned long UyRVB4; } ;

/* Variables and functions */
 int /*<<< orphan*/  BucKo (unsigned long volatile*,int,unsigned int) ; 
 int /*<<< orphan*/  GLE_s4 (TYPE_5__*,int) ; 
 unsigned int NHDsK3 (unsigned long volatile*,int) ; 
 unsigned int SlE234 (unsigned long volatile*,int) ; 
 unsigned int dMM0e1 (unsigned long volatile*,int) ; 
 unsigned int fFvjz3 (unsigned long volatile*,int) ; 
 int /*<<< orphan*/  h2LrH3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s3sCI1 (unsigned long volatile*,int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*,int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (TYPE_9__*,int,unsigned int) ; 
 int /*<<< orphan*/  uYS5N2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vUYb92 (int,int,TYPE_6__*,TYPE_5__*,int) ; 

__attribute__((used)) static void Pp5_4(kWMzp1*J7Iki4){{unsigned kUguy3,H4ghS2=0;{if(!(
J7Iki4->iO1iw4[0]))goto l5kPU2;{volatile unsigned long*RdZoN;unsigned
ADRH25,rT0fp2,wk4VW,Hdw702;RdZoN=&J7Iki4->fV7o35->UyRVB4;ADRH25=
dMM0e1(RdZoN,0x8);{if(!(ADRH25&32))goto Ex2aA2;H4ghS2|=8192u;Ex2aA2:;
}rT0fp2=SlE234(RdZoN,036);wk4VW=dMM0e1(RdZoN,0x6);{if(!(wk4VW&0x8))goto
zC34g4;H4ghS2|=04u;goto KelN_4;zC34g4:;{{if(!((J7Iki4->iO1iw4[0]&
0360ul)>(0x5ul<<0x4)))goto XQClD;{{if(!((rT0fp2&0x4)))goto TPDls1;
H4ghS2|=1024u;TPDls1:;}{if(!(wk4VW&4))goto JTU4E;H4ghS2|=0x8u;JTU4E:;
}{if(!(wk4VW&01))goto u7xdA3;H4ghS2|=02u;u7xdA3:;}{if(!((J7Iki4->
iO1iw4[0]&0360ul)>(0x6ul<<0x4)))goto qhKq6;{{if(!((rT0fp2&0x2)))goto
CRbKo2;H4ghS2|=4096u;CRbKo2:;}{if(!(wk4VW&64))goto NSe7w;H4ghS2|=64u;
NSe7w:;}switch(wk4VW&(128|32)){case 128:H4ghS2|=16u;break;case 32:
H4ghS2|=32u;break;default:wk4VW&=~(128|32);}}qhKq6:;}{if(!(J7Iki4->
iO1iw4[0]&268435456ul))goto paxXI3;{{if(!(rT0fp2>>04>=015))goto xHgra
;H4ghS2|=16384u;xHgra:;}{if(!((rT0fp2&01)))goto LlIil1;H4ghS2|=2048u;
LlIil1:;}}paxXI3:;}}XQClD:;}{if(!(wk4VW&0x2))goto fm_hx3;H4ghS2|=1u;
fm_hx3:;}}KelN_4:;}{if(!(0x1&&(wk4VW&16)))goto vj2bt2;{H4ghS2|=256u;
J7Iki4->YRHFy->io7IZ3[0]._xj3V4++;}vj2bt2:;}Hdw702=dMM0e1(RdZoN,0x7);
{if(!(Hdw702&4))goto Oi41C4;H4ghS2|=128u;Oi41C4:;}{if(!(J7Iki4->
iO1iw4[0]&65536ul))goto nkDDY;{{if(!(Hdw702&64))goto Qk17R1;{iOPn3*
xb5nq1=J7Iki4->hRUi43[0][0x2u];xb5nq1->BC6Zd3[xb5nq1->fVNme%256]=(
unsigned char)SlE234(RdZoN,31);{if(!((xb5nq1->fVNme-xb5nq1->ELKAp3)%
256>=256-01))goto FWoEJ2;{xb5nq1->PnawH[0]++;xb5nq1->ELKAp3++;}FWoEJ2
:;}xb5nq1->fVNme++;vUYb92(02u,512,xb5nq1,J7Iki4,0);}Qk17R1:;}{if(!(
Hdw702&010))goto AooXh2;{iOPn3*xb5nq1=J7Iki4->hRUi43[0][3u];{if(!((
xb5nq1->fVNme-xb5nq1->ELKAp3)%256>=0x1))goto xliFy2;{unsigned zQ6M_2=
xb5nq1->BC6Zd3[xb5nq1->ELKAp3%256];BucKo(RdZoN,041,J7Iki4->v6D2d3[0].
jf4g9=(unsigned char)(zQ6M_2|64));xb5nq1->ELKAp3++;}goto N0cAE4;
xliFy2:;xb5nq1->PnawH[0]++;N0cAE4:;}vUYb92(0x3u,512,xb5nq1,J7Iki4,0);
}AooXh2:;}}goto Ytnfz2;nkDDY:;{if(!(J7Iki4->iO1iw4[0]&131072ul))goto
pZwR;{{if(!(Hdw702&02))goto qhPRk4;{int X3V8j4;iOPn3*xb5nq1=J7Iki4->
hRUi43[0][02u];X3V8j4=07;{kB1KA:xb5nq1->BC6Zd3[(xb5nq1->fVNme+X3V8j4)%
256]=(unsigned char)SlE234(RdZoN,0130+X3V8j4);if(--X3V8j4>=0)goto
kB1KA;};{if(!((xb5nq1->fVNme-xb5nq1->ELKAp3)%256>=256-0x8))goto ak4S94
;{xb5nq1->PnawH[0]++;xb5nq1->ELKAp3+=8;}ak4S94:;}xb5nq1->fVNme+=0x8;
vUYb92(0x2u,4096,xb5nq1,J7Iki4,0);}qhPRk4:;}{if(!(Hdw702&32))goto
D2VDT2;{iOPn3*xb5nq1=J7Iki4->hRUi43[0][0x3u];{if(!((xb5nq1->fVNme-
xb5nq1->ELKAp3)%256>=8))goto xZ7sX;{int X3V8j4=7;{jughc:BucKo(RdZoN,
0120+X3V8j4,xb5nq1->BC6Zd3[(xb5nq1->ELKAp3+X3V8j4)%256]);if(--X3V8j4
>=0)goto jughc;};xb5nq1->ELKAp3+=0x8;}goto vGGMc2;xZ7sX:;xb5nq1->
PnawH[0]++;vGGMc2:;}vUYb92(0x3u,4096,xb5nq1,J7Iki4,0);}D2VDT2:;}}pZwR
:;}Ytnfz2:;}{if(!(J7Iki4->iO1iw4[0]&32768ul))goto NUiYy1;{{if(!(
Hdw702&128))goto SgaJH4;{int X3V8j4;iOPn3*xb5nq1=J7Iki4->hRUi43[0][0u
];X3V8j4=017;{wY1aR:xb5nq1->BC6Zd3[(xb5nq1->fVNme+X3V8j4)%256]=(
unsigned char)SlE234(RdZoN,48+X3V8j4);if(--X3V8j4>=0)goto wY1aR;};{if
(!((xb5nq1->fVNme-xb5nq1->ELKAp3)%256>=256-16))goto if4tC3;{xb5nq1->
PnawH[0]++;xb5nq1->ELKAp3+=16;}if4tC3:;}xb5nq1->fVNme+=16;vUYb92(0u,
4096,xb5nq1,J7Iki4,0);}SgaJH4:;}{if(!(Hdw702&32))goto W5FZB2;{iOPn3*
xb5nq1=J7Iki4->hRUi43[0][0x1u];{if(!((xb5nq1->fVNme-xb5nq1->ELKAp3)%
256>=16))goto qC85k4;{int X3V8j4=15;{Ov6y41:BucKo(RdZoN,64+X3V8j4,
J7Iki4->v6D2d3[0].FNU7M3[X3V8j4]=xb5nq1->BC6Zd3[(xb5nq1->ELKAp3+
X3V8j4)%256]);if(--X3V8j4>=0)goto Ov6y41;};xb5nq1->ELKAp3+=16;}goto
o1L6S1;qC85k4:;xb5nq1->PnawH[0]++;o1L6S1:;}vUYb92(1u,4096,xb5nq1,
J7Iki4,0);}W5FZB2:;}}NUiYy1:;}{if(!(0&&(Hdw702&1)))goto Nufn25;{
H4ghS2|=512u;J7Iki4->YRHFy->io7IZ3[0].ounCU4++;}Nufn25:;}BucKo(RdZoN,
0x16,J7Iki4->v6D2d3[0].Q1iXV3&~(01?wk4VW&~16:wk4VW));BucKo(RdZoN,0x17
,J7Iki4->v6D2d3[0].DvwSz1&~(Hdw702&4));{if(!(Hdw702&16))goto sSbPo1;{
J7Iki4->YRHFy->io7IZ3[0].smyqr+=(SlE234(RdZoN,0)<<010)+SlE234(RdZoN,
0x1);{if(!((J7Iki4->iO1iw4[0]&0360ul)>(5ul<<4)))goto zKRWY3;{unsigned
rx55l1,tYsSE2;rx55l1=SlE234(RdZoN,02);{if(!(J7Iki4->iO1iw4[0]&
268435456ul))goto lZCyu2;J7Iki4->YRHFy->io7IZ3[0].QV1Pb3+=((rx55l1&03
)<<010)+SlE234(RdZoN,03);lZCyu2:;}tYsSE2=SlE234(RdZoN,4);{if(!(J7Iki4
->iO1iw4[0]&(268435456ul|134217728ul)))goto Gl7nf;J7Iki4->YRHFy->
io7IZ3[0].mZSLK1+=((tYsSE2&3)<<010)+SlE234(RdZoN,5);Gl7nf:;}J7Iki4->
YRHFy->io7IZ3[0].zwLFt3+=(tYsSE2>>2)+((rx55l1&~03)<<6);}zKRWY3:;}
J7Iki4->YRHFy->io7IZ3[0].lpVV64++;}sSbPo1:;}}goto QptoN3;l5kPU2:;
H4ghS2=32768u;QptoN3:;}kUguy3=H4ghS2^J7Iki4->oXafA1[0].H4ghS2;{if(!(
kUguy3))goto uRG2Q2;{J7Iki4->YRHFy->io7IZ3[0].H4ghS2=J7Iki4->oXafA1[0
].H4ghS2=H4ghS2;GLE_s4(J7Iki4,0);{if(!(J7Iki4->YRHFy->yjdp7))goto
PwiOJ;{uYS5N2(&J7Iki4->h2LrH3);J7Iki4->YRHFy->yjdp7(J7Iki4->YRHFy,0,
kUguy3);h2LrH3(&J7Iki4->h2LrH3);}PwiOJ:;}}uRG2Q2:;}};{unsigned kUguy3
,H4ghS2=0;{if(!(J7Iki4->iO1iw4[01]))goto wyazp4;{volatile unsigned
long*RdZoN;unsigned ADRH25,rT0fp2,wk4VW,Hdw702;RdZoN=&J7Iki4->fV7o35
->UyRVB4;ADRH25=NHDsK3(RdZoN,010);{if(!(ADRH25&32))goto ojbR01;H4ghS2
|=8192u;ojbR01:;}rT0fp2=fFvjz3(RdZoN,0x1e);wk4VW=NHDsK3(RdZoN,0x6);{
if(!(wk4VW&0x8))goto K7Qbq4;H4ghS2|=0x4u;goto rsP7X2;K7Qbq4:;{{if(!((
J7Iki4->iO1iw4[01]&240ul)>(05ul<<4)))goto q8PSF2;{{if(!((rT0fp2&0x4)))goto
yQbCz;H4ghS2|=1024u;yQbCz:;}{if(!(wk4VW&04))goto qDbQb3;H4ghS2|=010u;
qDbQb3:;}{if(!(wk4VW&1))goto J4NyB2;H4ghS2|=02u;J4NyB2:;}{if(!((
J7Iki4->iO1iw4[0x1]&0360ul)>(6ul<<4)))goto WvRg31;{{if(!((rT0fp2&2)))goto
PXdWr4;H4ghS2|=4096u;PXdWr4:;}{if(!(wk4VW&64))goto X04Ko3;H4ghS2|=64u
;X04Ko3:;}switch(wk4VW&(128|32)){case 128:H4ghS2|=16u;break;case 32:
H4ghS2|=32u;break;default:wk4VW&=~(128|32);}}WvRg31:;}{if(!(J7Iki4->
iO1iw4[01]&268435456ul))goto eoj0m1;{{if(!(rT0fp2>>04>=015))goto
oOqXI4;H4ghS2|=16384u;oOqXI4:;}{if(!((rT0fp2&0x1)))goto qeXeK;H4ghS2
|=2048u;qeXeK:;}}eoj0m1:;}}q8PSF2:;}{if(!(wk4VW&02))goto fZpYx3;
H4ghS2|=1u;fZpYx3:;}}rsP7X2:;}{if(!(1&&(wk4VW&16)))goto v3xAt2;{
H4ghS2|=256u;J7Iki4->YRHFy->io7IZ3[0x1]._xj3V4++;}v3xAt2:;}Hdw702=
NHDsK3(RdZoN,7);{if(!(Hdw702&4))goto Nubfw;H4ghS2|=128u;Nubfw:;}{if(!
(J7Iki4->iO1iw4[0x1]&65536ul))goto kIw4A;{{if(!(Hdw702&64))goto hMOtf2
;{iOPn3*xb5nq1=J7Iki4->hRUi43[1][02u];xb5nq1->BC6Zd3[xb5nq1->fVNme%
256]=(unsigned char)fFvjz3(RdZoN,31);{if(!((xb5nq1->fVNme-xb5nq1->
ELKAp3)%256>=256-0x1))goto n9RMY;{xb5nq1->PnawH[0]++;xb5nq1->ELKAp3++
;}n9RMY:;}xb5nq1->fVNme++;vUYb92(2u,512,xb5nq1,J7Iki4,01);}hMOtf2:;}{
if(!(Hdw702&010))goto UzdZm4;{iOPn3*xb5nq1=J7Iki4->hRUi43[1][03u];{if
(!((xb5nq1->fVNme-xb5nq1->ELKAp3)%256>=1))goto VA7c_2;{unsigned zQ6M_2
=xb5nq1->BC6Zd3[xb5nq1->ELKAp3%256];s3sCI1(RdZoN,0x21,J7Iki4->v6D2d3[
1].jf4g9=(unsigned char)(zQ6M_2|64));xb5nq1->ELKAp3++;}goto _5jq61;
VA7c_2:;xb5nq1->PnawH[0]++;_5jq61:;}vUYb92(0x3u,512,xb5nq1,J7Iki4,1);
}UzdZm4:;}}goto OO3a03;kIw4A:;{if(!(J7Iki4->iO1iw4[0x1]&131072ul))goto
NJK9y1;{{if(!(Hdw702&2))goto pXz9V1;{int X3V8j4;iOPn3*xb5nq1=J7Iki4->
hRUi43[01][02u];X3V8j4=07;{C3bNb:xb5nq1->BC6Zd3[(xb5nq1->fVNme+X3V8j4
)%256]=(unsigned char)fFvjz3(RdZoN,0130+X3V8j4);if(--X3V8j4>=0)goto
C3bNb;};{if(!((xb5nq1->fVNme-xb5nq1->ELKAp3)%256>=256-010))goto ds3jz4
;{xb5nq1->PnawH[0]++;xb5nq1->ELKAp3+=010;}ds3jz4:;}xb5nq1->fVNme+=0x8
;vUYb92(2u,4096,xb5nq1,J7Iki4,1);}pXz9V1:;}{if(!(Hdw702&32))goto
nFUGf1;{iOPn3*xb5nq1=J7Iki4->hRUi43[1][0x3u];{if(!((xb5nq1->fVNme-
xb5nq1->ELKAp3)%256>=8))goto xAdT74;{int X3V8j4=7;{AxBoj2:s3sCI1(
RdZoN,0120+X3V8j4,xb5nq1->BC6Zd3[(xb5nq1->ELKAp3+X3V8j4)%256]);if(--
X3V8j4>=0)goto AxBoj2;};xb5nq1->ELKAp3+=0x8;}goto NeqBE4;xAdT74:;
xb5nq1->PnawH[0]++;NeqBE4:;}vUYb92(0x3u,4096,xb5nq1,J7Iki4,0x1);}
nFUGf1:;}}NJK9y1:;}OO3a03:;}{if(!(J7Iki4->iO1iw4[0x1]&32768ul))goto
_lCoK1;{{if(!(Hdw702&128))goto n_AjF4;{int X3V8j4;iOPn3*xb5nq1=J7Iki4
->hRUi43[0x1][0u];X3V8j4=15;{IYF8d1:xb5nq1->BC6Zd3[(xb5nq1->fVNme+
X3V8j4)%256]=(unsigned char)fFvjz3(RdZoN,48+X3V8j4);if(--X3V8j4>=0)goto
IYF8d1;};{if(!((xb5nq1->fVNme-xb5nq1->ELKAp3)%256>=256-16))goto PXvj5
;{xb5nq1->PnawH[0]++;xb5nq1->ELKAp3+=16;}PXvj5:;}xb5nq1->fVNme+=16;
vUYb92(0u,4096,xb5nq1,J7Iki4,0x1);}n_AjF4:;}{if(!(Hdw702&32))goto
EHOiM1;{iOPn3*xb5nq1=J7Iki4->hRUi43[1][1u];{if(!((xb5nq1->fVNme-
xb5nq1->ELKAp3)%256>=16))goto Zh7nv2;{int X3V8j4=15;{oOE2W:s3sCI1(
RdZoN,64+X3V8j4,J7Iki4->v6D2d3[1].FNU7M3[X3V8j4]=xb5nq1->BC6Zd3[(
xb5nq1->ELKAp3+X3V8j4)%256]);if(--X3V8j4>=0)goto oOE2W;};xb5nq1->
ELKAp3+=16;}goto KSS8F;Zh7nv2:;xb5nq1->PnawH[0]++;KSS8F:;}vUYb92(0x1u
,4096,xb5nq1,J7Iki4,01);}EHOiM1:;}}_lCoK1:;}{if(!(0&&(Hdw702&01)))goto
__FnD3;{H4ghS2|=512u;J7Iki4->YRHFy->io7IZ3[0x1].ounCU4++;}__FnD3:;}
s3sCI1(RdZoN,026,J7Iki4->v6D2d3[0x1].Q1iXV3&~(0x1?wk4VW&~16:wk4VW));
s3sCI1(RdZoN,23,J7Iki4->v6D2d3[1].DvwSz1&~(Hdw702&4));{if(!(Hdw702&16
))goto B_9IY2;{J7Iki4->YRHFy->io7IZ3[0x1].smyqr+=(fFvjz3(RdZoN,0)<<8)+
fFvjz3(RdZoN,0x1);{if(!((J7Iki4->iO1iw4[1]&240ul)>(5ul<<4)))goto
gbJeJ4;{unsigned rx55l1,tYsSE2;rx55l1=fFvjz3(RdZoN,2);{if(!(J7Iki4->
iO1iw4[0x1]&268435456ul))goto bgpE63;J7Iki4->YRHFy->io7IZ3[1].QV1Pb3
+=((rx55l1&0x3)<<8)+fFvjz3(RdZoN,3);bgpE63:;}tYsSE2=fFvjz3(RdZoN,4);{
if(!(J7Iki4->iO1iw4[0x1]&(268435456ul|134217728ul)))goto kixrg4;
J7Iki4->YRHFy->io7IZ3[0x1].mZSLK1+=((tYsSE2&03)<<010)+fFvjz3(RdZoN,05
);kixrg4:;}J7Iki4->YRHFy->io7IZ3[1].zwLFt3+=(tYsSE2>>0x2)+((rx55l1&~
0x3)<<6);}gbJeJ4:;}J7Iki4->YRHFy->io7IZ3[0x1].lpVV64++;}B_9IY2:;}}
goto DpY605;wyazp4:;H4ghS2=32768u;DpY605:;}kUguy3=H4ghS2^J7Iki4->
oXafA1[0x1].H4ghS2;{if(!(kUguy3))goto dWbRI2;{J7Iki4->YRHFy->io7IZ3[1
].H4ghS2=J7Iki4->oXafA1[0x1].H4ghS2=H4ghS2;GLE_s4(J7Iki4,01);{if(!(
J7Iki4->YRHFy->yjdp7))goto meOKL1;{uYS5N2(&J7Iki4->h2LrH3);J7Iki4->
YRHFy->yjdp7(J7Iki4->YRHFy,0x1,kUguy3);h2LrH3(&J7Iki4->h2LrH3);}
meOKL1:;}}dWbRI2:;}};}