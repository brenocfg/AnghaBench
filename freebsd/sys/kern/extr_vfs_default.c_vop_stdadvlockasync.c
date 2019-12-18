#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vop_advlockasync_args {TYPE_1__* a_fl; struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/  v_lockf; } ;
struct vattr {scalar_t__ va_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_ucred; } ;
struct TYPE_3__ {scalar_t__ l_whence; } ;

/* Variables and functions */
 int LK_RETRY ; 
 int LK_SHARED ; 
 scalar_t__ SEEK_END ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 TYPE_2__* curthread ; 
 int lf_advlockasync (struct vop_advlockasync_args*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

int
vop_stdadvlockasync(struct vop_advlockasync_args *ap)
{
	struct vnode *vp;
	struct vattr vattr;
	int error;

	vp = ap->a_vp;
	if (ap->a_fl->l_whence == SEEK_END) {
		/* The size argument is only needed for SEEK_END. */
		vn_lock(vp, LK_SHARED | LK_RETRY);
		error = VOP_GETATTR(vp, &vattr, curthread->td_ucred);
		VOP_UNLOCK(vp, 0);
		if (error)
			return (error);
	} else
		vattr.va_size = 0;

	return (lf_advlockasync(ap, &(vp->v_lockf), vattr.va_size));
}