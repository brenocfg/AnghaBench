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
struct pt_regs {int tnpc; int tpc; } ;
struct arch_uprobe {int ixol; } ;

/* Variables and functions */

bool arch_uprobe_skip_sstep(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	/* We currently only emulate NOP instructions.
	 */

	if (auprobe->ixol == (1 << 24)) {
		regs->tnpc += 4;
		regs->tpc += 4;
		return true;
	}

	return false;
}