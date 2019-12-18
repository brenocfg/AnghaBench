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
struct thread {TYPE_1__* td_proc; int /*<<< orphan*/  td_sigmask; int /*<<< orphan*/  td_siglist; } ;
struct task_struct {struct thread* task_thread; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_3__ {int /*<<< orphan*/  p_siglist; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SIGISEMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGSETNAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGSETOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
linux_signal_pending(struct task_struct *task)
{
	struct thread *td;
	sigset_t pending;

	td = task->task_thread;
	PROC_LOCK(td->td_proc);
	pending = td->td_siglist;
	SIGSETOR(pending, td->td_proc->p_siglist);
	SIGSETNAND(pending, td->td_sigmask);
	PROC_UNLOCK(td->td_proc);
	return (!SIGISEMPTY(pending));
}