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
struct task_struct {int dummy; } ;
struct pt_regs {scalar_t__ int_code; } ;

/* Variables and functions */
 scalar_t__ UPROBE_TRAP_NR ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

bool arch_uprobe_xol_was_trapped(struct task_struct *tsk)
{
	struct pt_regs *regs = task_pt_regs(tsk);

	if (regs->int_code != UPROBE_TRAP_NR)
		return true;
	return false;
}