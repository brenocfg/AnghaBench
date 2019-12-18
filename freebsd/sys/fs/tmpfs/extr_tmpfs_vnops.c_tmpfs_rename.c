#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vop_rename_args {struct componentname* a_tcnp; struct vnode* a_tvp; struct vnode* a_tdvp; struct componentname* a_fcnp; struct vnode* a_fvp; struct vnode* a_fdvp; } ;
struct vnode {struct mount* v_mount; } ;
struct TYPE_3__ {struct tmpfs_node* tn_parent; } ;
struct tmpfs_node {int tn_flags; scalar_t__ tn_type; scalar_t__ tn_size; int /*<<< orphan*/  tn_status; int /*<<< orphan*/  tn_links; TYPE_1__ tn_dir; } ;
struct tmpfs_mount {int dummy; } ;
struct TYPE_4__ {char* td_name; } ;
struct tmpfs_dirent {TYPE_2__ ud; struct tmpfs_node* td_node; } ;
struct mount {int dummy; } ;
struct componentname {int cn_flags; int cn_namelen; char* cn_nameptr; } ;

/* Variables and functions */
 int APPEND ; 
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int DOWHITEOUT ; 
 int EINVAL ; 
 int EISDIR ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int ENOTEMPTY ; 
 int EPERM ; 
 int EXDEV ; 
 int HASBUF ; 
 int IMMUTABLE ; 
 int IMPLIES (int /*<<< orphan*/ ,int) ; 
 int ISDOTDOT ; 
 int ISWHITEOUT ; 
 int LK_EXCLUSIVE ; 
 int LK_NOWAIT ; 
 int MAXNAMLEN ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_TMPFSNAME ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int NOUNLINK ; 
 int /*<<< orphan*/  TMPFS_ASSERT_LOCKED (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_LOCK (struct tmpfs_mount*) ; 
 int /*<<< orphan*/  TMPFS_NODE_CHANGED ; 
 int /*<<< orphan*/  TMPFS_NODE_LOCK (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_NODE_MODIFIED ; 
 int /*<<< orphan*/  TMPFS_NODE_UNLOCK (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_UNLOCK (struct tmpfs_mount*) ; 
 int /*<<< orphan*/  TMPFS_VALIDATE_DIR (struct tmpfs_node*) ; 
 scalar_t__ VDIR ; 
 struct tmpfs_mount* VFS_TO_TMPFS (struct mount*) ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 struct tmpfs_node* VP_TO_TMPFS_DIR (struct vnode*) ; 
 struct tmpfs_node* VP_TO_TMPFS_NODE (struct vnode*) ; 
 scalar_t__ bcmp (char*,char*,int) ; 
 int /*<<< orphan*/  cache_purge (struct vnode*) ; 
 int /*<<< orphan*/  cache_purge_negative (struct vnode*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmpfs_dir_attach (struct vnode*,struct tmpfs_dirent*) ; 
 int /*<<< orphan*/  tmpfs_dir_detach (struct vnode*,struct tmpfs_dirent*) ; 
 struct tmpfs_dirent* tmpfs_dir_lookup (struct tmpfs_node*,struct tmpfs_node*,struct componentname*) ; 
 int /*<<< orphan*/  tmpfs_dir_whiteout_add (struct vnode*,struct componentname*) ; 
 int /*<<< orphan*/  tmpfs_dir_whiteout_remove (struct vnode*,struct componentname*) ; 
 int /*<<< orphan*/  tmpfs_dirent_init (struct tmpfs_dirent*,char*,int) ; 
 int /*<<< orphan*/  tmpfs_free_dirent (struct tmpfs_mount*,struct tmpfs_dirent*) ; 
 int tmpfs_rename_relock (struct vnode*,struct vnode**,struct vnode*,struct vnode**,struct componentname*,struct componentname*) ; 
 scalar_t__ tmpfs_use_nc (struct vnode*) ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 scalar_t__ vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
tmpfs_rename(struct vop_rename_args *v)
{
	struct vnode *fdvp = v->a_fdvp;
	struct vnode *fvp = v->a_fvp;
	struct componentname *fcnp = v->a_fcnp;
	struct vnode *tdvp = v->a_tdvp;
	struct vnode *tvp = v->a_tvp;
	struct componentname *tcnp = v->a_tcnp;
	struct mount *mp = NULL;
	char *newname;
	struct tmpfs_dirent *de;
	struct tmpfs_mount *tmp;
	struct tmpfs_node *fdnode;
	struct tmpfs_node *fnode;
	struct tmpfs_node *tnode;
	struct tmpfs_node *tdnode;
	int error;

	MPASS(VOP_ISLOCKED(tdvp));
	MPASS(IMPLIES(tvp != NULL, VOP_ISLOCKED(tvp)));
	MPASS(fcnp->cn_flags & HASBUF);
	MPASS(tcnp->cn_flags & HASBUF);

	/*
	 * Disallow cross-device renames.
	 * XXX Why isn't this done by the caller?
	 */
	if (fvp->v_mount != tdvp->v_mount ||
	    (tvp != NULL && fvp->v_mount != tvp->v_mount)) {
		error = EXDEV;
		goto out;
	}

	/* If source and target are the same file, there is nothing to do. */
	if (fvp == tvp) {
		error = 0;
		goto out;
	}

	/*
	 * If we need to move the directory between entries, lock the
	 * source so that we can safely operate on it.
	 */
	if (fdvp != tdvp && fdvp != tvp) {
		if (vn_lock(fdvp, LK_EXCLUSIVE | LK_NOWAIT) != 0) {
			mp = tdvp->v_mount;
			error = vfs_busy(mp, 0);
			if (error != 0) {
				mp = NULL;
				goto out;
			}
			error = tmpfs_rename_relock(fdvp, &fvp, tdvp, &tvp,
			    fcnp, tcnp);
			if (error != 0) {
				vfs_unbusy(mp);
				return (error);
			}
			ASSERT_VOP_ELOCKED(fdvp,
			    "tmpfs_rename: fdvp not locked");
			ASSERT_VOP_ELOCKED(tdvp,
			    "tmpfs_rename: tdvp not locked");
			if (tvp != NULL)
				ASSERT_VOP_ELOCKED(tvp,
				    "tmpfs_rename: tvp not locked");
			if (fvp == tvp) {
				error = 0;
				goto out_locked;
			}
		}
	}

	tmp = VFS_TO_TMPFS(tdvp->v_mount);
	tdnode = VP_TO_TMPFS_DIR(tdvp);
	tnode = (tvp == NULL) ? NULL : VP_TO_TMPFS_NODE(tvp);
	fdnode = VP_TO_TMPFS_DIR(fdvp);
	fnode = VP_TO_TMPFS_NODE(fvp);
	de = tmpfs_dir_lookup(fdnode, fnode, fcnp);

	/*
	 * Entry can disappear before we lock fdvp,
	 * also avoid manipulating '.' and '..' entries.
	 */
	if (de == NULL) {
		if ((fcnp->cn_flags & ISDOTDOT) != 0 ||
		    (fcnp->cn_namelen == 1 && fcnp->cn_nameptr[0] == '.'))
			error = EINVAL;
		else
			error = ENOENT;
		goto out_locked;
	}
	MPASS(de->td_node == fnode);

	/*
	 * If re-naming a directory to another preexisting directory
	 * ensure that the target directory is empty so that its
	 * removal causes no side effects.
	 * Kern_rename guarantees the destination to be a directory
	 * if the source is one.
	 */
	if (tvp != NULL) {
		MPASS(tnode != NULL);

		if ((tnode->tn_flags & (NOUNLINK | IMMUTABLE | APPEND)) ||
		    (tdnode->tn_flags & (APPEND | IMMUTABLE))) {
			error = EPERM;
			goto out_locked;
		}

		if (fnode->tn_type == VDIR && tnode->tn_type == VDIR) {
			if (tnode->tn_size > 0) {
				error = ENOTEMPTY;
				goto out_locked;
			}
		} else if (fnode->tn_type == VDIR && tnode->tn_type != VDIR) {
			error = ENOTDIR;
			goto out_locked;
		} else if (fnode->tn_type != VDIR && tnode->tn_type == VDIR) {
			error = EISDIR;
			goto out_locked;
		} else {
			MPASS(fnode->tn_type != VDIR &&
				tnode->tn_type != VDIR);
		}
	}

	if ((fnode->tn_flags & (NOUNLINK | IMMUTABLE | APPEND))
	    || (fdnode->tn_flags & (APPEND | IMMUTABLE))) {
		error = EPERM;
		goto out_locked;
	}

	/*
	 * Ensure that we have enough memory to hold the new name, if it
	 * has to be changed.
	 */
	if (fcnp->cn_namelen != tcnp->cn_namelen ||
	    bcmp(fcnp->cn_nameptr, tcnp->cn_nameptr, fcnp->cn_namelen) != 0) {
		newname = malloc(tcnp->cn_namelen, M_TMPFSNAME, M_WAITOK);
	} else
		newname = NULL;

	/*
	 * If the node is being moved to another directory, we have to do
	 * the move.
	 */
	if (fdnode != tdnode) {
		/*
		 * In case we are moving a directory, we have to adjust its
		 * parent to point to the new parent.
		 */
		if (de->td_node->tn_type == VDIR) {
			struct tmpfs_node *n;

			/*
			 * Ensure the target directory is not a child of the
			 * directory being moved.  Otherwise, we'd end up
			 * with stale nodes.
			 */
			n = tdnode;
			/*
			 * TMPFS_LOCK guaranties that no nodes are freed while
			 * traversing the list. Nodes can only be marked as
			 * removed: tn_parent == NULL.
			 */
			TMPFS_LOCK(tmp);
			TMPFS_NODE_LOCK(n);
			while (n != n->tn_dir.tn_parent) {
				struct tmpfs_node *parent;

				if (n == fnode) {
					TMPFS_NODE_UNLOCK(n);
					TMPFS_UNLOCK(tmp);
					error = EINVAL;
					if (newname != NULL)
						    free(newname, M_TMPFSNAME);
					goto out_locked;
				}
				parent = n->tn_dir.tn_parent;
				TMPFS_NODE_UNLOCK(n);
				if (parent == NULL) {
					n = NULL;
					break;
				}
				TMPFS_NODE_LOCK(parent);
				if (parent->tn_dir.tn_parent == NULL) {
					TMPFS_NODE_UNLOCK(parent);
					n = NULL;
					break;
				}
				n = parent;
			}
			TMPFS_UNLOCK(tmp);
			if (n == NULL) {
				error = EINVAL;
				if (newname != NULL)
					    free(newname, M_TMPFSNAME);
				goto out_locked;
			}
			TMPFS_NODE_UNLOCK(n);

			/* Adjust the parent pointer. */
			TMPFS_VALIDATE_DIR(fnode);
			TMPFS_NODE_LOCK(de->td_node);
			de->td_node->tn_dir.tn_parent = tdnode;
			TMPFS_NODE_UNLOCK(de->td_node);

			/*
			 * As a result of changing the target of the '..'
			 * entry, the link count of the source and target
			 * directories has to be adjusted.
			 */
			TMPFS_NODE_LOCK(tdnode);
			TMPFS_ASSERT_LOCKED(tdnode);
			tdnode->tn_links++;
			TMPFS_NODE_UNLOCK(tdnode);

			TMPFS_NODE_LOCK(fdnode);
			TMPFS_ASSERT_LOCKED(fdnode);
			fdnode->tn_links--;
			TMPFS_NODE_UNLOCK(fdnode);
		}
	}

	/*
	 * Do the move: just remove the entry from the source directory
	 * and insert it into the target one.
	 */
	tmpfs_dir_detach(fdvp, de);

	if (fcnp->cn_flags & DOWHITEOUT)
		tmpfs_dir_whiteout_add(fdvp, fcnp);
	if (tcnp->cn_flags & ISWHITEOUT)
		tmpfs_dir_whiteout_remove(tdvp, tcnp);

	/*
	 * If the name has changed, we need to make it effective by changing
	 * it in the directory entry.
	 */
	if (newname != NULL) {
		MPASS(tcnp->cn_namelen <= MAXNAMLEN);

		free(de->ud.td_name, M_TMPFSNAME);
		de->ud.td_name = newname;
		tmpfs_dirent_init(de, tcnp->cn_nameptr, tcnp->cn_namelen);

		fnode->tn_status |= TMPFS_NODE_CHANGED;
		tdnode->tn_status |= TMPFS_NODE_MODIFIED;
	}

	/*
	 * If we are overwriting an entry, we have to remove the old one
	 * from the target directory.
	 */
	if (tvp != NULL) {
		struct tmpfs_dirent *tde;

		/* Remove the old entry from the target directory. */
		tde = tmpfs_dir_lookup(tdnode, tnode, tcnp);
		tmpfs_dir_detach(tdvp, tde);

		/*
		 * Free the directory entry we just deleted.  Note that the
		 * node referred by it will not be removed until the vnode is
		 * really reclaimed.
		 */
		tmpfs_free_dirent(VFS_TO_TMPFS(tvp->v_mount), tde);
	}

	tmpfs_dir_attach(tdvp, de);

	if (tmpfs_use_nc(fvp)) {
		cache_purge(fvp);
		if (tvp != NULL)
			cache_purge(tvp);
		cache_purge_negative(tdvp);
	}

	error = 0;

out_locked:
	if (fdvp != tdvp && fdvp != tvp)
		VOP_UNLOCK(fdvp, 0);

out:
	/*
	 * Release target nodes.
	 * XXX: I don't understand when tdvp can be the same as tvp, but
	 * other code takes care of this...
	 */
	if (tdvp == tvp)
		vrele(tdvp);
	else
		vput(tdvp);
	if (tvp != NULL)
		vput(tvp);

	/* Release source nodes. */
	vrele(fdvp);
	vrele(fvp);

	if (mp != NULL)
		vfs_unbusy(mp);

	return (error);
}