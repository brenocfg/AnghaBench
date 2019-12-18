#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long hBew43; int /*<<< orphan*/  h2LrH3; TYPE_1__* fV7o35; } ;
typedef  TYPE_2__ kWMzp1 ;
struct TYPE_4__ {unsigned long UyRVB4; } ;

/* Variables and functions */
 int /*<<< orphan*/  LzuvP2 (unsigned long volatile*,unsigned long) ; 
 int /*<<< orphan*/  h2LrH3 (int /*<<< orphan*/ *) ; 
 unsigned long long kD2ag4 (unsigned long,int) ; 
 int /*<<< orphan*/  uYS5N2 (int /*<<< orphan*/ *) ; 

unsigned long long
__attribute__((cdecl))TAU32_SetGeneratorFrequency(kWMzp1*J7Iki4,
unsigned long long jYvNM3){volatile unsigned long*RdZoN;unsigned long
TrF875;unsigned long V4Eg_2,Curt94=(unsigned long)(jYvNM3>>32);{if(!(
((int)Curt94)<=0))goto ajFIr1;goto ejnKl2;goto bSFnY1;ajFIr1:;{if(!(
Curt94<2048000-011610))goto UVOU33;goto kIGV65;goto LHp0y4;UVOU33:;{
if(!(Curt94>=2048000+011610))goto MT7_U;goto uuBga4;MT7_U:;}LHp0y4:;}
bSFnY1:;}mcEID3:jYvNM3+=65536*0175/02;jYvNM3>>=16;__asm__("divl %3":
"=a,a"(TrF875),"=d,d"(V4Eg_2):"A,A"(jYvNM3),"r,m"(0175):"cc");h2LrH3
(&J7Iki4->h2LrH3);{if(!(J7Iki4->hBew43!=TrF875))goto Vs72l;{J7Iki4->
hBew43=TrF875;RdZoN=&J7Iki4->fV7o35->UyRVB4;LzuvP2(RdZoN,TrF875);}
Vs72l:;}uYS5N2(&J7Iki4->h2LrH3);return kD2ag4(TrF875,125*65536);
ejnKl2:jYvNM3=((unsigned long long)2048000ul)<<32;goto mcEID3;kIGV65:
jYvNM3=((unsigned long long)2048000ul-011610)<<32;goto mcEID3;uuBga4:
jYvNM3=((unsigned long long)2048000ul+011610)<<32;goto mcEID3;}