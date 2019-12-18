#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 unsigned long long kD2ag4 (unsigned long,int) ; 

unsigned
long long __attribute__((cdecl))TAU32_ProbeGeneratorFrequency(
unsigned long long jYvNM3){unsigned long TrF875,V4Eg_2,yG5VL=0,Curt94
=(unsigned long)(jYvNM3>>32);{if(!(((int)Curt94)<=0))goto PY2k02;
Curt94=2048000;goto iJL0J;PY2k02:;{if(!(Curt94<2048000-0x1388))goto
fcI1o1;Curt94=2048000-0x1388;goto dEEsv;fcI1o1:;{if(!(Curt94>=2048000
+011610))goto pfvK;Curt94=2048000+011610;goto z7JL65;pfvK:;yG5VL=(
unsigned long)jYvNM3;z7JL65:;}dEEsv:;}iJL0J:;}jYvNM3=(((unsigned long
long)Curt94)<<32)+yG5VL;jYvNM3+=65536*0175/2;jYvNM3>>=16;__asm__(
"divl %3":"=a,a"(TrF875),"=d,d"(V4Eg_2):"A,A"(jYvNM3),"r,m"(0175):
"cc");return kD2ag4(TrF875,0175*65536);}