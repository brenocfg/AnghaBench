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
typedef  scalar_t__ uid_t ;
struct uidinfo {int dummy; } ;
struct ucred {scalar_t__ cr_ruid; scalar_t__ cr_svuid; scalar_t__ cr_uid; } ;
struct thread {struct proc* td_proc; } ;
struct setresuid_args {scalar_t__ euid; scalar_t__ ruid; scalar_t__ suid; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_EUID (scalar_t__) ; 
 int /*<<< orphan*/  AUDIT_ARG_RUID (scalar_t__) ; 
 int /*<<< orphan*/  AUDIT_ARG_SUID (scalar_t__) ; 
 int /*<<< orphan*/  PRIV_CRED_SETRESUID ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  change_euid (struct ucred*,struct uidinfo*) ; 
 int /*<<< orphan*/  change_ruid (struct ucred*,struct uidinfo*) ; 
 int /*<<< orphan*/  change_svuid (struct ucred*,scalar_t__) ; 
 struct ucred* crcopysafe (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct ucred* crget () ; 
 int /*<<< orphan*/  crhold (struct ucred*) ; 
 int mac_cred_check_setresuid (struct ucred*,scalar_t__,scalar_t__,scalar_t__) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_set_cred (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  racct_proc_ucred_changed (struct proc*,struct ucred*,struct ucred*) ; 
 int /*<<< orphan*/  rctl_proc_ucred_changed (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  setsugid (struct proc*) ; 
 struct uidinfo* uifind (scalar_t__) ; 
 int /*<<< orphan*/  uifree (struct uidinfo*) ; 

int
sys_setresuid(struct thread *td, struct setresuid_args *uap)
{
	struct proc *p = td->td_proc;
	struct ucred *newcred, *oldcred;
	uid_t euid, ruid, suid;
	struct uidinfo *euip, *ruip;
	int error;

	euid = uap->euid;
	ruid = uap->ruid;
	suid = uap->suid;
	AUDIT_ARG_EUID(euid);
	AUDIT_ARG_RUID(ruid);
	AUDIT_ARG_SUID(suid);
	newcred = crget();
	euip = uifind(euid);
	ruip = uifind(ruid);
	PROC_LOCK(p);
	oldcred = crcopysafe(p, newcred);

#ifdef MAC
	error = mac_cred_check_setresuid(oldcred, ruid, euid, suid);
	if (error)
		goto fail;
#endif

	if (((ruid != (uid_t)-1 && ruid != oldcred->cr_ruid &&
	     ruid != oldcred->cr_svuid &&
	      ruid != oldcred->cr_uid) ||
	     (euid != (uid_t)-1 && euid != oldcred->cr_ruid &&
	    euid != oldcred->cr_svuid &&
	      euid != oldcred->cr_uid) ||
	     (suid != (uid_t)-1 && suid != oldcred->cr_ruid &&
	    suid != oldcred->cr_svuid &&
	      suid != oldcred->cr_uid)) &&
	    (error = priv_check_cred(oldcred, PRIV_CRED_SETRESUID)) != 0)
		goto fail;

	if (euid != (uid_t)-1 && oldcred->cr_uid != euid) {
		change_euid(newcred, euip);
		setsugid(p);
	}
	if (ruid != (uid_t)-1 && oldcred->cr_ruid != ruid) {
		change_ruid(newcred, ruip);
		setsugid(p);
	}
	if (suid != (uid_t)-1 && oldcred->cr_svuid != suid) {
		change_svuid(newcred, suid);
		setsugid(p);
	}
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
	uifree(ruip);
	uifree(euip);
	crfree(oldcred);
	return (0);

fail:
	PROC_UNLOCK(p);
	uifree(ruip);
	uifree(euip);
	crfree(newcred);
	return (error);

}