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
struct vattr {scalar_t__ va_size; } ;
struct ucred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_CLOSE_FLAGS ; 
 int /*<<< orphan*/  AUDIT_WORKER_LOCK () ; 
 int /*<<< orphan*/  AUDIT_WORKER_UNLOCK () ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 scalar_t__ VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 struct ucred* audit_cred ; 
 scalar_t__ audit_file_rotate_wait ; 
 scalar_t__ audit_size ; 
 int /*<<< orphan*/  audit_syscalls_enabled_update () ; 
 int /*<<< orphan*/  audit_trail_enabled ; 
 struct vnode* audit_vp ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  vn_close (struct vnode*,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

void
audit_rotate_vnode(struct ucred *cred, struct vnode *vp)
{
	struct ucred *old_audit_cred;
	struct vnode *old_audit_vp;
	struct vattr vattr;

	KASSERT((cred != NULL && vp != NULL) || (cred == NULL && vp == NULL),
	    ("audit_rotate_vnode: cred %p vp %p", cred, vp));

	if (vp != NULL) {
		vn_lock(vp, LK_SHARED | LK_RETRY);
		if (VOP_GETATTR(vp, &vattr, cred) != 0)
			vattr.va_size = 0;
		VOP_UNLOCK(vp, 0);
	} else {
		vattr.va_size = 0;
	}

	/*
	 * Rotate the vnode/cred, and clear the rotate flag so that we will
	 * send a rotate trigger if the new file fills.
	 */
	AUDIT_WORKER_LOCK();
	old_audit_cred = audit_cred;
	old_audit_vp = audit_vp;
	audit_cred = cred;
	audit_vp = vp;
	audit_size = vattr.va_size;
	audit_file_rotate_wait = 0;
	audit_trail_enabled = (audit_vp != NULL);
	audit_syscalls_enabled_update();
	AUDIT_WORKER_UNLOCK();

	/*
	 * If there was an old vnode/credential, close and free.
	 */
	if (old_audit_vp != NULL) {
		vn_close(old_audit_vp, AUDIT_CLOSE_FLAGS, old_audit_cred,
		    curthread);
		crfree(old_audit_cred);
	}
}