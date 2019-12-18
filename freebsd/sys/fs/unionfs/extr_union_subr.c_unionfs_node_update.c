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
struct vnode {scalar_t__ v_type; TYPE_1__* v_vnlock; } ;
struct unionfs_node_hashhead {int dummy; } ;
struct unionfs_node {int /*<<< orphan*/ * un_path; struct vnode* un_uppervp; struct vnode* un_dvp; struct vnode* un_lowervp; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {unsigned int lk_recurse; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct unionfs_node_hashhead*,struct unionfs_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct unionfs_node*,int /*<<< orphan*/ ) ; 
 int LK_CANRECURSE ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 struct vnode* NULLVP ; 
 struct vnode* UNIONFSTOV (struct unionfs_node*) ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  un_hash ; 
 struct unionfs_node_hashhead* unionfs_get_hashhead (struct vnode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static void
unionfs_node_update(struct unionfs_node *unp, struct vnode *uvp,
		    struct thread *td)
{
	unsigned	count, lockrec;
	struct vnode   *vp;
	struct vnode   *lvp;
	struct vnode   *dvp;

	vp = UNIONFSTOV(unp);
	lvp = unp->un_lowervp;
	ASSERT_VOP_ELOCKED(lvp, "unionfs_node_update");
	dvp = unp->un_dvp;

	/*
	 * lock update
	 */
	VI_LOCK(vp);
	unp->un_uppervp = uvp;
	vp->v_vnlock = uvp->v_vnlock;
	VI_UNLOCK(vp);
	lockrec = lvp->v_vnlock->lk_recurse;
	for (count = 0; count < lockrec; count++)
		vn_lock(uvp, LK_EXCLUSIVE | LK_CANRECURSE | LK_RETRY);

	/*
	 * cache update
	 */
	if (unp->un_path != NULL && dvp != NULLVP && vp->v_type == VDIR) {
		static struct unionfs_node_hashhead *hd;

		VI_LOCK(dvp);
		hd = unionfs_get_hashhead(dvp, unp->un_path);
		LIST_REMOVE(unp, un_hash);
		LIST_INSERT_HEAD(hd, unp, un_hash);
		VI_UNLOCK(dvp);
	}
}