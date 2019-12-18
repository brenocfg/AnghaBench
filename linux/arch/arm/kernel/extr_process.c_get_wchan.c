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
struct stackframe {unsigned long sp; unsigned long pc; scalar_t__ lr; int /*<<< orphan*/  fp; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 unsigned long THREAD_SIZE ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 
 int /*<<< orphan*/  thread_saved_fp (struct task_struct*) ; 
 unsigned long thread_saved_pc (struct task_struct*) ; 
 unsigned long thread_saved_sp (struct task_struct*) ; 
 scalar_t__ unwind_frame (struct stackframe*) ; 

unsigned long get_wchan(struct task_struct *p)
{
	struct stackframe frame;
	unsigned long stack_page;
	int count = 0;
	if (!p || p == current || p->state == TASK_RUNNING)
		return 0;

	frame.fp = thread_saved_fp(p);
	frame.sp = thread_saved_sp(p);
	frame.lr = 0;			/* recovered from the stack */
	frame.pc = thread_saved_pc(p);
	stack_page = (unsigned long)task_stack_page(p);
	do {
		if (frame.sp < stack_page ||
		    frame.sp >= stack_page + THREAD_SIZE ||
		    unwind_frame(&frame) < 0)
			return 0;
		if (!in_sched_functions(frame.pc))
			return frame.pc;
	} while (count ++ < 16);
	return 0;
}