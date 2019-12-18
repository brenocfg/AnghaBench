#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int SP4ZU; unsigned char HtJEJ; int /*<<< orphan*/  h2LrH3; TYPE_1__* fV7o35; } ;
typedef  TYPE_2__ kWMzp1 ;
struct TYPE_9__ {unsigned int CCKdO2; unsigned int HZ1wC3; int /*<<< orphan*/  XmIKi3; } ;
struct TYPE_7__ {unsigned long UyRVB4; } ;
typedef  TYPE_3__ Drk7M4 ;

/* Variables and functions */
 int /*<<< orphan*/  AUUSL3 (unsigned long volatile*,int,unsigned char) ; 
 int /*<<< orphan*/  GLE_s4 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  h2LrH3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uYS5N2 (int /*<<< orphan*/ *) ; 

int __attribute__((
cdecl))TAU32_SetSaCross(kWMzp1*J7Iki4,Drk7M4 Uwhrn4){unsigned char
f2E883=0;{if(!(Uwhrn4.CCKdO2>04u||Uwhrn4.HZ1wC3>04u))goto scDVj2;
return 0;scDVj2:;}{if(!(!Uwhrn4.XmIKi3&&(Uwhrn4.CCKdO2==1u||Uwhrn4.
HZ1wC3==01u)))goto dS8884;return 0;dS8884:;}{if(!(J7Iki4->SP4ZU==0x2))goto
Ksejb1;{if(!(Uwhrn4.CCKdO2==3u||Uwhrn4.HZ1wC3!=0u))goto E8X83;return 0
;E8X83:;}Ksejb1:;}{if(!(Uwhrn4.XmIKi3))goto O1Tns4;f2E883|=64;O1Tns4:
;}{if(!(Uwhrn4.CCKdO2))goto rXxhw3;f2E883|=16|((Uwhrn4.CCKdO2-01)<<0);
rXxhw3:;}{if(!(Uwhrn4.HZ1wC3))goto nVDTK2;f2E883|=32|((Uwhrn4.HZ1wC3-
01)<<2);nVDTK2:;}{if(!(f2E883!=J7Iki4->HtJEJ))goto stLrO1;{volatile
unsigned long*RdZoN;h2LrH3(&J7Iki4->h2LrH3);RdZoN=&J7Iki4->fV7o35->
UyRVB4;AUUSL3(RdZoN,8,J7Iki4->HtJEJ=f2E883);GLE_s4(J7Iki4,(-0x1));
uYS5N2(&J7Iki4->h2LrH3);}stLrO1:;}return 1;}