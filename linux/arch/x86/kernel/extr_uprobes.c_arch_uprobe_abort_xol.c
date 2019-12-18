#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  saved_tf; int /*<<< orphan*/  saved_trap_nr; } ;
struct uprobe_task {TYPE_3__ autask; int /*<<< orphan*/  vaddr; } ;
struct pt_regs {int /*<<< orphan*/  flags; int /*<<< orphan*/  ip; } ;
struct arch_uprobe {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  trap_nr; } ;
struct TYPE_8__ {TYPE_2__ thread; struct uprobe_task* utask; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* abort ) (struct arch_uprobe*,struct pt_regs*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  X86_EFLAGS_TF ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  stub1 (struct arch_uprobe*,struct pt_regs*) ; 

void arch_uprobe_abort_xol(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	struct uprobe_task *utask = current->utask;

	if (auprobe->ops->abort)
		auprobe->ops->abort(auprobe, regs);

	current->thread.trap_nr = utask->autask.saved_trap_nr;
	regs->ip = utask->vaddr;
	/* clear TF if it was set by us in arch_uprobe_pre_xol() */
	if (!utask->autask.saved_tf)
		regs->flags &= ~X86_EFLAGS_TF;
}