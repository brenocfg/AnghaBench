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
struct thread {struct ucred* td_ucred; } ;
struct proc {struct ucred* p_ucred; } ;
struct nlm_file_svid {scalar_t__ ns_svid; struct ucred* ns_ucred; } ;
struct flock {scalar_t__ l_pid; } ;

/* Variables and functions */
 struct nlm_file_svid* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct nlm_file_svid* LIST_NEXT (struct nlm_file_svid*,int /*<<< orphan*/ ) ; 
 int NLM_SVID_HASH_SIZE ; 
 scalar_t__ PID_MAX ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct ucred* crhold (struct ucred*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nlm_file_svids ; 
 int /*<<< orphan*/  nlm_svid_lock ; 
 int /*<<< orphan*/  ns_link ; 
 struct proc* pfind (scalar_t__) ; 

__attribute__((used)) static void
nlm_set_creds_for_lock(struct thread *td, struct flock *fl)
{
	int i;
	struct nlm_file_svid *ns;
	struct proc *p;
	struct ucred *cred;

	cred = NULL;
	if (fl->l_pid > PID_MAX) {
		/*
		 * If this was originally a F_FLOCK-style lock, we
		 * recorded the creds used when it was originally
		 * locked in the nlm_file_svid structure.
		 */
		mtx_lock(&nlm_svid_lock);
		for (i = 0; i < NLM_SVID_HASH_SIZE; i++) {
			for (ns = LIST_FIRST(&nlm_file_svids[i]); ns;
			     ns = LIST_NEXT(ns, ns_link)) {
				if (ns->ns_svid == fl->l_pid) {
					cred = crhold(ns->ns_ucred);
					break;
				}
			}
		}
		mtx_unlock(&nlm_svid_lock);
	} else {
		/*
		 * This lock is owned by a process. Get a reference to
		 * the process creds.
		 */
		p = pfind(fl->l_pid);
		if (p) {
			cred = crhold(p->p_ucred);
			PROC_UNLOCK(p);
		}
	}

	/*
	 * If we can't find a cred, fall back on the recovery
	 * thread's cred.
	 */
	if (!cred) {
		cred = crhold(td->td_ucred);
	}

	td->td_ucred = cred;
}