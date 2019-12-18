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
struct vattr {int /*<<< orphan*/  va_rdev; int /*<<< orphan*/  va_mode; int /*<<< orphan*/  va_type; } ;
struct tmpfs_node {scalar_t__ tn_links; int /*<<< orphan*/  tn_gid; } ;
struct tmpfs_mount {int dummy; } ;
struct tmpfs_dirent {int dummy; } ;
struct componentname {int cn_flags; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; TYPE_1__* cn_cred; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int EMLINK ; 
 int HASBUF ; 
 int ISWHITEOUT ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ TMPFS_LINK_MAX ; 
 int /*<<< orphan*/  VDIR ; 
 struct tmpfs_mount* VFS_TO_TMPFS (int /*<<< orphan*/ ) ; 
 struct tmpfs_node* VP_TO_TMPFS_DIR (struct vnode*) ; 
 int tmpfs_alloc_dirent (struct tmpfs_mount*,struct tmpfs_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tmpfs_dirent**) ; 
 int tmpfs_alloc_node (int /*<<< orphan*/ ,struct tmpfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tmpfs_node*,char const*,int /*<<< orphan*/ ,struct tmpfs_node**) ; 
 int tmpfs_alloc_vp (int /*<<< orphan*/ ,struct tmpfs_node*,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  tmpfs_dir_attach (struct vnode*,struct tmpfs_dirent*) ; 
 int /*<<< orphan*/  tmpfs_dir_whiteout_remove (struct vnode*,struct componentname*) ; 
 int /*<<< orphan*/  tmpfs_free_dirent (struct tmpfs_mount*,struct tmpfs_dirent*) ; 
 int /*<<< orphan*/  tmpfs_free_node (struct tmpfs_mount*,struct tmpfs_node*) ; 

int
tmpfs_alloc_file(struct vnode *dvp, struct vnode **vpp, struct vattr *vap,
    struct componentname *cnp, const char *target)
{
	int error;
	struct tmpfs_dirent *de;
	struct tmpfs_mount *tmp;
	struct tmpfs_node *dnode;
	struct tmpfs_node *node;
	struct tmpfs_node *parent;

	ASSERT_VOP_ELOCKED(dvp, "tmpfs_alloc_file");
	MPASS(cnp->cn_flags & HASBUF);

	tmp = VFS_TO_TMPFS(dvp->v_mount);
	dnode = VP_TO_TMPFS_DIR(dvp);
	*vpp = NULL;

	/* If the entry we are creating is a directory, we cannot overflow
	 * the number of links of its parent, because it will get a new
	 * link. */
	if (vap->va_type == VDIR) {
		/* Ensure that we do not overflow the maximum number of links
		 * imposed by the system. */
		MPASS(dnode->tn_links <= TMPFS_LINK_MAX);
		if (dnode->tn_links == TMPFS_LINK_MAX) {
			return (EMLINK);
		}

		parent = dnode;
		MPASS(parent != NULL);
	} else
		parent = NULL;

	/* Allocate a node that represents the new file. */
	error = tmpfs_alloc_node(dvp->v_mount, tmp, vap->va_type,
	    cnp->cn_cred->cr_uid, dnode->tn_gid, vap->va_mode, parent,
	    target, vap->va_rdev, &node);
	if (error != 0)
		return (error);

	/* Allocate a directory entry that points to the new file. */
	error = tmpfs_alloc_dirent(tmp, node, cnp->cn_nameptr, cnp->cn_namelen,
	    &de);
	if (error != 0) {
		tmpfs_free_node(tmp, node);
		return (error);
	}

	/* Allocate a vnode for the new file. */
	error = tmpfs_alloc_vp(dvp->v_mount, node, LK_EXCLUSIVE, vpp);
	if (error != 0) {
		tmpfs_free_dirent(tmp, de);
		tmpfs_free_node(tmp, node);
		return (error);
	}

	/* Now that all required items are allocated, we can proceed to
	 * insert the new node into the directory, an operation that
	 * cannot fail. */
	if (cnp->cn_flags & ISWHITEOUT)
		tmpfs_dir_whiteout_remove(dvp, cnp);
	tmpfs_dir_attach(dvp, de);
	return (0);
}