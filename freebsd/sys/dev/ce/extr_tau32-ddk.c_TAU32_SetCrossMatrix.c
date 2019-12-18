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
struct TYPE_8__ {int SP4ZU; int jfimS4; int /*<<< orphan*/  h2LrH3; TYPE_3__* YRHFy; TYPE_1__* fV7o35; int /*<<< orphan*/  xOYSq1; int /*<<< orphan*/  veMrO; } ;
typedef  TYPE_2__ kWMzp1 ;
struct TYPE_9__ {unsigned int jfimS4; int /*<<< orphan*/  (* yjdp7 ) (TYPE_3__*,int,unsigned int) ;} ;
struct TYPE_7__ {unsigned long UyRVB4; } ;

/* Variables and functions */
 int /*<<< orphan*/  DhumT2 (TYPE_2__*,unsigned long volatile*,int) ; 
 int /*<<< orphan*/  L37Zk1 (int,unsigned char*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2LrH3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int,unsigned int) ; 
 int /*<<< orphan*/  uYS5N2 (int /*<<< orphan*/ *) ; 

int __attribute__((cdecl))TAU32_SetCrossMatrix
(kWMzp1*J7Iki4,unsigned char*eCQDF,unsigned long m45Hf){int aKuBh3;
h2LrH3(&J7Iki4->h2LrH3);aKuBh3=96;{if(!(J7Iki4->SP4ZU==02))goto YTCT72
;aKuBh3-=32;YTCT72:;}{if(!(L37Zk1(aKuBh3,eCQDF,m45Hf,J7Iki4->veMrO,
J7Iki4->xOYSq1)))goto YJ3xz2;{volatile unsigned long*RdZoN;RdZoN=&
J7Iki4->fV7o35->UyRVB4;{if(!(J7Iki4->jfimS4&0x4u))goto lKr7C;{{if(!(!
(J7Iki4->jfimS4&0x2u)))goto xaiXa;{J7Iki4->YRHFy->jfimS4=J7Iki4->
jfimS4|=02u;{if(!(J7Iki4->YRHFy->yjdp7))goto ZBFlD1;{uYS5N2(&J7Iki4->
h2LrH3);J7Iki4->YRHFy->yjdp7(J7Iki4->YRHFy,-0x1,2u);h2LrH3(&J7Iki4->
h2LrH3);}ZBFlD1:;}}xaiXa:;}}goto jFtDD4;lKr7C:;{J7Iki4->YRHFy->jfimS4
=J7Iki4->jfimS4|=4u;DhumT2(J7Iki4,RdZoN,aKuBh3);}jFtDD4:;}}goto yMivT1
;YJ3xz2:;{{if(!(J7Iki4->jfimS4&2u))goto XsLr1;{J7Iki4->YRHFy->jfimS4=
J7Iki4->jfimS4&=~0x2u;{if(!(J7Iki4->YRHFy->yjdp7))goto cVjEh2;{uYS5N2
(&J7Iki4->h2LrH3);J7Iki4->YRHFy->yjdp7(J7Iki4->YRHFy,-1,2u);h2LrH3(&
J7Iki4->h2LrH3);}cVjEh2:;}}XsLr1:;}}yMivT1:;}uYS5N2(&J7Iki4->h2LrH3);
return 0x1;}