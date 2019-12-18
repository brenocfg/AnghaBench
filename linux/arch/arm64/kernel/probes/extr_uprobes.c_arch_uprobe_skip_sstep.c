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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,unsigned long,struct pt_regs*) ;} ;
struct arch_uprobe {TYPE_1__ api; int /*<<< orphan*/ * insn; int /*<<< orphan*/  simulate; } ;
typedef  int /*<<< orphan*/  probe_opcode_t ;

/* Variables and functions */
 unsigned long instruction_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned long,struct pt_regs*) ; 

bool arch_uprobe_skip_sstep(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	probe_opcode_t insn;
	unsigned long addr;

	if (!auprobe->simulate)
		return false;

	insn = *(probe_opcode_t *)(&auprobe->insn[0]);
	addr = instruction_pointer(regs);

	if (auprobe->api.handler)
		auprobe->api.handler(insn, addr, regs);

	return true;
}