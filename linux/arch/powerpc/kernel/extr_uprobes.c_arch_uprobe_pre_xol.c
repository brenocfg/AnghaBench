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
struct pt_regs {int /*<<< orphan*/  nip; } ;
struct arch_uprobe_task {int /*<<< orphan*/  saved_trap_nr; } ;
struct arch_uprobe {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  trap_nr; } ;
struct TYPE_7__ {TYPE_2__* utask; TYPE_1__ thread; } ;
struct TYPE_6__ {int /*<<< orphan*/  xol_vaddr; struct arch_uprobe_task autask; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPROBE_TRAP_NR ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  user_enable_single_step (TYPE_3__*) ; 

int arch_uprobe_pre_xol(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	struct arch_uprobe_task *autask = &current->utask->autask;

	autask->saved_trap_nr = current->thread.trap_nr;
	current->thread.trap_nr = UPROBE_TRAP_NR;
	regs->nip = current->utask->xol_vaddr;

	user_enable_single_step(current);
	return 0;
}