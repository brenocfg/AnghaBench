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
 int ERESTART ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_HADTHREADS ; 
 int /*<<< orphan*/  SINGLE_BOUNDARY ; 
 int TDP_EXECVMSPC ; 
 struct thread* curthread ; 
 scalar_t__ thread_single (struct proc*,int /*<<< orphan*/ ) ; 

int
pre_execve(struct thread *td, struct vmspace **oldvmspace)
{
	struct proc *p;
	int error;

	KASSERT(td == curthread, ("non-current thread %p", td));
	error = 0;
	p = td->td_proc;
	if ((p->p_flag & P_HADTHREADS) != 0) {
		PROC_LOCK(p);
		if (thread_single(p, SINGLE_BOUNDARY) != 0)
			error = ERESTART;
		PROC_UNLOCK(p);
	}
	KASSERT(error != 0 || (td->td_pflags & TDP_EXECVMSPC) == 0,
	    ("nested execve"));
	*oldvmspace = p->p_vmspace;
	return (error);
}