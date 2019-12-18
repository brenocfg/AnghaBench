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
struct vnode {int v_iflag; struct autofs_node* v_data; int /*<<< orphan*/  v_vflag; int /*<<< orphan*/  v_type; } ;
struct mount {int dummy; } ;
struct autofs_node {int /*<<< orphan*/  an_vnode_lock; struct vnode* an_vnode; int /*<<< orphan*/ * an_parent; int /*<<< orphan*/  an_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_ASSERT_UNLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUTOFS_DEBUG (char*,...) ; 
 int /*<<< orphan*/  AUTOFS_WARN (char*,int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  VDIR ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VN_LOCK_ASHARE (struct vnode*) ; 
 int /*<<< orphan*/  VV_ROOT ; 
 int /*<<< orphan*/  autofs_vnodeops ; 
 int /*<<< orphan*/  curthread ; 
 int getnewvnode (char*,struct mount*,int /*<<< orphan*/ *,struct vnode**) ; 
 int insmntque (struct vnode*,struct mount*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int vget (struct vnode*,int,int /*<<< orphan*/ ) ; 
 int vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

int
autofs_node_vn(struct autofs_node *anp, struct mount *mp, int flags,
    struct vnode **vpp)
{
	struct vnode *vp;
	int error;

	AUTOFS_ASSERT_UNLOCKED(anp->an_mount);

	sx_xlock(&anp->an_vnode_lock);

	vp = anp->an_vnode;
	if (vp != NULL) {
		error = vget(vp, flags | LK_RETRY, curthread);
		if (error != 0) {
			AUTOFS_WARN("vget failed with error %d", error);
			sx_xunlock(&anp->an_vnode_lock);
			return (error);
		}
		if (vp->v_iflag & VI_DOOMED) {
			/*
			 * We got forcibly unmounted.
			 */
			AUTOFS_DEBUG("doomed vnode");
			sx_xunlock(&anp->an_vnode_lock);
			vput(vp);

			return (ENOENT);
		}

		*vpp = vp;
		sx_xunlock(&anp->an_vnode_lock);
		return (0);
	}

	error = getnewvnode("autofs", mp, &autofs_vnodeops, &vp);
	if (error != 0) {
		sx_xunlock(&anp->an_vnode_lock);
		return (error);
	}

	error = vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	if (error != 0) {
		sx_xunlock(&anp->an_vnode_lock);
		vdrop(vp);
		return (error);
	}

	vp->v_type = VDIR;
	if (anp->an_parent == NULL)
		vp->v_vflag |= VV_ROOT;
	vp->v_data = anp;

	VN_LOCK_ASHARE(vp);

	error = insmntque(vp, mp);
	if (error != 0) {
		AUTOFS_DEBUG("insmntque() failed with error %d", error);
		sx_xunlock(&anp->an_vnode_lock);
		return (error);
	}

	KASSERT(anp->an_vnode == NULL, ("lost race"));
	anp->an_vnode = vp;

	sx_xunlock(&anp->an_vnode_lock);

	*vpp = vp;
	return (0);
}