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
struct thread {int /*<<< orphan*/  td_dbgflags; struct proc* td_proc; } ;
struct proc {int p_numthreads; int p_pendingexits; int p_ptevents; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SYSCALL_EXIT (int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_SLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int PTRACE_LWP ; 
 int /*<<< orphan*/  RACCT_NTHR ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  TDB_EXIT ; 
 int /*<<< orphan*/  ptracestop (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  racct_sub (struct proc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tdsigcleanup (struct thread*) ; 
 int /*<<< orphan*/  thread_exit () ; 
 int /*<<< orphan*/  thread_stopped (struct proc*) ; 
 int /*<<< orphan*/  tidhash_remove (struct thread*) ; 

int
kern_thr_exit(struct thread *td)
{
	struct proc *p;

	p = td->td_proc;

	/*
	 * If all of the threads in a process call this routine to
	 * exit (e.g. all threads call pthread_exit()), exactly one
	 * thread should return to the caller to terminate the process
	 * instead of the thread.
	 *
	 * Checking p_numthreads alone is not sufficient since threads
	 * might be committed to terminating while the PROC_LOCK is
	 * dropped in either ptracestop() or while removing this thread
	 * from the tidhash.  Instead, the p_pendingexits field holds
	 * the count of threads in either of those states and a thread
	 * is considered the "last" thread if all of the other threads
	 * in a process are already terminating.
	 */
	PROC_LOCK(p);
	if (p->p_numthreads == p->p_pendingexits + 1) {
		/*
		 * Ignore attempts to shut down last thread in the
		 * proc.  This will actually call _exit(2) in the
		 * usermode trampoline when it returns.
		 */
		PROC_UNLOCK(p);
		return (0);
	}

	p->p_pendingexits++;
	td->td_dbgflags |= TDB_EXIT;
	if (p->p_ptevents & PTRACE_LWP)
		ptracestop(td, SIGTRAP, NULL);
	PROC_UNLOCK(p);
	tidhash_remove(td);
	PROC_LOCK(p);
	p->p_pendingexits--;

	/*
	 * The check above should prevent all other threads from this
	 * process from exiting while the PROC_LOCK is dropped, so
	 * there must be at least one other thread other than the
	 * current thread.
	 */
	KASSERT(p->p_numthreads > 1, ("too few threads"));
	racct_sub(p, RACCT_NTHR, 1);
	tdsigcleanup(td);

#ifdef AUDIT
	AUDIT_SYSCALL_EXIT(0, td);
#endif

	PROC_SLOCK(p);
	thread_stopped(p);
	thread_exit();
	/* NOTREACHED */
}