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
struct ucred {struct loginclass* cr_loginclass; } ;
struct thread {struct proc* td_proc; } ;
struct setloginclass_args {int /*<<< orphan*/  namebuf; } ;
struct proc {int dummy; } ;
struct loginclass {int dummy; } ;
typedef  int /*<<< orphan*/  lcname ;

/* Variables and functions */
 int EINVAL ; 
 int MAXLOGNAME ; 
 int /*<<< orphan*/  PRIV_PROC_SETLOGINCLASS ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 struct ucred* crcopysafe (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct ucred* crget () ; 
 int /*<<< orphan*/  crhold (struct ucred*) ; 
 struct loginclass* loginclass_find (char*) ; 
 int /*<<< orphan*/  loginclass_free (struct loginclass*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_set_cred (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  racct_proc_ucred_changed (struct proc*,struct ucred*,struct ucred*) ; 
 int /*<<< orphan*/  rctl_proc_ucred_changed (struct proc*,struct ucred*) ; 

int
sys_setloginclass(struct thread *td, struct setloginclass_args *uap)
{
	struct proc *p = td->td_proc;
	int error;
	char lcname[MAXLOGNAME];
	struct loginclass *newlc;
	struct ucred *newcred, *oldcred;

	error = priv_check(td, PRIV_PROC_SETLOGINCLASS);
	if (error != 0)
		return (error);
	error = copyinstr(uap->namebuf, lcname, sizeof(lcname), NULL);
	if (error != 0)
		return (error);

	newlc = loginclass_find(lcname);
	if (newlc == NULL)
		return (EINVAL);
	newcred = crget();

	PROC_LOCK(p);
	oldcred = crcopysafe(p, newcred);
	newcred->cr_loginclass = newlc;
	proc_set_cred(p, newcred);
#ifdef RACCT
	racct_proc_ucred_changed(p, oldcred, newcred);
	crhold(newcred);
#endif
	PROC_UNLOCK(p);
#ifdef RCTL
	rctl_proc_ucred_changed(p, newcred);
	crfree(newcred);
#endif
	loginclass_free(oldcred->cr_loginclass);
	crfree(oldcred);

	return (0);
}