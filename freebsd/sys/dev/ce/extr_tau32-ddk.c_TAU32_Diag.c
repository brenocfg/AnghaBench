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
struct TYPE_5__ {unsigned long GEt0d; int /*<<< orphan*/  h2LrH3; TYPE_1__* fV7o35; } ;
typedef  TYPE_2__ kWMzp1 ;
struct TYPE_4__ {unsigned long UyRVB4; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUUSL3 (unsigned long volatile*,int,unsigned long) ; 
 int /*<<< orphan*/  LzuvP2 (unsigned long volatile*,unsigned long) ; 
 int RtiEy4 (unsigned long volatile*,int) ; 
 int /*<<< orphan*/  h2LrH3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uYS5N2 (int /*<<< orphan*/ *) ; 

unsigned long __attribute__((cdecl))TAU32_Diag
(kWMzp1*J7Iki4,unsigned Smebz2,unsigned long a0Zcs){volatile unsigned
long*RdZoN;unsigned long qwUGv3=0;h2LrH3(&J7Iki4->h2LrH3);RdZoN=&
J7Iki4->fV7o35->UyRVB4;switch(Smebz2){case 01:((RdZoN)[-1])=0;((RdZoN
)[0])=0xFFFF;((RdZoN)[-1])=224;((RdZoN)[-01])=0;case 0:qwUGv3=(((
RdZoN)[0])&0xFFFF)|(((RdZoN)[-0x1])<<16);break;case 02:((RdZoN)[-1])=
a0Zcs>>16;((RdZoN)[0])=a0Zcs&0xFFFF;qwUGv3=((RdZoN)[0]);break;case 0x3
:((RdZoN)[0])=a0Zcs&0xFFFF;((RdZoN)[-1])=a0Zcs>>16;qwUGv3=((RdZoN)[0]
);break;case 0x5:AUUSL3(RdZoN,(a0Zcs>>16)&0xFF,(a0Zcs>>0x8)&0xFF);
break;case 0x6:AUUSL3(RdZoN,(a0Zcs>>16)&0xFF,(a0Zcs>>8)&0xFF);case 04
:qwUGv3=RtiEy4(RdZoN,(a0Zcs>>16)&0xFF)<<010;break;case 0x7:AUUSL3(
RdZoN,(a0Zcs>>16)&0xFF,(a0Zcs>>8)&0xFF);qwUGv3=RtiEy4(RdZoN,0x5);
break;case 010:AUUSL3(RdZoN,(a0Zcs>>16)&0xFF,(a0Zcs>>8)&0xFF);AUUSL3(
RdZoN,0x5,a0Zcs&0xFF);break;case 011:AUUSL3(RdZoN,(a0Zcs>>16)&0xFF,(
a0Zcs>>010)&0xFF);qwUGv3=RtiEy4(RdZoN,05);AUUSL3(RdZoN,(a0Zcs>>16)&
0xFF,(a0Zcs>>0x8)&0xFF);AUUSL3(RdZoN,0x5,a0Zcs&0xFF);break;case 012:
AUUSL3(RdZoN,(a0Zcs>>16)&0xFF,(a0Zcs>>8)&0xFF);AUUSL3(RdZoN,0x5,a0Zcs
&0xFF);AUUSL3(RdZoN,(a0Zcs>>16)&0xFF,(a0Zcs>>0x8)&0xFF);qwUGv3=RtiEy4
(RdZoN,05);break;case 013:AUUSL3(RdZoN,(a0Zcs>>16)&0xFF,(a0Zcs>>8)&
0xFF);AUUSL3(RdZoN,5,a0Zcs&0xFF);AUUSL3(RdZoN,(a0Zcs>>16)&0xFF,(a0Zcs
>>0x8)&0xFF);qwUGv3=RtiEy4(RdZoN,5);AUUSL3(RdZoN,(a0Zcs>>16)&0xFF,(
a0Zcs>>0x8)&0xFF);AUUSL3(RdZoN,05,qwUGv3&a0Zcs&0xFF);break;case 014:{
if(!(a0Zcs>2097151999ul))goto bZsbt1;qwUGv3=~0ul;goto NQD_Y1;bZsbt1:;
{unsigned long T8Tg75=a0Zcs;__asm __volatile("mul %2;"
"add $2147483648, %0;" "adc $0, %1":"=a"(T8Tg75),"=d"(qwUGv3):"r"(
01422335136ul),"0"(T8Tg75));qwUGv3+=a0Zcs+a0Zcs;}NQD_Y1:;}LzuvP2(
RdZoN,qwUGv3);AUUSL3(RdZoN,0,J7Iki4->GEt0d=(J7Iki4->GEt0d&~043)|32);
break;}uYS5N2(&J7Iki4->h2LrH3);return qwUGv3;}