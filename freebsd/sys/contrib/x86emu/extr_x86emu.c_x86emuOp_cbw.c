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
struct TYPE_2__ {int mode; int R_AX; int R_EAX; int R_AL; int R_AH; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int SYSMODE_PREFIX_DATA ; 

__attribute__((used)) static void
x86emuOp_cbw(struct x86emu *emu)
{
	if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
		if (emu->x86.R_AX & 0x8000) {
			emu->x86.R_EAX |= 0xffff0000;
		} else {
			emu->x86.R_EAX &= 0x0000ffff;
		}
	} else {
		if (emu->x86.R_AL & 0x80) {
			emu->x86.R_AH = 0xff;
		} else {
			emu->x86.R_AH = 0x0;
		}
	}
}