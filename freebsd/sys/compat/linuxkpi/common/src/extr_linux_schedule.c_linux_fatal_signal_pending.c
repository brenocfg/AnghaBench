#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_1__* td_proc; int /*<<< orphan*/  td_siglist; } ;
struct task_struct {struct thread* task_thread; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_siglist; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_1__*) ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGKILL ; 

bool
linux_fatal_signal_pending(struct task_struct *task)
{
	struct thread *td;
	bool ret;

	td = task->task_thread;
	PROC_LOCK(td->td_proc);
	ret = SIGISMEMBER(td->td_siglist, SIGKILL) ||
	    SIGISMEMBER(td->td_proc->p_siglist, SIGKILL);
	PROC_UNLOCK(td->td_proc);
	return (ret);
}