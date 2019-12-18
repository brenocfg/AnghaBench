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
struct proc {int p_flag; struct filedesc* p_fd; } ;
struct filedesc {int dummy; } ;

/* Variables and functions */
 int ERESTART ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_HADTHREADS ; 
 int P_SYSTEM ; 
 int RFCFDG ; 
 int RFFDG ; 
 int RFPROC ; 
 int /*<<< orphan*/  SINGLE_BOUNDARY ; 
 int /*<<< orphan*/  fdescfree (struct thread*) ; 
 struct filedesc* fdinit (struct filedesc*,int) ; 
 int /*<<< orphan*/  fdunshare (struct thread*) ; 
 scalar_t__ thread_single (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_single_end (struct proc*,int /*<<< orphan*/ ) ; 
 int vm_forkproc (struct thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
fork_norfproc(struct thread *td, int flags)
{
	int error;
	struct proc *p1;

	KASSERT((flags & RFPROC) == 0,
	    ("fork_norfproc called with RFPROC set"));
	p1 = td->td_proc;

	if (((p1->p_flag & (P_HADTHREADS|P_SYSTEM)) == P_HADTHREADS) &&
	    (flags & (RFCFDG | RFFDG))) {
		PROC_LOCK(p1);
		if (thread_single(p1, SINGLE_BOUNDARY)) {
			PROC_UNLOCK(p1);
			return (ERESTART);
		}
		PROC_UNLOCK(p1);
	}

	error = vm_forkproc(td, NULL, NULL, NULL, flags);
	if (error)
		goto fail;

	/*
	 * Close all file descriptors.
	 */
	if (flags & RFCFDG) {
		struct filedesc *fdtmp;
		fdtmp = fdinit(td->td_proc->p_fd, false);
		fdescfree(td);
		p1->p_fd = fdtmp;
	}

	/*
	 * Unshare file descriptors (from parent).
	 */
	if (flags & RFFDG)
		fdunshare(td);

fail:
	if (((p1->p_flag & (P_HADTHREADS|P_SYSTEM)) == P_HADTHREADS) &&
	    (flags & (RFCFDG | RFFDG))) {
		PROC_LOCK(p1);
		thread_single_end(p1, SINGLE_BOUNDARY);
		PROC_UNLOCK(p1);
	}
	return (error);
}