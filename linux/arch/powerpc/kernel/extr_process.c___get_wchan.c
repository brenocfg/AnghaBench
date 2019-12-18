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
struct task_struct {scalar_t__ state; TYPE_1__ thread; } ;

/* Variables and functions */
 size_t STACK_FRAME_LR_SAVE ; 
 int /*<<< orphan*/  STACK_FRAME_OVERHEAD ; 
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 
 int /*<<< orphan*/  validate_sp (unsigned long,struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long __get_wchan(struct task_struct *p)
{
	unsigned long ip, sp;
	int count = 0;

	if (!p || p == current || p->state == TASK_RUNNING)
		return 0;

	sp = p->thread.ksp;
	if (!validate_sp(sp, p, STACK_FRAME_OVERHEAD))
		return 0;

	do {
		sp = *(unsigned long *)sp;
		if (!validate_sp(sp, p, STACK_FRAME_OVERHEAD) ||
		    p->state == TASK_RUNNING)
			return 0;
		if (count > 0) {
			ip = ((unsigned long *)sp)[STACK_FRAME_LR_SAVE];
			if (!in_sched_functions(ip))
				return ip;
		}
	} while (count++ < 16);
	return 0;
}