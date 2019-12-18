#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vop_rmdir_args {TYPE_2__* a_cnp; struct vnode* a_vp; struct vnode* a_dvp; } ;
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct TYPE_4__ {struct tmpfs_node* tn_parent; } ;
struct tmpfs_node {scalar_t__ tn_size; int tn_flags; int tn_status; int /*<<< orphan*/  tn_links; TYPE_1__ tn_dir; } ;
struct tmpfs_mount {int dummy; } ;
struct tmpfs_dirent {int dummy; } ;
struct TYPE_5__ {int cn_flags; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;

/* Variables and functions */
 int APPEND ; 
 int DOWHITEOUT ; 
 int ENOTEMPTY ; 
 int EPERM ; 
 int IMMUTABLE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int NOUNLINK ; 
 int TMPFS_DIRENT_MATCHES (struct tmpfs_dirent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TMPFS_NODE_ACCESSED ; 
 int TMPFS_NODE_CHANGED ; 
 int /*<<< orphan*/  TMPFS_NODE_LOCK (struct tmpfs_node*) ; 
 int TMPFS_NODE_MODIFIED ; 
 int /*<<< orphan*/  TMPFS_NODE_UNLOCK (struct tmpfs_node*) ; 
 struct tmpfs_mount* VFS_TO_TMPFS (int /*<<< orphan*/ ) ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 struct tmpfs_node* VP_TO_TMPFS_DIR (struct vnode*) ; 
 int /*<<< orphan*/  cache_purge (struct vnode*) ; 
 int /*<<< orphan*/  tmpfs_dir_detach (struct vnode*,struct tmpfs_dirent*) ; 
 struct tmpfs_dirent* tmpfs_dir_lookup (struct tmpfs_node*,struct tmpfs_node*,TYPE_2__*) ; 
 int /*<<< orphan*/  tmpfs_dir_whiteout_add (struct vnode*,TYPE_2__*) ; 
 int /*<<< orphan*/  tmpfs_free_dirent (struct tmpfs_mount*,struct tmpfs_dirent*) ; 
 int /*<<< orphan*/  tmpfs_update (struct vnode*) ; 
 scalar_t__ tmpfs_use_nc (struct vnode*) ; 

__attribute__((used)) static int
tmpfs_rmdir(struct vop_rmdir_args *v)
{
	struct vnode *dvp = v->a_dvp;
	struct vnode *vp = v->a_vp;

	int error;
	struct tmpfs_dirent *de;
	struct tmpfs_mount *tmp;
	struct tmpfs_node *dnode;
	struct tmpfs_node *node;

	MPASS(VOP_ISLOCKED(dvp));
	MPASS(VOP_ISLOCKED(vp));

	tmp = VFS_TO_TMPFS(dvp->v_mount);
	dnode = VP_TO_TMPFS_DIR(dvp);
	node = VP_TO_TMPFS_DIR(vp);

	/* Directories with more than two entries ('.' and '..') cannot be
	 * removed. */
	 if (node->tn_size > 0) {
		 error = ENOTEMPTY;
		 goto out;
	 }

	if ((dnode->tn_flags & APPEND)
	    || (node->tn_flags & (NOUNLINK | IMMUTABLE | APPEND))) {
		error = EPERM;
		goto out;
	}

	/* This invariant holds only if we are not trying to remove "..".
	  * We checked for that above so this is safe now. */
	MPASS(node->tn_dir.tn_parent == dnode);

	/* Get the directory entry associated with node (vp).  This was
	 * filled by tmpfs_lookup while looking up the entry. */
	de = tmpfs_dir_lookup(dnode, node, v->a_cnp);
	MPASS(TMPFS_DIRENT_MATCHES(de,
	    v->a_cnp->cn_nameptr,
	    v->a_cnp->cn_namelen));

	/* Check flags to see if we are allowed to remove the directory. */
	if ((dnode->tn_flags & APPEND) != 0 ||
	    (node->tn_flags & (NOUNLINK | IMMUTABLE | APPEND)) != 0) {
		error = EPERM;
		goto out;
	}


	/* Detach the directory entry from the directory (dnode). */
	tmpfs_dir_detach(dvp, de);
	if (v->a_cnp->cn_flags & DOWHITEOUT)
		tmpfs_dir_whiteout_add(dvp, v->a_cnp);

	/* No vnode should be allocated for this entry from this point */
	TMPFS_NODE_LOCK(node);
	node->tn_links--;
	node->tn_dir.tn_parent = NULL;
	node->tn_status |= TMPFS_NODE_ACCESSED | TMPFS_NODE_CHANGED |
	    TMPFS_NODE_MODIFIED;

	TMPFS_NODE_UNLOCK(node);

	TMPFS_NODE_LOCK(dnode);
	dnode->tn_links--;
	dnode->tn_status |= TMPFS_NODE_ACCESSED | TMPFS_NODE_CHANGED |
	    TMPFS_NODE_MODIFIED;
	TMPFS_NODE_UNLOCK(dnode);

	if (tmpfs_use_nc(dvp)) {
		cache_purge(dvp);
		cache_purge(vp);
	}

	/* Free the directory entry we just deleted.  Note that the node
	 * referred by it will not be removed until the vnode is really
	 * reclaimed. */
	tmpfs_free_dirent(tmp, de);

	/* Release the deleted vnode (will destroy the node, notify
	 * interested parties and clean it from the cache). */

	dnode->tn_status |= TMPFS_NODE_CHANGED;
	tmpfs_update(dvp);

	error = 0;

out:
	return error;
}