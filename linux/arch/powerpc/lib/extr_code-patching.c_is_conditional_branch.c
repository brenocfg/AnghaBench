#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

bool is_conditional_branch(unsigned int instr)
{
	unsigned int opcode = instr >> 26;

	if (opcode == 16)       /* bc, bca, bcl, bcla */
		return true;
	if (opcode == 19) {
		switch ((instr >> 1) & 0x3ff) {
		case 16:        /* bclr, bclrl */
		case 528:       /* bcctr, bcctrl */
		case 560:       /* bctar, bctarl */
			return true;
		}
	}
	return false;
}