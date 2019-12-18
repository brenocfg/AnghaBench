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
struct TYPE_2__ {unsigned long ksp; } ;
struct task_struct {TYPE_1__ thread; } ;
struct stack_trace {int dummy; } ;

/* Variables and functions */
 struct task_struct* current ; 
 unsigned long current_stack_pointer () ; 
 int /*<<< orphan*/  put_task_stack (struct task_struct*) ; 
 int /*<<< orphan*/  save_context_stack (struct stack_trace*,unsigned long,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_get_task_stack (struct task_struct*) ; 

void save_stack_trace_tsk(struct task_struct *tsk, struct stack_trace *trace)
{
	unsigned long sp;

	if (!try_get_task_stack(tsk))
		return;

	if (tsk == current)
		sp = current_stack_pointer();
	else
		sp = tsk->thread.ksp;

	save_context_stack(trace, sp, tsk, 0);

	put_task_stack(tsk);
}