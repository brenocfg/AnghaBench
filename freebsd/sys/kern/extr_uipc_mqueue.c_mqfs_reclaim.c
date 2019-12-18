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
struct vop_reclaim_args {struct vnode* a_vp; } ;
struct vnode {struct mqfs_vdata* v_data; int /*<<< orphan*/  v_mount; } ;
struct mqfs_vdata {struct mqfs_node* mv_node; } ;
struct mqfs_node {int dummy; } ;
struct mqfs_info {int /*<<< orphan*/  mi_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct mqfs_vdata*,int /*<<< orphan*/ ) ; 
 struct mqfs_info* VFSTOMQFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mqnode_release (struct mqfs_node*) ; 
 int /*<<< orphan*/  mv_link ; 
 int /*<<< orphan*/  mvdata_zone ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct mqfs_vdata*) ; 

__attribute__((used)) static int
mqfs_reclaim(struct vop_reclaim_args *ap)
{
	struct mqfs_info *mqfs = VFSTOMQFS(ap->a_vp->v_mount);
	struct vnode *vp = ap->a_vp;
	struct mqfs_node *pn;
	struct mqfs_vdata *vd;

	vd = vp->v_data;
	pn = vd->mv_node;
	sx_xlock(&mqfs->mi_lock);
	vp->v_data = NULL;
	LIST_REMOVE(vd, mv_link);
	uma_zfree(mvdata_zone, vd);
	mqnode_release(pn);
	sx_xunlock(&mqfs->mi_lock);
	return (0);
}