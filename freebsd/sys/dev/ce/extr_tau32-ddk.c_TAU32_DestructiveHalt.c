#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* YRHFy; TYPE_1__* fV7o35; int /*<<< orphan*/  uyKJn2; int /*<<< orphan*/  h2LrH3; } ;
typedef  TYPE_3__ kWMzp1 ;
struct TYPE_11__ {scalar_t__ NNm8q; scalar_t__ QhwfE1; } ;
struct TYPE_10__ {unsigned long UyRVB4; int Be1a54; scalar_t__ PGh3e4; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUUSL3 (unsigned long volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B1Wc_1 (TYPE_3__*) ; 
 int /*<<< orphan*/  CLbj94 (TYPE_3__*) ; 
 int /*<<< orphan*/  IoSy32 (TYPE_3__*,int,int) ; 
 int Sptqu ; 
 int /*<<< orphan*/  WdqxE (TYPE_3__*,int) ; 
 int /*<<< orphan*/  blWHd2 ; 
 int /*<<< orphan*/  c0gFy1 (TYPE_3__*,int) ; 
 int gQf6j1 ; 
 int /*<<< orphan*/  l4W8X (unsigned long volatile*) ; 
 int r3CcP2 ; 
 int /*<<< orphan*/  wP7Tk3 (int /*<<< orphan*/ *) ; 

void __attribute__((
cdecl))TAU32_DestructiveHalt(kWMzp1*J7Iki4,int mdbib4){volatile
unsigned long*RdZoN;CLbj94(J7Iki4);wP7Tk3(&J7Iki4->h2LrH3);J7Iki4->
fV7o35->PGh3e4=0;RdZoN=&J7Iki4->fV7o35->UyRVB4;IoSy32(J7Iki4,0x16,0);
IoSy32(J7Iki4,027,0);J7Iki4->uyKJn2=blWHd2;J7Iki4->fV7o35->Be1a54=(
gQf6j1|Sptqu|r3CcP2);{J_oOV2:{__asm __volatile(""::);__asm __volatile
("lock; addl $0,(%%esp)": : :"cc");__asm __volatile(""::);}if(0)goto
J_oOV2;};IoSy32(J7Iki4,18,16);WdqxE(J7Iki4,16);IoSy32(J7Iki4,0x18,0x1
);WdqxE(J7Iki4,16);B1Wc_1(J7Iki4);AUUSL3(RdZoN,0,0);l4W8X(RdZoN);((
RdZoN)[-01])=0;J7Iki4->YRHFy->QhwfE1=0;J7Iki4->YRHFy->NNm8q=0;c0gFy1(
J7Iki4,mdbib4);}