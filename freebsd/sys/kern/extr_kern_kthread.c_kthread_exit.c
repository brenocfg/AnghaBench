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
struct thread {struct proc* td_proc; } ;
struct proc {int p_numthreads; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMC_CALL_HOOK_UNLOCKED (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PMC_FN_THR_EXIT_LOG ; 
 scalar_t__ PMC_SYSTEM_SAMPLING_ACTIVE () ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_SLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  td_hash ; 
 int /*<<< orphan*/  tdsigcleanup (struct thread*) ; 
 int /*<<< orphan*/  thread_exit () ; 
 int /*<<< orphan*/  tidhash_lock ; 
 int /*<<< orphan*/  umtx_thread_exit (struct thread*) ; 
 int /*<<< orphan*/  wakeup (struct thread*) ; 

void
kthread_exit(void)
{
	struct proc *p;
	struct thread *td;

	td = curthread;
	p = td->td_proc;

#ifdef HWPMC_HOOKS
	if (PMC_SYSTEM_SAMPLING_ACTIVE())
		PMC_CALL_HOOK_UNLOCKED(td, PMC_FN_THR_EXIT_LOG, NULL);
#endif
	/* A module may be waiting for us to exit. */
	wakeup(td);

	/*
	 * The last exiting thread in a kernel process must tear down
	 * the whole process.
	 */
	rw_wlock(&tidhash_lock);
	PROC_LOCK(p);
	if (p->p_numthreads == 1) {
		PROC_UNLOCK(p);
		rw_wunlock(&tidhash_lock);
		kproc_exit(0);
	}
	LIST_REMOVE(td, td_hash);
	rw_wunlock(&tidhash_lock);
	umtx_thread_exit(td);
	tdsigcleanup(td);
	PROC_SLOCK(p);
	thread_exit();
}