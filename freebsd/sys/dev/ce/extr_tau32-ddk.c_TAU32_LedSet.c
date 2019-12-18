#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int GEt0d; unsigned int jfimS4; int /*<<< orphan*/  h2LrH3; TYPE_2__* fV7o35; TYPE_1__* YRHFy; } ;
typedef  TYPE_3__ kWMzp1 ;
struct TYPE_6__ {unsigned long UyRVB4; } ;
struct TYPE_5__ {unsigned int jfimS4; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUUSL3 (unsigned long volatile*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  h2LrH3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uYS5N2 (int /*<<< orphan*/ *) ; 

void
__attribute__((cdecl))TAU32_LedSet(kWMzp1*J7Iki4,int xkMXp){unsigned
t57WF3;h2LrH3(&J7Iki4->h2LrH3);t57WF3=J7Iki4->GEt0d&~16;{if(!(xkMXp))goto
nToJ62;t57WF3|=16;nToJ62:;}{if(!(J7Iki4->GEt0d!=t57WF3))goto d7HTj3;{
volatile unsigned long*RdZoN;unsigned jfimS4=J7Iki4->jfimS4&~8u;{if(!
(t57WF3&16))goto pylPi3;jfimS4|=0x8u;pylPi3:;}J7Iki4->YRHFy->jfimS4=
J7Iki4->jfimS4=jfimS4;RdZoN=&J7Iki4->fV7o35->UyRVB4;AUUSL3(RdZoN,0,
J7Iki4->GEt0d=t57WF3);}d7HTj3:;}uYS5N2(&J7Iki4->h2LrH3);}