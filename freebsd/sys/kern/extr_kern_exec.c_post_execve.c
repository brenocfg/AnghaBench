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
struct vmspace {int dummy; } ;
struct thread {int td_pflags; struct proc* td_proc; } ;
struct proc {int p_flag; struct vmspace* p_vmspace; } ;

/* Variables and functions */
 int EJUSTRETURN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_HADTHREADS ; 
 int /*<<< orphan*/  SINGLE_BOUNDARY ; 
 int /*<<< orphan*/  SINGLE_EXIT ; 
 int TDP_EXECVMSPC ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  thread_single (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_single_end (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmspace_free (struct vmspace*) ; 

void
post_execve(struct thread *td, int error, struct vmspace *oldvmspace)
{
	struct proc *p;

	KASSERT(td == curthread, ("non-current thread %p", td));
	p = td->td_proc;
	if ((p->p_flag & P_HADTHREADS) != 0) {
		PROC_LOCK(p);
		/*
		 * If success, we upgrade to SINGLE_EXIT state to
		 * force other threads to suicide.
		 */
		if (error == EJUSTRETURN)
			thread_single(p, SINGLE_EXIT);
		else
			thread_single_end(p, SINGLE_BOUNDARY);
		PROC_UNLOCK(p);
	}
	if ((td->td_pflags & TDP_EXECVMSPC) != 0) {
		KASSERT(p->p_vmspace != oldvmspace,
		    ("oldvmspace still used"));
		vmspace_free(oldvmspace);
		td->td_pflags &= ~TDP_EXECVMSPC;
	}
}