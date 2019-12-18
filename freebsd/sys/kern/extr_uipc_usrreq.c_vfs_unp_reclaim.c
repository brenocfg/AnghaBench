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
struct vnode {scalar_t__ v_type; } ;
struct unpcb {struct vnode* unp_vnode; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  UNP_PCB_LOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK (struct unpcb*) ; 
 int /*<<< orphan*/  VOP_UNP_CONNECT (struct vnode*,struct unpcb**) ; 
 int /*<<< orphan*/  VOP_UNP_DETACH (struct vnode*) ; 
 scalar_t__ VSOCK ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 struct mtx* mtx_pool_find (int /*<<< orphan*/ ,struct vnode*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  mtxpool_sleep ; 
 int /*<<< orphan*/  vunref (struct vnode*) ; 

void
vfs_unp_reclaim(struct vnode *vp)
{
	struct unpcb *unp;
	int active;
	struct mtx *vplock;

	ASSERT_VOP_ELOCKED(vp, "vfs_unp_reclaim");
	KASSERT(vp->v_type == VSOCK,
	    ("vfs_unp_reclaim: vp->v_type != VSOCK"));

	active = 0;
	vplock = mtx_pool_find(mtxpool_sleep, vp);
	mtx_lock(vplock);
	VOP_UNP_CONNECT(vp, &unp);
	if (unp == NULL)
		goto done;
	UNP_PCB_LOCK(unp);
	if (unp->unp_vnode == vp) {
		VOP_UNP_DETACH(vp);
		unp->unp_vnode = NULL;
		active = 1;
	}
	UNP_PCB_UNLOCK(unp);
 done:
	mtx_unlock(vplock);
	if (active)
		vunref(vp);
}