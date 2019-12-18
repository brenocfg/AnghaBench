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
typedef  int /*<<< orphan*/  u32 ;
struct arch_uprobe_task {scalar_t__ saved_tnpc; } ;
struct uprobe_task {scalar_t__ state; scalar_t__ vaddr; struct arch_uprobe_task autask; } ;
struct pt_regs {scalar_t__ tpc; scalar_t__ tnpc; } ;
struct arch_uprobe {int /*<<< orphan*/  ixol; } ;
struct TYPE_2__ {struct uprobe_task* utask; } ;

/* Variables and functions */
 scalar_t__ UTASK_SSTEP_ACK ; 
 TYPE_1__* current ; 
 scalar_t__ relbranch_fixup (int /*<<< orphan*/ ,struct uprobe_task*,struct pt_regs*) ; 
 int retpc_fixup (struct pt_regs*,int /*<<< orphan*/ ,unsigned long) ; 

int arch_uprobe_post_xol(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	struct uprobe_task *utask = current->utask;
	struct arch_uprobe_task *autask = &utask->autask;
	u32 insn = auprobe->ixol;
	int rc = 0;

	if (utask->state == UTASK_SSTEP_ACK) {
		regs->tnpc = relbranch_fixup(insn, utask, regs);
		regs->tpc = autask->saved_tnpc;
		rc =  retpc_fixup(regs, insn, (unsigned long) utask->vaddr);
	} else {
		regs->tnpc = utask->vaddr+4;
		regs->tpc = autask->saved_tnpc+4;
	}
	return rc;
}