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
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 scalar_t__ THREAD_SIZE ; 
 struct task_struct* current ; 
 scalar_t__ current_stack_pointer ; 
 int /*<<< orphan*/  dump_mem (char*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  show_trace (struct task_struct*,unsigned long*,int /*<<< orphan*/ *) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 

void show_stack(struct task_struct *tsk, unsigned long *sp)
{
	unsigned long stack;

	if (!tsk)
		tsk = current;
	if (tsk == current)
		sp = (unsigned long *)current_stack_pointer;
	else
		sp = (unsigned long *)tsk->thread.sp;

	stack = (unsigned long)sp;
	dump_mem("Stack: ", stack, THREAD_SIZE +
		 (unsigned long)task_stack_page(tsk));
	show_trace(tsk, sp, NULL);
}