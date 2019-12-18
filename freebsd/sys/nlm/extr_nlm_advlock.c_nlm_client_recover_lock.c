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
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct thread {struct ucred* td_ucred; } ;
struct nlm_recovery_context {int nr_state; int /*<<< orphan*/  nr_host; } ;
struct flock {int dummy; } ;

/* Variables and functions */
 int ERESTART ; 
 int /*<<< orphan*/  F_REMOTE ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  LK_SHARED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct thread* curthread ; 
 int nlm_advlock_internal (struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct flock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlm_host_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_set_creds_for_lock (struct thread*,struct flock*) ; 
 int vn_lock (struct vnode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nlm_client_recover_lock(struct vnode *vp, struct flock *fl, void *arg)
{
	struct nlm_recovery_context *nr = (struct nlm_recovery_context *) arg;
	struct thread *td = curthread;
	struct ucred *oldcred;
	int state, error;

	/*
	 * If the remote NSM state changes during recovery, the host
	 * must have rebooted a second time. In that case, we must
	 * restart the recovery.
	 */
	state = nlm_host_get_state(nr->nr_host);
	if (nr->nr_state != state)
		return (ERESTART);

	error = vn_lock(vp, LK_SHARED);
	if (error)
		return (error);

	oldcred = td->td_ucred;
	nlm_set_creds_for_lock(td, fl);

	error = nlm_advlock_internal(vp, NULL, F_SETLK, fl, F_REMOTE,
	    TRUE, TRUE);

	crfree(td->td_ucred);
	td->td_ucred = oldcred;

	return (error);
}