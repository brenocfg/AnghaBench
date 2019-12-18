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
struct flock {int /*<<< orphan*/  l_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  F_REMOTE ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct thread* curthread ; 
 int nlm_advlock_internal (struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct flock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_set_creds_for_lock (struct thread*,struct flock*) ; 

__attribute__((used)) static int
nlm_reclaim_free_lock(struct vnode *vp, struct flock *fl, void *arg)
{
	struct flock newfl;
	struct thread *td = curthread;
	struct ucred *oldcred;
	int error;

	newfl = *fl;
	newfl.l_type = F_UNLCK;

	oldcred = td->td_ucred;
	nlm_set_creds_for_lock(td, &newfl);

	error = nlm_advlock_internal(vp, NULL, F_UNLCK, &newfl, F_REMOTE,
	    FALSE, FALSE);

	crfree(td->td_ucred);
	td->td_ucred = oldcred;

	return (error);
}