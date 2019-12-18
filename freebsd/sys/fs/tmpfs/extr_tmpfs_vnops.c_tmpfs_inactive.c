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
struct vop_inactive_args {struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct tmpfs_node {scalar_t__ tn_links; } ;

/* Variables and functions */
 struct tmpfs_node* VP_TO_TMPFS_NODE (struct vnode*) ; 
 int /*<<< orphan*/  tmpfs_check_mtime (struct vnode*) ; 
 int /*<<< orphan*/  vrecycle (struct vnode*) ; 

__attribute__((used)) static int
tmpfs_inactive(struct vop_inactive_args *v)
{
	struct vnode *vp;
	struct tmpfs_node *node;

	vp = v->a_vp;
	node = VP_TO_TMPFS_NODE(vp);
	if (node->tn_links == 0)
		vrecycle(vp);
	else
		tmpfs_check_mtime(vp);
	return (0);
}