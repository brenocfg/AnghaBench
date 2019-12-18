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
 int /*<<< orphan*/  KERN_DEFAULT ; 
 struct task_struct* current ; 
 unsigned long* get_stack_pointer (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_trace_log_lvl (struct task_struct*,int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ ) ; 

void show_stack(struct task_struct *task, unsigned long *sp)
{
	task = task ? : current;

	/*
	 * Stack frames below this one aren't interesting.  Don't show them
	 * if we're printing for %current.
	 */
	if (!sp && task == current)
		sp = get_stack_pointer(current, NULL);

	show_trace_log_lvl(task, NULL, sp, KERN_DEFAULT);
}