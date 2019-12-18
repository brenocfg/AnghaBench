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
struct ucred {scalar_t__ cr_rgid; scalar_t__ cr_svgid; scalar_t__* cr_groups; } ;
struct thread {struct proc* td_proc; } ;
struct setgid_args {scalar_t__ gid; } ;
struct proc {int dummy; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_GID (scalar_t__) ; 
 int /*<<< orphan*/  PRIV_CRED_SETGID ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  change_egid (struct ucred*,scalar_t__) ; 
 int /*<<< orphan*/  change_rgid (struct ucred*,scalar_t__) ; 
 int /*<<< orphan*/  change_svgid (struct ucred*,scalar_t__) ; 
 struct ucred* crcopysafe (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct ucred* crget () ; 
 int mac_cred_check_setgid (struct ucred*,scalar_t__) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_set_cred (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  setsugid (struct proc*) ; 

int
sys_setgid(struct thread *td, struct setgid_args *uap)
{
	struct proc *p = td->td_proc;
	struct ucred *newcred, *oldcred;
	gid_t gid;
	int error;

	gid = uap->gid;
	AUDIT_ARG_GID(gid);
	newcred = crget();
	PROC_LOCK(p);
	oldcred = crcopysafe(p, newcred);

#ifdef MAC
	error = mac_cred_check_setgid(oldcred, gid);
	if (error)
		goto fail;
#endif

	/*
	 * See if we have "permission" by POSIX 1003.1 rules.
	 *
	 * Note that setgid(getegid()) is a special case of
	 * "appropriate privileges" in appendix B.4.2.2.  We need
	 * to use this clause to be compatible with traditional BSD
	 * semantics.  Basically, it means that "setgid(xx)" sets all
	 * three id's (assuming you have privs).
	 *
	 * For notes on the logic here, see setuid() above.
	 */
	if (gid != oldcred->cr_rgid &&		/* allow setgid(getgid()) */
#ifdef _POSIX_SAVED_IDS
	    gid != oldcred->cr_svgid &&		/* allow setgid(saved gid) */
#endif
#ifdef POSIX_APPENDIX_B_4_2_2	/* Use BSD-compat clause from B.4.2.2 */
	    gid != oldcred->cr_groups[0] && /* allow setgid(getegid()) */
#endif
	    (error = priv_check_cred(oldcred, PRIV_CRED_SETGID)) != 0)
		goto fail;

#ifdef _POSIX_SAVED_IDS
	/*
	 * Do we have "appropriate privileges" (are we root or gid == egid)
	 * If so, we are changing the real uid and saved gid.
	 */
	if (
#ifdef POSIX_APPENDIX_B_4_2_2	/* use the clause from B.4.2.2 */
	    gid == oldcred->cr_groups[0] ||
#endif
	    /* We are using privs. */
	    priv_check_cred(oldcred, PRIV_CRED_SETGID) == 0)
#endif
	{
		/*
		 * Set real gid
		 */
		if (oldcred->cr_rgid != gid) {
			change_rgid(newcred, gid);
			setsugid(p);
		}
		/*
		 * Set saved gid
		 *
		 * XXX always set saved gid even if not _POSIX_SAVED_IDS, as
		 * the security of setegid() depends on it.  B.4.2.2 says it
		 * is important that we should do this.
		 */
		if (oldcred->cr_svgid != gid) {
			change_svgid(newcred, gid);
			setsugid(p);
		}
	}
	/*
	 * In all cases permitted cases, we are changing the egid.
	 * Copy credentials so other references do not see our changes.
	 */
	if (oldcred->cr_groups[0] != gid) {
		change_egid(newcred, gid);
		setsugid(p);
	}
	proc_set_cred(p, newcred);
	PROC_UNLOCK(p);
	crfree(oldcred);
	return (0);

fail:
	PROC_UNLOCK(p);
	crfree(newcred);
	return (error);
}