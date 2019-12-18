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
struct vop_read_args {struct uio* a_uio; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_mount; } ;
struct uio {scalar_t__ uio_offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  tn_aobj; } ;
struct tmpfs_node {int /*<<< orphan*/  tn_size; TYPE_1__ tn_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISDIR ; 
 int /*<<< orphan*/  TMPFS_NODE_ACCESSED ; 
 int /*<<< orphan*/  VFS_TO_TMPFS (int /*<<< orphan*/ ) ; 
 struct tmpfs_node* VP_TO_TMPFS_NODE (struct vnode*) ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  tmpfs_set_status (int /*<<< orphan*/ ,struct tmpfs_node*,int /*<<< orphan*/ ) ; 
 int uiomove_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio*) ; 

__attribute__((used)) static int
tmpfs_read(struct vop_read_args *v)
{
	struct vnode *vp;
	struct uio *uio;
	struct tmpfs_node *node;

	vp = v->a_vp;
	if (vp->v_type != VREG)
		return (EISDIR);
	uio = v->a_uio;
	if (uio->uio_offset < 0)
		return (EINVAL);
	node = VP_TO_TMPFS_NODE(vp);
	tmpfs_set_status(VFS_TO_TMPFS(vp->v_mount), node, TMPFS_NODE_ACCESSED);
	return (uiomove_object(node->tn_reg.tn_aobj, node->tn_size, uio));
}