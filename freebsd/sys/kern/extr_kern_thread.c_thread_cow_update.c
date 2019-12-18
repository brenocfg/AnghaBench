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
struct ucred {int dummy; } ;
struct thread {int /*<<< orphan*/  td_cowgen; struct plimit* td_limit; struct ucred* td_ucred; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_cowgen; struct plimit* p_limit; struct ucred* p_ucred; } ;
struct plimit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct ucred* crhold (struct ucred*) ; 
 int /*<<< orphan*/  lim_free (struct plimit*) ; 
 struct plimit* lim_hold (struct plimit*) ; 

void
thread_cow_update(struct thread *td)
{
	struct proc *p;
	struct ucred *oldcred;
	struct plimit *oldlimit;

	p = td->td_proc;
	oldcred = NULL;
	oldlimit = NULL;
	PROC_LOCK(p);
	if (td->td_ucred != p->p_ucred) {
		oldcred = td->td_ucred;
		td->td_ucred = crhold(p->p_ucred);
	}
	if (td->td_limit != p->p_limit) {
		oldlimit = td->td_limit;
		td->td_limit = lim_hold(p->p_limit);
	}
	td->td_cowgen = p->p_cowgen;
	PROC_UNLOCK(p);
	if (oldcred != NULL)
		crfree(oldcred);
	if (oldlimit != NULL)
		lim_free(oldlimit);
}