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
typedef  scalar_t__ u_int ;
struct ucred {int cr_ngroups; } ;
struct thread {struct proc* td_proc; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_GROUPSET (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PRIV_CRED_SETGROUPS ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct ucred* crcopysafe (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  crextend (struct ucred*,scalar_t__) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct ucred* crget () ; 
 int /*<<< orphan*/  crsetgroups_locked (struct ucred*,scalar_t__,int /*<<< orphan*/ *) ; 
 int mac_cred_check_setgroups (struct ucred*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ngroups_max ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_set_cred (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  setsugid (struct proc*) ; 

int
kern_setgroups(struct thread *td, u_int ngrp, gid_t *groups)
{
	struct proc *p = td->td_proc;
	struct ucred *newcred, *oldcred;
	int error;

	MPASS(ngrp <= ngroups_max + 1);
	AUDIT_ARG_GROUPSET(groups, ngrp);
	newcred = crget();
	crextend(newcred, ngrp);
	PROC_LOCK(p);
	oldcred = crcopysafe(p, newcred);

#ifdef MAC
	error = mac_cred_check_setgroups(oldcred, ngrp, groups);
	if (error)
		goto fail;
#endif

	error = priv_check_cred(oldcred, PRIV_CRED_SETGROUPS);
	if (error)
		goto fail;

	if (ngrp == 0) {
		/*
		 * setgroups(0, NULL) is a legitimate way of clearing the
		 * groups vector on non-BSD systems (which generally do not
		 * have the egid in the groups[0]).  We risk security holes
		 * when running non-BSD software if we do not do the same.
		 */
		newcred->cr_ngroups = 1;
	} else {
		crsetgroups_locked(newcred, ngrp, groups);
	}
	setsugid(p);
	proc_set_cred(p, newcred);
	PROC_UNLOCK(p);
	crfree(oldcred);
	return (0);

fail:
	PROC_UNLOCK(p);
	crfree(newcred);
	return (error);
}