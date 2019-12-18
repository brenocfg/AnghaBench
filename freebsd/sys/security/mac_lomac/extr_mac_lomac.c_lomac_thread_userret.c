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
struct ucred {int /*<<< orphan*/  cr_label; } ;
struct thread {struct proc* td_proc; } ;
struct proc {struct ucred* p_ucred; int /*<<< orphan*/  p_label; } ;
struct TYPE_2__ {int ml_flags; } ;
struct mac_lomac_proc {int /*<<< orphan*/  mtx; TYPE_1__ mac_lomac; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int MAC_LOMAC_FLAG_UPDATE ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct mac_lomac_proc* PSLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crcopy (struct ucred*,struct ucred*) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct ucred* crget () ; 
 int /*<<< orphan*/  crhold (struct ucred*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  lomac_copy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_proc_vm_revoke (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_set_cred (struct proc*,struct ucred*) ; 

__attribute__((used)) static void
lomac_thread_userret(struct thread *td)
{
	struct proc *p = td->td_proc;
	struct mac_lomac_proc *subj = PSLOT(p->p_label);
	struct ucred *newcred, *oldcred;
	int dodrop;

	mtx_lock(&subj->mtx);
	if (subj->mac_lomac.ml_flags & MAC_LOMAC_FLAG_UPDATE) {
		dodrop = 0;
		mtx_unlock(&subj->mtx);
		newcred = crget();
		/*
		 * Prevent a lock order reversal in mac_proc_vm_revoke;
		 * ideally, the other user of subj->mtx wouldn't be holding
		 * Giant.
		 */
		mtx_lock(&Giant);
		PROC_LOCK(p);
		mtx_lock(&subj->mtx);
		/*
		 * Check if we lost the race while allocating the cred.
		 */
		if ((subj->mac_lomac.ml_flags & MAC_LOMAC_FLAG_UPDATE) == 0) {
			crfree(newcred);
			goto out;
		}
		oldcred = p->p_ucred;
		crcopy(newcred, oldcred);
		crhold(newcred);
		lomac_copy(&subj->mac_lomac, SLOT(newcred->cr_label));
		proc_set_cred(p, newcred);
		crfree(oldcred);
		dodrop = 1;
	out:
		mtx_unlock(&subj->mtx);
		PROC_UNLOCK(p);
		if (dodrop)
			mac_proc_vm_revoke(curthread);
		mtx_unlock(&Giant);
	} else {
		mtx_unlock(&subj->mtx);
	}
}