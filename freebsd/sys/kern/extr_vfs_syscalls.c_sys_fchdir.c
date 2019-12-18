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
struct vnode {struct mount* v_mountedhere; } ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;
struct file {struct vnode* f_vnode; } ;
struct fchdir_args {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_ARG_VNODE1 (struct vnode*) ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int VFS_ROOT (struct mount*,int,struct vnode**) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_fchdir_rights ; 
 int change_dir (struct vnode*,struct thread*) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getvnode (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file**) ; 
 int /*<<< orphan*/  pwd_chdir (struct thread*,struct vnode*) ; 
 scalar_t__ vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrefact (struct vnode*) ; 

int
sys_fchdir(struct thread *td, struct fchdir_args *uap)
{
	struct vnode *vp, *tdp;
	struct mount *mp;
	struct file *fp;
	int error;

	AUDIT_ARG_FD(uap->fd);
	error = getvnode(td, uap->fd, &cap_fchdir_rights,
	    &fp);
	if (error != 0)
		return (error);
	vp = fp->f_vnode;
	vrefact(vp);
	fdrop(fp, td);
	vn_lock(vp, LK_SHARED | LK_RETRY);
	AUDIT_ARG_VNODE1(vp);
	error = change_dir(vp, td);
	while (!error && (mp = vp->v_mountedhere) != NULL) {
		if (vfs_busy(mp, 0))
			continue;
		error = VFS_ROOT(mp, LK_SHARED, &tdp);
		vfs_unbusy(mp);
		if (error != 0)
			break;
		vput(vp);
		vp = tdp;
	}
	if (error != 0) {
		vput(vp);
		return (error);
	}
	VOP_UNLOCK(vp, 0);
	pwd_chdir(td, vp);
	return (0);
}