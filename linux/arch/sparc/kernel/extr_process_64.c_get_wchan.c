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
struct thread_info {unsigned long ksp; } ;
struct task_struct {scalar_t__ state; } ;
struct reg_window {unsigned long* ins; } ;

/* Variables and functions */
 unsigned long STACK_BIAS ; 
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 
 int /*<<< orphan*/  kstack_valid (struct thread_info*,unsigned long) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

unsigned long get_wchan(struct task_struct *task)
{
	unsigned long pc, fp, bias = 0;
	struct thread_info *tp;
	struct reg_window *rw;
        unsigned long ret = 0;
	int count = 0; 

	if (!task || task == current ||
            task->state == TASK_RUNNING)
		goto out;

	tp = task_thread_info(task);
	bias = STACK_BIAS;
	fp = task_thread_info(task)->ksp + bias;

	do {
		if (!kstack_valid(tp, fp))
			break;
		rw = (struct reg_window *) fp;
		pc = rw->ins[7];
		if (!in_sched_functions(pc)) {
			ret = pc;
			goto out;
		}
		fp = rw->ins[6] + bias;
	} while (++count < 16);

out:
	return ret;
}