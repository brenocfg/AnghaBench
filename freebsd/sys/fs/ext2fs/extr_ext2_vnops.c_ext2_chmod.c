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
struct vnode {scalar_t__ v_type; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_flag; int /*<<< orphan*/  i_gid; } ;

/* Variables and functions */
 int ALLPERMS ; 
 int EFTYPE ; 
 int /*<<< orphan*/  IN_CHANGE ; 
 int ISGID ; 
 int /*<<< orphan*/  PRIV_VFS_SETGID ; 
 int /*<<< orphan*/  PRIV_VFS_STICKYFILE ; 
 int S_ISTXT ; 
 int /*<<< orphan*/  VADMIN ; 
 scalar_t__ VDIR ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 struct inode* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  groupmember (int /*<<< orphan*/ ,struct ucred*) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_chmod(struct vnode *vp, int mode, struct ucred *cred, struct thread *td)
{
	struct inode *ip = VTOI(vp);
	int error;

	/*
	 * To modify the permissions on a file, must possess VADMIN
	 * for that file.
	 */
	if ((error = VOP_ACCESS(vp, VADMIN, cred, td)))
		return (error);
	/*
	 * Privileged processes may set the sticky bit on non-directories,
	 * as well as set the setgid bit on a file with a group that the
	 * process is not a member of.
	 */
	if (vp->v_type != VDIR && (mode & S_ISTXT)) {
		error = priv_check_cred(cred, PRIV_VFS_STICKYFILE);
		if (error)
			return (EFTYPE);
	}
	if (!groupmember(ip->i_gid, cred) && (mode & ISGID)) {
		error = priv_check_cred(cred, PRIV_VFS_SETGID);
		if (error)
			return (error);
	}
	ip->i_mode &= ~ALLPERMS;
	ip->i_mode |= (mode & ALLPERMS);
	ip->i_flag |= IN_CHANGE;
	return (0);
}