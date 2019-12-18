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
struct thread_info {int dummy; } ;
struct task_struct {struct thread_info* stack; } ;
struct TYPE_2__ {struct task_struct* task; } ;

/* Variables and functions */
 TYPE_1__* _switch (struct thread_info*,struct thread_info*) ; 
 struct thread_info** current_thread_info_set ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ lwa_flag ; 
 size_t smp_processor_id () ; 

struct task_struct *__switch_to(struct task_struct *old,
				struct task_struct *new)
{
	struct task_struct *last;
	struct thread_info *new_ti, *old_ti;
	unsigned long flags;

	local_irq_save(flags);

	/* current_set is an array of saved current pointers
	 * (one for each cpu). we need them at user->kernel transition,
	 * while we save them at kernel->user transition
	 */
	new_ti = new->stack;
	old_ti = old->stack;

	lwa_flag = 0;

	current_thread_info_set[smp_processor_id()] = new_ti;
	last = (_switch(old_ti, new_ti))->task;

	local_irq_restore(flags);

	return last;
}