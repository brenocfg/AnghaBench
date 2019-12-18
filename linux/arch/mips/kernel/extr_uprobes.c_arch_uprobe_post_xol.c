#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  saved_trap_nr; } ;
struct uprobe_task {TYPE_2__ autask; } ;
struct pt_regs {int /*<<< orphan*/  cp0_epc; } ;
struct arch_uprobe {int /*<<< orphan*/  resume_epc; } ;
struct TYPE_4__ {int /*<<< orphan*/  trap_nr; } ;
struct TYPE_6__ {TYPE_1__ thread; struct uprobe_task* utask; } ;

/* Variables and functions */
 TYPE_3__* current ; 

int arch_uprobe_post_xol(struct arch_uprobe *aup, struct pt_regs *regs)
{
	struct uprobe_task *utask = current->utask;

	current->thread.trap_nr = utask->autask.saved_trap_nr;
	regs->cp0_epc = aup->resume_epc;

	return 0;
}