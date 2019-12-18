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
typedef  int u_long ;
struct vnode {TYPE_1__* v_mount; } ;
struct ucred {int dummy; } ;
struct tmpfs_node {int tn_flags; int /*<<< orphan*/  tn_status; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {int mnt_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int EROFS ; 
 int MNT_RDONLY ; 
 int /*<<< orphan*/  PRIV_VFS_SYSFLAGS ; 
 int SF_APPEND ; 
 int SF_ARCHIVED ; 
 int SF_IMMUTABLE ; 
 int SF_NOUNLINK ; 
 int SF_SETTABLE ; 
 int /*<<< orphan*/  TMPFS_NODE_CHANGED ; 
 int UF_APPEND ; 
 int UF_ARCHIVE ; 
 int UF_HIDDEN ; 
 int UF_IMMUTABLE ; 
 int UF_NODUMP ; 
 int UF_NOUNLINK ; 
 int UF_OFFLINE ; 
 int UF_OPAQUE ; 
 int UF_READONLY ; 
 int UF_REPARSE ; 
 int UF_SPARSE ; 
 int UF_SYSTEM ; 
 int /*<<< orphan*/  VADMIN ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 struct tmpfs_node* VP_TO_TMPFS_NODE (struct vnode*) ; 
 int /*<<< orphan*/  priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int securelevel_gt (struct ucred*,int /*<<< orphan*/ ) ; 

int
tmpfs_chflags(struct vnode *vp, u_long flags, struct ucred *cred,
    struct thread *p)
{
	int error;
	struct tmpfs_node *node;

	ASSERT_VOP_ELOCKED(vp, "chflags");

	node = VP_TO_TMPFS_NODE(vp);

	if ((flags & ~(SF_APPEND | SF_ARCHIVED | SF_IMMUTABLE | SF_NOUNLINK |
	    UF_APPEND | UF_ARCHIVE | UF_HIDDEN | UF_IMMUTABLE | UF_NODUMP |
	    UF_NOUNLINK | UF_OFFLINE | UF_OPAQUE | UF_READONLY | UF_REPARSE |
	    UF_SPARSE | UF_SYSTEM)) != 0)
		return (EOPNOTSUPP);

	/* Disallow this operation if the file system is mounted read-only. */
	if (vp->v_mount->mnt_flag & MNT_RDONLY)
		return EROFS;

	/*
	 * Callers may only modify the file flags on objects they
	 * have VADMIN rights for.
	 */
	if ((error = VOP_ACCESS(vp, VADMIN, cred, p)))
		return (error);
	/*
	 * Unprivileged processes are not permitted to unset system
	 * flags, or modify flags if any system flags are set.
	 */
	if (!priv_check_cred(cred, PRIV_VFS_SYSFLAGS)) {
		if (node->tn_flags &
		    (SF_NOUNLINK | SF_IMMUTABLE | SF_APPEND)) {
			error = securelevel_gt(cred, 0);
			if (error)
				return (error);
		}
	} else {
		if (node->tn_flags &
		    (SF_NOUNLINK | SF_IMMUTABLE | SF_APPEND) ||
		    ((flags ^ node->tn_flags) & SF_SETTABLE))
			return (EPERM);
	}
	node->tn_flags = flags;
	node->tn_status |= TMPFS_NODE_CHANGED;

	ASSERT_VOP_ELOCKED(vp, "chflags2");

	return (0);
}