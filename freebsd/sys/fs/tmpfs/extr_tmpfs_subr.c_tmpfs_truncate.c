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
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct tmpfs_node {scalar_t__ tn_size; int tn_status; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {scalar_t__ tm_maxfilesize; } ;

/* Variables and functions */
 int EFBIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int TMPFS_NODE_CHANGED ; 
 int TMPFS_NODE_MODIFIED ; 
 TYPE_1__* VFS_TO_TMPFS (int /*<<< orphan*/ ) ; 
 struct tmpfs_node* VP_TO_TMPFS_NODE (struct vnode*) ; 
 int tmpfs_reg_resize (struct vnode*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmpfs_update (struct vnode*) ; 

int
tmpfs_truncate(struct vnode *vp, off_t length)
{
	int error;
	struct tmpfs_node *node;

	node = VP_TO_TMPFS_NODE(vp);

	if (length < 0) {
		error = EINVAL;
		goto out;
	}

	if (node->tn_size == length) {
		error = 0;
		goto out;
	}

	if (length > VFS_TO_TMPFS(vp->v_mount)->tm_maxfilesize)
		return (EFBIG);

	error = tmpfs_reg_resize(vp, length, FALSE);
	if (error == 0)
		node->tn_status |= TMPFS_NODE_CHANGED | TMPFS_NODE_MODIFIED;

out:
	tmpfs_update(vp);

	return (error);
}