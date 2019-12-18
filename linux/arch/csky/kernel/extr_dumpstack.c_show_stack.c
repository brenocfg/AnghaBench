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
 int /*<<< orphan*/  show_trace (unsigned long*) ; 
 scalar_t__ thread_saved_fp (struct task_struct*) ; 

void show_stack(struct task_struct *task, unsigned long *stack)
{
	if (!stack) {
		if (task)
			stack = (unsigned long *)thread_saved_fp(task);
		else
#ifdef CONFIG_STACKTRACE
			asm volatile("mov %0, r8\n":"=r"(stack)::"memory");
#else
			stack = (unsigned long *)&stack;
#endif
	}

	show_trace(stack);
}