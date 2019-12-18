#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int SP4ZU; int GEt0d; int /*<<< orphan*/  h2LrH3; TYPE_1__* fV7o35; } ;
typedef  TYPE_2__ kWMzp1 ;
struct TYPE_5__ {unsigned long UyRVB4; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUUSL3 (unsigned long volatile*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  GLE_s4 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  h2LrH3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uYS5N2 (int /*<<< orphan*/ *) ; 

int
__attribute__((cdecl))TAU32_SetCasIo(kWMzp1*J7Iki4,int qUKv12){{if(!(
J7Iki4->SP4ZU==02))goto BBR_Y2;return 0;goto sYPGd4;BBR_Y2:;{unsigned
t57WF3;h2LrH3(&J7Iki4->h2LrH3);t57WF3=J7Iki4->GEt0d&~0x8;{if(!(qUKv12
))goto E98ZN1;t57WF3|=010;E98ZN1:;}{if(!(J7Iki4->GEt0d!=t57WF3))goto
x4H574;{volatile unsigned long*RdZoN;RdZoN=&J7Iki4->fV7o35->UyRVB4;
AUUSL3(RdZoN,0,J7Iki4->GEt0d=t57WF3);GLE_s4(J7Iki4,(-1));}x4H574:;}
uYS5N2(&J7Iki4->h2LrH3);return 1;}sYPGd4:;}}