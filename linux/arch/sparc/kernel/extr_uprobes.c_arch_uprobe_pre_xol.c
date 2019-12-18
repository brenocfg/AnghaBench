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
struct arch_uprobe_task {int /*<<< orphan*/  saved_tnpc; int /*<<< orphan*/  saved_tpc; } ;
struct uprobe_task {int /*<<< orphan*/  xol_vaddr; struct arch_uprobe_task autask; } ;
struct pt_regs {int /*<<< orphan*/  tnpc; int /*<<< orphan*/  tpc; } ;
struct arch_uprobe {int dummy; } ;
struct TYPE_2__ {struct uprobe_task* utask; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  instruction_pointer_set (struct pt_regs*,int /*<<< orphan*/ ) ; 

int arch_uprobe_pre_xol(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	struct uprobe_task *utask = current->utask;
	struct arch_uprobe_task *autask = &current->utask->autask;

	/* Save the current program counters so they can be restored
	 * later.
	 */
	autask->saved_tpc = regs->tpc;
	autask->saved_tnpc = regs->tnpc;

	/* Adjust PC and NPC so the first instruction in the XOL slot
	 * will be executed by the user task.
	 */
	instruction_pointer_set(regs, utask->xol_vaddr);

	return 0;
}