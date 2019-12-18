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
struct TYPE_2__ {scalar_t__ sp; } ;
struct task_struct {scalar_t__ state; TYPE_1__ thread; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* current ; 
 scalar_t__ in_sched_functions (unsigned long) ; 
 unsigned long thread_saved_pc (struct task_struct*) ; 

unsigned long get_wchan(struct task_struct *p)
{
	unsigned long pc;

	if (!p || p == current || p->state == TASK_RUNNING)
		return 0;

	/*
	 * The same comment as on the Alpha applies here, too ...
	 */
	pc = thread_saved_pc(p);

#ifdef CONFIG_FRAME_POINTER
	if (in_sched_functions(pc)) {
		unsigned long schedule_frame = (unsigned long)p->thread.sp;
		return ((unsigned long *)schedule_frame)[21];
	}
#endif

	return pc;
}