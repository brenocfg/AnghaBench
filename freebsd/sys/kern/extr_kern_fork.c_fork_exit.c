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
struct trapframe {int dummy; } ;
struct thread {char* td_name; int /*<<< orphan*/  td_pflags; struct proc* td_proc; } ;
struct proc {scalar_t__ p_state; int p_pid; int p_flag; TYPE_1__* p_sysent; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sv_schedtail ) (struct thread*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,struct thread*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_PROC ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PRS_NORMAL ; 
 int P_KPROC ; 
 int /*<<< orphan*/  TDP_FORKING ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  deadthread ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  sched_fork_exit (struct thread*) ; 
 int /*<<< orphan*/  stub1 (struct thread*) ; 
 int /*<<< orphan*/  td_get_sched (struct thread*) ; 
 int /*<<< orphan*/  thread_stash (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
fork_exit(void (*callout)(void *, struct trapframe *), void *arg,
    struct trapframe *frame)
{
	struct proc *p;
	struct thread *td;
	struct thread *dtd;

	td = curthread;
	p = td->td_proc;
	KASSERT(p->p_state == PRS_NORMAL, ("executing process is still new"));

	CTR4(KTR_PROC, "fork_exit: new thread %p (td_sched %p, pid %d, %s)",
	    td, td_get_sched(td), p->p_pid, td->td_name);

	sched_fork_exit(td);
	/*
	* Processes normally resume in mi_switch() after being
	* cpu_switch()'ed to, but when children start up they arrive here
	* instead, so we must do much the same things as mi_switch() would.
	*/
	if ((dtd = PCPU_GET(deadthread))) {
		PCPU_SET(deadthread, NULL);
		thread_stash(dtd);
	}
	thread_unlock(td);

	/*
	 * cpu_fork_kthread_handler intercepts this function call to
	 * have this call a non-return function to stay in kernel mode.
	 * initproc has its own fork handler, but it does return.
	 */
	KASSERT(callout != NULL, ("NULL callout in fork_exit"));
	callout(arg, frame);

	/*
	 * Check if a kernel thread misbehaved and returned from its main
	 * function.
	 */
	if (p->p_flag & P_KPROC) {
		printf("Kernel thread \"%s\" (pid %d) exited prematurely.\n",
		    td->td_name, p->p_pid);
		kthread_exit();
	}
	mtx_assert(&Giant, MA_NOTOWNED);

	if (p->p_sysent->sv_schedtail != NULL)
		(p->p_sysent->sv_schedtail)(td);
	td->td_pflags &= ~TDP_FORKING;
}