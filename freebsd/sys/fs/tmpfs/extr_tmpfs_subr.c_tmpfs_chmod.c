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
struct vnode {scalar_t__ v_type; TYPE_1__* v_mount; } ;
struct ucred {int dummy; } ;
struct tmpfs_node {int tn_flags; int tn_mode; int /*<<< orphan*/  tn_status; int /*<<< orphan*/  tn_gid; } ;
struct thread {int dummy; } ;
typedef  int mode_t ;
struct TYPE_2__ {int mnt_flag; } ;

/* Variables and functions */
 int ALLPERMS ; 
 int APPEND ; 
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int EFTYPE ; 
 int EPERM ; 
 int EROFS ; 
 int IMMUTABLE ; 
 int MNT_RDONLY ; 
 int /*<<< orphan*/  PRIV_VFS_SETGID ; 
 int /*<<< orphan*/  PRIV_VFS_STICKYFILE ; 
 int S_ISGID ; 
 int S_ISTXT ; 
 int /*<<< orphan*/  TMPFS_NODE_CHANGED ; 
 int /*<<< orphan*/  VADMIN ; 
 scalar_t__ VDIR ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 struct tmpfs_node* VP_TO_TMPFS_NODE (struct vnode*) ; 
 int /*<<< orphan*/  groupmember (int /*<<< orphan*/ ,struct ucred*) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 

int
tmpfs_chmod(struct vnode *vp, mode_t mode, struct ucred *cred, struct thread *p)
{
	int error;
	struct tmpfs_node *node;

	ASSERT_VOP_ELOCKED(vp, "chmod");

	node = VP_TO_TMPFS_NODE(vp);

	/* Disallow this operation if the file system is mounted read-only. */
	if (vp->v_mount->mnt_flag & MNT_RDONLY)
		return EROFS;

	/* Immutable or append-only files cannot be modified, either. */
	if (node->tn_flags & (IMMUTABLE | APPEND))
		return EPERM;

	/*
	 * To modify the permissions on a file, must possess VADMIN
	 * for that file.
	 */
	if ((error = VOP_ACCESS(vp, VADMIN, cred, p)))
		return (error);

	/*
	 * Privileged processes may set the sticky bit on non-directories,
	 * as well as set the setgid bit on a file with a group that the
	 * process is not a member of.
	 */
	if (vp->v_type != VDIR && (mode & S_ISTXT)) {
		if (priv_check_cred(cred, PRIV_VFS_STICKYFILE))
			return (EFTYPE);
	}
	if (!groupmember(node->tn_gid, cred) && (mode & S_ISGID)) {
		error = priv_check_cred(cred, PRIV_VFS_SETGID);
		if (error)
			return (error);
	}


	node->tn_mode &= ~ALLPERMS;
	node->tn_mode |= mode & ALLPERMS;

	node->tn_status |= TMPFS_NODE_CHANGED;

	ASSERT_VOP_ELOCKED(vp, "chmod2");

	return (0);
}