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
struct pt_regs {int dummy; } ;

/* Variables and functions */

void gdb_regs_to_pt_regs(unsigned long *gdb_regs, struct pt_regs *regs)
{
	unsigned int i;
	unsigned long *pt_regb = (unsigned long *)regs;

	/* pt_regs and gdb_regs have the same 37 values.
	 * The rest of gdb_regs are unused and can't be changed.
	 * r0 register value can't be changed too. */
	for (i = 1; i < (sizeof(struct pt_regs) / 4) - 1; i++)
		pt_regb[i] = gdb_regs[i];
}