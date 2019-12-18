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
struct vop_reclaim_args {struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/ * v_data; int /*<<< orphan*/ * v_object; int /*<<< orphan*/  v_mount; } ;
struct TYPE_2__ {int /*<<< orphan*/  tn_aobj; } ;
struct tmpfs_node {scalar_t__ tn_links; int tn_vpstate; TYPE_1__ tn_reg; } ;
struct tmpfs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMPFS_NODE_LOCK (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_NODE_UNLOCK (struct tmpfs_node*) ; 
 int TMPFS_VNODE_ALLOCATING ; 
 int TMPFS_VNODE_DOOMED ; 
 struct tmpfs_mount* VFS_TO_TMPFS (int /*<<< orphan*/ ) ; 
 struct tmpfs_node* VP_TO_TMPFS_NODE (struct vnode*) ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  cache_purge (struct vnode*) ; 
 int /*<<< orphan*/  tmpfs_destroy_vobject (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmpfs_free_node (struct tmpfs_mount*,struct tmpfs_node*) ; 
 int /*<<< orphan*/  tmpfs_free_vp (struct vnode*) ; 
 scalar_t__ tmpfs_use_nc (struct vnode*) ; 

int
tmpfs_reclaim(struct vop_reclaim_args *v)
{
	struct vnode *vp = v->a_vp;

	struct tmpfs_mount *tmp;
	struct tmpfs_node *node;

	node = VP_TO_TMPFS_NODE(vp);
	tmp = VFS_TO_TMPFS(vp->v_mount);

	if (vp->v_type == VREG)
		tmpfs_destroy_vobject(vp, node->tn_reg.tn_aobj);
	vp->v_object = NULL;
	if (tmpfs_use_nc(vp))
		cache_purge(vp);

	TMPFS_NODE_LOCK(node);
	tmpfs_free_vp(vp);

	/* If the node referenced by this vnode was deleted by the user,
	 * we must free its associated data structures (now that the vnode
	 * is being reclaimed). */
	if (node->tn_links == 0 &&
	    (node->tn_vpstate & TMPFS_VNODE_ALLOCATING) == 0) {
		node->tn_vpstate = TMPFS_VNODE_DOOMED;
		TMPFS_NODE_UNLOCK(node);
		tmpfs_free_node(tmp, node);
	} else
		TMPFS_NODE_UNLOCK(node);

	MPASS(vp->v_data == NULL);
	return 0;
}