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
struct arch_uprobe {int /*<<< orphan*/  insn; } ;

/* Variables and functions */
 int emulate_step (struct pt_regs*,int /*<<< orphan*/ ) ; 

bool arch_uprobe_skip_sstep(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	int ret;

	/*
	 * emulate_step() returns 1 if the insn was successfully emulated.
	 * For all other cases, we need to single-step in hardware.
	 */
	ret = emulate_step(regs, auprobe->insn);
	if (ret > 0)
		return true;

	return false;
}