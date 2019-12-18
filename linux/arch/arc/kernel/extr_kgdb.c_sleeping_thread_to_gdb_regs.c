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
struct TYPE_2__ {scalar_t__ callee_reg; } ;
struct task_struct {TYPE_1__ thread; } ;
struct callee_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  task_pt_regs (struct task_struct*) ; 
 int /*<<< orphan*/  to_gdb_regs (unsigned long*,int /*<<< orphan*/ ,struct callee_regs*) ; 

void sleeping_thread_to_gdb_regs(unsigned long *gdb_regs,
				 struct task_struct *task)
{
	if (task)
		to_gdb_regs(gdb_regs, task_pt_regs(task),
			(struct callee_regs *) task->thread.callee_reg);
}