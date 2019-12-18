#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int SP4ZU; unsigned char** jyElQ3; int /*<<< orphan*/  h2LrH3; } ;
typedef  TYPE_1__ kWMzp1 ;

/* Variables and functions */
 int /*<<< orphan*/  GLE_s4 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  h2LrH3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uYS5N2 (int /*<<< orphan*/ *) ; 

int __attribute__((cdecl))TAU32_UpdateIdleCodes
(kWMzp1*J7Iki4,int b9Zs_,unsigned long dJtvs,unsigned char RAwCl1){
int fRgzh2=0;int X3V8j4;{if(!((b9Zs_!=(-0x1)&&b9Zs_>1)||dJtvs==0))goto
ObnCM2;return 0;ObnCM2:;}{if(!(J7Iki4->SP4ZU==2&&b9Zs_>0))goto UiHem4
;return 0;UiHem4:;}h2LrH3(&J7Iki4->h2LrH3);X3V8j4=0;{Ssl144:{{if(!(
dJtvs&0x1))goto TpZ785;{{if(!(b9Zs_==(-1)||b9Zs_==0))goto j7vft;{if(!
(J7Iki4->jyElQ3[0][X3V8j4]!=RAwCl1))goto g1F5_1;{J7Iki4->jyElQ3[0][
X3V8j4]=RAwCl1;fRgzh2=01;}g1F5_1:;}j7vft:;}{if(!(J7Iki4->SP4ZU!=2))goto
pMVyr2;{if(!(b9Zs_==(-1)||b9Zs_==01))goto v8BDc2;{if(!(J7Iki4->jyElQ3
[01][X3V8j4]!=RAwCl1))goto a2mb94;{J7Iki4->jyElQ3[01][X3V8j4]=RAwCl1;
fRgzh2=0x1;}a2mb94:;}v8BDc2:;}pMVyr2:;}}TpZ785:;}++X3V8j4;}if((32==32
||X3V8j4<32)&&(dJtvs>>=0x1)!=0)goto Ssl144;};{if(!(fRgzh2))goto RguOm
;GLE_s4(J7Iki4,b9Zs_);RguOm:;}uYS5N2(&J7Iki4->h2LrH3);return 1;}