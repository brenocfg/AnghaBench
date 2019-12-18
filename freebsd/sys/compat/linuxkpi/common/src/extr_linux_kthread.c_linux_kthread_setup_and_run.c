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
struct thread {struct task_struct* td_lkpi_task; } ;
struct task_struct {void* task_data; int /*<<< orphan*/ * task_fn; } ;
typedef  int /*<<< orphan*/  linux_task_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  PI_SWI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRQ_BORING ; 
 int /*<<< orphan*/  SWI_NET ; 
 int /*<<< orphan*/  linux_set_current (struct thread*) ; 
 int /*<<< orphan*/  sched_add (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_prio (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

struct task_struct *
linux_kthread_setup_and_run(struct thread *td, linux_task_fn_t *task_fn, void *arg)
{
	struct task_struct *task;

	linux_set_current(td);

	task = td->td_lkpi_task;
	task->task_fn = task_fn;
	task->task_data = arg;

	thread_lock(td);
	/* make sure the scheduler priority is raised */
	sched_prio(td, PI_SWI(SWI_NET));
	/* put thread into run-queue */
	sched_add(td, SRQ_BORING);
	thread_unlock(td);

	return (task);
}