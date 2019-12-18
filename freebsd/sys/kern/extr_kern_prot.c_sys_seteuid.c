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
struct seteuid_args {scalar_t__ euid; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_EUID (scalar_t__) ; 
 int /*<<< orphan*/  PRIV_CRED_SETEUID ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  change_euid (struct ucred*,struct uidinfo*) ; 
 struct ucred* crcopysafe (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct ucred* crget () ; 
 int mac_cred_check_seteuid (struct ucred*,scalar_t__) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_set_cred (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  setsugid (struct proc*) ; 
 struct uidinfo* uifind (scalar_t__) ; 
 int /*<<< orphan*/  uifree (struct uidinfo*) ; 

int
sys_seteuid(struct thread *td, struct seteuid_args *uap)
{
	struct proc *p = td->td_proc;
	struct ucred *newcred, *oldcred;
	uid_t euid;
	struct uidinfo *euip;
	int error;

	euid = uap->euid;
	AUDIT_ARG_EUID(euid);
	newcred = crget();
	euip = uifind(euid);
	PROC_LOCK(p);
	/*
	 * Copy credentials so other references do not see our changes.
	 */
	oldcred = crcopysafe(p, newcred);

#ifdef MAC
	error = mac_cred_check_seteuid(oldcred, euid);
	if (error)
		goto fail;
#endif

	if (euid != oldcred->cr_ruid &&		/* allow seteuid(getuid()) */
	    euid != oldcred->cr_svuid &&	/* allow seteuid(saved uid) */
	    (error = priv_check_cred(oldcred, PRIV_CRED_SETEUID)) != 0)
		goto fail;

	/*
	 * Everything's okay, do it.
	 */
	if (oldcred->cr_uid != euid) {
		change_euid(newcred, euip);
		setsugid(p);
	}
	proc_set_cred(p, newcred);
	PROC_UNLOCK(p);
	uifree(euip);
	crfree(oldcred);
	return (0);

fail:
	PROC_UNLOCK(p);
	uifree(euip);
	crfree(newcred);
	return (error);
}