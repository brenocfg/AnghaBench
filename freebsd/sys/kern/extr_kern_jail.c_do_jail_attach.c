#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucred {struct prison* cr_prison; } ;
struct thread {TYPE_1__* td_ucred; struct proc* td_proc; } ;
struct proc {int dummy; } ;
struct prison {int /*<<< orphan*/  pr_root; int /*<<< orphan*/  pr_cpuset; int /*<<< orphan*/  pr_mtx; int /*<<< orphan*/  pr_uref; int /*<<< orphan*/  pr_ref; } ;
struct TYPE_2__ {struct prison* cr_prison; } ;

/* Variables and functions */
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int PD_DEREF ; 
 int PD_DEUREF ; 
 int PD_LIST_SLOCKED ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PR_METHOD_ATTACH ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allprison_lock ; 
 int change_dir (int /*<<< orphan*/ ,struct thread*) ; 
 int cpuset_setproc_update_set (struct proc*,int /*<<< orphan*/ ) ; 
 struct ucred* crcopysafe (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct ucred* crget () ; 
 int /*<<< orphan*/  crhold (struct ucred*) ; 
 int mac_vnode_check_chroot (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int osd_jail_call (struct prison*,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  prison_deref (struct prison*,int) ; 
 int /*<<< orphan*/  proc_set_cred (struct proc*,struct ucred*) ; 
 int pwd_chroot (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  racct_proc_ucred_changed (struct proc*,struct ucred*,struct ucred*) ; 
 int /*<<< orphan*/  rctl_proc_ucred_changed (struct proc*,struct ucred*) ; 
 int /*<<< orphan*/  setsugid (struct proc*) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_lock (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
do_jail_attach(struct thread *td, struct prison *pr)
{
	struct proc *p;
	struct ucred *newcred, *oldcred;
	int error;

	/*
	 * XXX: Note that there is a slight race here if two threads
	 * in the same privileged process attempt to attach to two
	 * different jails at the same time.  It is important for
	 * user processes not to do this, or they might end up with
	 * a process root from one prison, but attached to the jail
	 * of another.
	 */
	pr->pr_ref++;
	pr->pr_uref++;
	mtx_unlock(&pr->pr_mtx);

	/* Let modules do whatever they need to prepare for attaching. */
	error = osd_jail_call(pr, PR_METHOD_ATTACH, td);
	if (error) {
		prison_deref(pr, PD_DEREF | PD_DEUREF | PD_LIST_SLOCKED);
		return (error);
	}
	sx_sunlock(&allprison_lock);

	/*
	 * Reparent the newly attached process to this jail.
	 */
	p = td->td_proc;
	error = cpuset_setproc_update_set(p, pr->pr_cpuset);
	if (error)
		goto e_revert_osd;

	vn_lock(pr->pr_root, LK_EXCLUSIVE | LK_RETRY);
	if ((error = change_dir(pr->pr_root, td)) != 0)
		goto e_unlock;
#ifdef MAC
	if ((error = mac_vnode_check_chroot(td->td_ucred, pr->pr_root)))
		goto e_unlock;
#endif
	VOP_UNLOCK(pr->pr_root, 0);
	if ((error = pwd_chroot(td, pr->pr_root)))
		goto e_revert_osd;

	newcred = crget();
	PROC_LOCK(p);
	oldcred = crcopysafe(p, newcred);
	newcred->cr_prison = pr;
	proc_set_cred(p, newcred);
	setsugid(p);
#ifdef RACCT
	racct_proc_ucred_changed(p, oldcred, newcred);
	crhold(newcred);
#endif
	PROC_UNLOCK(p);
#ifdef RCTL
	rctl_proc_ucred_changed(p, newcred);
	crfree(newcred);
#endif
	prison_deref(oldcred->cr_prison, PD_DEREF | PD_DEUREF);
	crfree(oldcred);
	return (0);

 e_unlock:
	VOP_UNLOCK(pr->pr_root, 0);
 e_revert_osd:
	/* Tell modules this thread is still in its old jail after all. */
	(void)osd_jail_call(td->td_ucred->cr_prison, PR_METHOD_ATTACH, td);
	prison_deref(pr, PD_DEREF | PD_DEUREF);
	return (error);
}