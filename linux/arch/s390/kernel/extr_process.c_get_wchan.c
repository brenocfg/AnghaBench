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
struct TYPE_2__ {scalar_t__ ksp; } ;
struct task_struct {scalar_t__ state; TYPE_1__ thread; } ;
struct stack_frame {int /*<<< orphan*/ * gprs; int /*<<< orphan*/  back_chain; } ;

/* Variables and functions */
 unsigned long READ_ONCE_NOCHECK (int /*<<< orphan*/ ) ; 
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 
 int /*<<< orphan*/  put_task_stack (struct task_struct*) ; 
 scalar_t__ task_pt_regs (struct task_struct*) ; 
 struct stack_frame* task_stack_page (struct task_struct*) ; 
 int /*<<< orphan*/  try_get_task_stack (struct task_struct*) ; 

unsigned long get_wchan(struct task_struct *p)
{
	struct stack_frame *sf, *low, *high;
	unsigned long return_address;
	int count;

	if (!p || p == current || p->state == TASK_RUNNING || !task_stack_page(p))
		return 0;

	if (!try_get_task_stack(p))
		return 0;

	low = task_stack_page(p);
	high = (struct stack_frame *) task_pt_regs(p);
	sf = (struct stack_frame *) p->thread.ksp;
	if (sf <= low || sf > high) {
		return_address = 0;
		goto out;
	}
	for (count = 0; count < 16; count++) {
		sf = (struct stack_frame *)READ_ONCE_NOCHECK(sf->back_chain);
		if (sf <= low || sf > high) {
			return_address = 0;
			goto out;
		}
		return_address = READ_ONCE_NOCHECK(sf->gprs[8]);
		if (!in_sched_functions(return_address))
			goto out;
	}
out:
	put_task_stack(p);
	return return_address;
}