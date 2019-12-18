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
struct vop_fsync_args {int /*<<< orphan*/  a_waitfor; struct vnode* a_vp; } ;
struct TYPE_2__ {scalar_t__ bv_cnt; } ;
struct bufobj {scalar_t__ bo_numoutput; TYPE_1__ bo_dirty; } ;
struct vnode {scalar_t__ v_type; struct bufobj v_bufobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_LOCK (struct bufobj*) ; 
 int /*<<< orphan*/  BO_UNLOCK (struct bufobj*) ; 
 scalar_t__ DOINGSOFTDEP (struct vnode*) ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 scalar_t__ VDIR ; 
 scalar_t__ VREG ; 
 int ffs_syncvnode (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int softdep_fsync (struct vnode*) ; 

__attribute__((used)) static int
ffs_fsync(struct vop_fsync_args *ap)
{
	struct vnode *vp;
	struct bufobj *bo;
	int error;

	vp = ap->a_vp;
	bo = &vp->v_bufobj;
retry:
	error = ffs_syncvnode(vp, ap->a_waitfor, 0);
	if (error)
		return (error);
	if (ap->a_waitfor == MNT_WAIT && DOINGSOFTDEP(vp)) {
		error = softdep_fsync(vp);
		if (error)
			return (error);

		/*
		 * The softdep_fsync() function may drop vp lock,
		 * allowing for dirty buffers to reappear on the
		 * bo_dirty list. Recheck and resync as needed.
		 */
		BO_LOCK(bo);
		if ((vp->v_type == VREG || vp->v_type == VDIR) &&
		    (bo->bo_numoutput > 0 || bo->bo_dirty.bv_cnt > 0)) {
			BO_UNLOCK(bo);
			goto retry;
		}
		BO_UNLOCK(bo);
	}
	return (0);
}