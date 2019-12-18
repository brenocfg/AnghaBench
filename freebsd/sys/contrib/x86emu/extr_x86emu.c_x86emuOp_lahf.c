#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int R_AH; int R_FLG; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */

__attribute__((used)) static void
x86emuOp_lahf(struct x86emu *emu)
{
	emu->x86.R_AH = (uint8_t) (emu->x86.R_FLG & 0xff);
	/* undocumented TC++ behavior??? Nope.  It's documented, but you have
	 * too look real hard to notice it. */
	emu->x86.R_AH |= 0x2;
}