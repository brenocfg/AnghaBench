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

/* Variables and functions */
 int /*<<< orphan*/  clear_fpu (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_used_math () ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  flush_ptrace_hw_breakpoint (struct task_struct*) ; 
 int /*<<< orphan*/  task_pt_regs (struct task_struct*) ; 

void flush_thread(void)
{
	struct task_struct *tsk = current;

	flush_ptrace_hw_breakpoint(tsk);

#if defined(CONFIG_SH_FPU)
	/* Forget lazy FPU state */
	clear_fpu(tsk, task_pt_regs(tsk));
	clear_used_math();
#endif
}