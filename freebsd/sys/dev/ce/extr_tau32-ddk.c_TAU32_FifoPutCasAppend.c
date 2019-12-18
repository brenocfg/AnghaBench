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
struct TYPE_5__ {int SP4ZU; int /*<<< orphan*/  h2LrH3; TYPE_1__* oXafA1; } ;
typedef  TYPE_2__ kWMzp1 ;
struct TYPE_4__ {int /*<<< orphan*/ * KqthD; } ;

/* Variables and functions */
 int Ji6_v2 (int,int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  h2LrH3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uYS5N2 (int /*<<< orphan*/ *) ; 

int __attribute__((cdecl))TAU32_FifoPutCasAppend
(kWMzp1*J7Iki4,int b9Zs_,unsigned char*X3ca,unsigned IOwwG2){int
Kt5Iv1=-2;h2LrH3(&J7Iki4->h2LrH3);switch(b9Zs_){case 0:Kt5Iv1=Ji6_v2(
01u,&J7Iki4->oXafA1[0].KqthD[01u],X3ca,IOwwG2);break;case 1:{if(!(
J7Iki4->SP4ZU!=0x2))goto BjC5Z;Kt5Iv1=Ji6_v2(01u,&J7Iki4->oXafA1[01].
KqthD[01u],X3ca,IOwwG2);BjC5Z:;}break;case(-1):Kt5Iv1=Ji6_v2(0x1u,&
J7Iki4->oXafA1[0].KqthD[01u],X3ca,IOwwG2);{if(!(J7Iki4->SP4ZU!=2))goto
lJjph3;{int QEvwb3=Ji6_v2(0x1u,&J7Iki4->oXafA1[1].KqthD[01u],X3ca,
IOwwG2);{if(!(QEvwb3<Kt5Iv1))goto XMUNv1;Kt5Iv1=QEvwb3;XMUNv1:;}}
lJjph3:;}}uYS5N2(&J7Iki4->h2LrH3);return Kt5Iv1;}