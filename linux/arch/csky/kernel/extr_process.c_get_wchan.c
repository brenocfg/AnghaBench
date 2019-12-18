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
struct task_struct {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 scalar_t__ THREAD_SIZE ; 
 scalar_t__ __kernel_text_address (unsigned long) ; 
 struct task_struct* current ; 
 scalar_t__ end_of_stack (struct task_struct*) ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 
 scalar_t__ thread_saved_fp (struct task_struct*) ; 

unsigned long get_wchan(struct task_struct *p)
{
	unsigned long lr;
	unsigned long *fp, *stack_start, *stack_end;
	int count = 0;

	if (!p || p == current || p->state == TASK_RUNNING)
		return 0;

	stack_start = (unsigned long *)end_of_stack(p);
	stack_end = (unsigned long *)(task_stack_page(p) + THREAD_SIZE);

	fp = (unsigned long *) thread_saved_fp(p);
	do {
		if (fp < stack_start || fp > stack_end)
			return 0;
#ifdef CONFIG_STACKTRACE
		lr = fp[1];
		fp = (unsigned long *)fp[0];
#else
		lr = *fp++;
#endif
		if (!in_sched_functions(lr) &&
		    __kernel_text_address(lr))
			return lr;
	} while (count++ < 16);

	return 0;
}