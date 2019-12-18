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
 int /*<<< orphan*/  CONFIG_FRAME_POINTER ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ TASK_RUNNING ; 
 unsigned long THREAD_SIZE ; 
 struct task_struct* current ; 
 scalar_t__ end_of_stack (struct task_struct*) ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 
 unsigned long thread_saved_fp (struct task_struct*) ; 

unsigned long get_wchan(struct task_struct *p)
{
	unsigned long fp, lr;
	unsigned long stack_start, stack_end;
	int count = 0;

	if (!p || p == current || p->state == TASK_RUNNING)
		return 0;

	if (IS_ENABLED(CONFIG_FRAME_POINTER)) {
		stack_start = (unsigned long)end_of_stack(p);
		stack_end = (unsigned long)task_stack_page(p) + THREAD_SIZE;

		fp = thread_saved_fp(p);
		do {
			if (fp < stack_start || fp > stack_end)
				return 0;
			lr = ((unsigned long *)fp)[0];
			if (!in_sched_functions(lr))
				return lr;
			fp = *(unsigned long *)(fp + 4);
		} while (count++ < 16);
	}
	return 0;
}