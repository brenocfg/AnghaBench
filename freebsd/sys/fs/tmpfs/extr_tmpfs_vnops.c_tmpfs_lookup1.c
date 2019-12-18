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
struct TYPE_2__ {struct tmpfs_node* tn_parent; } ;
struct tmpfs_node {scalar_t__ tn_type; int tn_mode; TYPE_1__ tn_dir; } ;
struct tmpfs_mount {int dummy; } ;
struct tmpfs_dirent {struct tmpfs_node* td_node; } ;
struct componentname {int cn_flags; int cn_namelen; char* cn_nameptr; scalar_t__ cn_nameiop; int /*<<< orphan*/  cn_lkflags; int /*<<< orphan*/  cn_thread; int /*<<< orphan*/  cn_cred; } ;

/* Variables and functions */
 scalar_t__ CREATE ; 
 scalar_t__ DELETE ; 
 int DOWHITEOUT ; 
 int EJUSTRETURN ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int EPERM ; 
 int /*<<< orphan*/  IFF (int,int) ; 
 int /*<<< orphan*/  IMPLIES (int,int) ; 
 int ISDOTDOT ; 
 int ISLASTCN ; 
 int ISWHITEOUT ; 
 int MAKEENTRY ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 struct vnode* NULLVP ; 
 scalar_t__ RENAME ; 
 int SAVENAME ; 
 int S_ISTXT ; 
 int /*<<< orphan*/  TMPFS_ASSERT_LOCKED (struct tmpfs_node*) ; 
 int /*<<< orphan*/  VADMIN ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VEXEC ; 
 struct tmpfs_mount* VFS_TO_TMPFS (int /*<<< orphan*/ ) ; 
 scalar_t__ VLNK ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VOP_ISLOCKED (struct vnode*) ; 
 struct tmpfs_node* VP_TO_TMPFS_DIR (struct vnode*) ; 
 int /*<<< orphan*/  VREF (struct vnode*) ; 
 int /*<<< orphan*/  VWRITE ; 
 int /*<<< orphan*/  cache_enter (struct vnode*,struct vnode*,struct componentname*) ; 
 int tmpfs_alloc_vp (int /*<<< orphan*/ ,struct tmpfs_node*,int /*<<< orphan*/ ,struct vnode**) ; 
 struct tmpfs_dirent* tmpfs_dir_lookup (struct tmpfs_node*,int /*<<< orphan*/ *,struct componentname*) ; 
 int /*<<< orphan*/  tmpfs_free_node (struct tmpfs_mount*,struct tmpfs_node*) ; 
 int /*<<< orphan*/  tmpfs_ref_node (struct tmpfs_node*) ; 
 scalar_t__ tmpfs_use_nc (struct vnode*) ; 
 int /*<<< orphan*/  tmpfs_vn_get_ino_alloc ; 
 int vn_vget_ino_gen (struct vnode*,int /*<<< orphan*/ ,struct tmpfs_node*,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static int
tmpfs_lookup1(struct vnode *dvp, struct vnode **vpp, struct componentname *cnp)
{
	struct tmpfs_dirent *de;
	struct tmpfs_node *dnode, *pnode;
	struct tmpfs_mount *tm;
	int error;

	dnode = VP_TO_TMPFS_DIR(dvp);
	*vpp = NULLVP;

	/* Check accessibility of requested node as a first step. */
	error = VOP_ACCESS(dvp, VEXEC, cnp->cn_cred, cnp->cn_thread);
	if (error != 0)
		goto out;

	/* We cannot be requesting the parent directory of the root node. */
	MPASS(IMPLIES(dnode->tn_type == VDIR &&
	    dnode->tn_dir.tn_parent == dnode,
	    !(cnp->cn_flags & ISDOTDOT)));

	TMPFS_ASSERT_LOCKED(dnode);
	if (dnode->tn_dir.tn_parent == NULL) {
		error = ENOENT;
		goto out;
	}
	if (cnp->cn_flags & ISDOTDOT) {
		tm = VFS_TO_TMPFS(dvp->v_mount);
		pnode = dnode->tn_dir.tn_parent;
		tmpfs_ref_node(pnode);
		error = vn_vget_ino_gen(dvp, tmpfs_vn_get_ino_alloc,
		    pnode, cnp->cn_lkflags, vpp);
		tmpfs_free_node(tm, pnode);
		if (error != 0)
			goto out;
	} else if (cnp->cn_namelen == 1 && cnp->cn_nameptr[0] == '.') {
		VREF(dvp);
		*vpp = dvp;
		error = 0;
	} else {
		de = tmpfs_dir_lookup(dnode, NULL, cnp);
		if (de != NULL && de->td_node == NULL)
			cnp->cn_flags |= ISWHITEOUT;
		if (de == NULL || de->td_node == NULL) {
			/*
			 * The entry was not found in the directory.
			 * This is OK if we are creating or renaming an
			 * entry and are working on the last component of
			 * the path name.
			 */
			if ((cnp->cn_flags & ISLASTCN) &&
			    (cnp->cn_nameiop == CREATE || \
			    cnp->cn_nameiop == RENAME ||
			    (cnp->cn_nameiop == DELETE &&
			    cnp->cn_flags & DOWHITEOUT &&
			    cnp->cn_flags & ISWHITEOUT))) {
				error = VOP_ACCESS(dvp, VWRITE, cnp->cn_cred,
				    cnp->cn_thread);
				if (error != 0)
					goto out;

				/*
				 * Keep the component name in the buffer for
				 * future uses.
				 */
				cnp->cn_flags |= SAVENAME;

				error = EJUSTRETURN;
			} else
				error = ENOENT;
		} else {
			struct tmpfs_node *tnode;

			/*
			 * The entry was found, so get its associated
			 * tmpfs_node.
			 */
			tnode = de->td_node;

			/*
			 * If we are not at the last path component and
			 * found a non-directory or non-link entry (which
			 * may itself be pointing to a directory), raise
			 * an error.
			 */
			if ((tnode->tn_type != VDIR &&
			    tnode->tn_type != VLNK) &&
			    !(cnp->cn_flags & ISLASTCN)) {
				error = ENOTDIR;
				goto out;
			}

			/*
			 * If we are deleting or renaming the entry, keep
			 * track of its tmpfs_dirent so that it can be
			 * easily deleted later.
			 */
			if ((cnp->cn_flags & ISLASTCN) &&
			    (cnp->cn_nameiop == DELETE ||
			    cnp->cn_nameiop == RENAME)) {
				error = VOP_ACCESS(dvp, VWRITE, cnp->cn_cred,
				    cnp->cn_thread);
				if (error != 0)
					goto out;

				/* Allocate a new vnode on the matching entry. */
				error = tmpfs_alloc_vp(dvp->v_mount, tnode,
				    cnp->cn_lkflags, vpp);
				if (error != 0)
					goto out;

				if ((dnode->tn_mode & S_ISTXT) &&
				  VOP_ACCESS(dvp, VADMIN, cnp->cn_cred,
				  cnp->cn_thread) && VOP_ACCESS(*vpp, VADMIN,
				  cnp->cn_cred, cnp->cn_thread)) {
					error = EPERM;
					vput(*vpp);
					*vpp = NULL;
					goto out;
				}
				cnp->cn_flags |= SAVENAME;
			} else {
				error = tmpfs_alloc_vp(dvp->v_mount, tnode,
				    cnp->cn_lkflags, vpp);
				if (error != 0)
					goto out;
			}
		}
	}

	/*
	 * Store the result of this lookup in the cache.  Avoid this if the
	 * request was for creation, as it does not improve timings on
	 * emprical tests.
	 */
	if ((cnp->cn_flags & MAKEENTRY) != 0 && tmpfs_use_nc(dvp))
		cache_enter(dvp, *vpp, cnp);

out:
	/*
	 * If there were no errors, *vpp cannot be null and it must be
	 * locked.
	 */
	MPASS(IFF(error == 0, *vpp != NULLVP && VOP_ISLOCKED(*vpp)));

	return (error);
}