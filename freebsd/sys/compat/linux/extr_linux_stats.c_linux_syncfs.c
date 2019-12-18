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
struct vnode {struct mount* v_mount; } ;
struct thread {int dummy; } ;
struct mount {int mnt_flag; } ;
struct linux_syncfs_args {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBF_MNTLSTLOCK ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int MNT_RDONLY ; 
 int /*<<< orphan*/  TDP_SYNCIO ; 
 int /*<<< orphan*/  VFS_SYNC (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_NOWAIT ; 
 int /*<<< orphan*/  cap_fsync_rights ; 
 int /*<<< orphan*/  curthread_pflags_restore (int) ; 
 int curthread_pflags_set (int /*<<< orphan*/ ) ; 
 int fgetvp (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vnode**) ; 
 int /*<<< orphan*/  mountlist_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_msync (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 scalar_t__ vn_start_write (int /*<<< orphan*/ *,struct mount**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
linux_syncfs(struct thread *td, struct linux_syncfs_args *args)
{
	struct mount *mp;
	struct vnode *vp;
	int error, save;

	error = fgetvp(td, args->fd, &cap_fsync_rights, &vp);
	if (error != 0)
		/*
		 * Linux syncfs() returns only EBADF, however fgetvp()
		 * can return EINVAL in case of file descriptor does
		 * not represent a vnode. XXX.
		 */
		return (error);

	mp = vp->v_mount;
	mtx_lock(&mountlist_mtx);
	error = vfs_busy(mp, MBF_MNTLSTLOCK);
	if (error != 0) {
		/* See comment above. */
		mtx_unlock(&mountlist_mtx);
		goto out;
	}
	if ((mp->mnt_flag & MNT_RDONLY) == 0 &&
	    vn_start_write(NULL, &mp, V_NOWAIT) == 0) {
		save = curthread_pflags_set(TDP_SYNCIO);
		vfs_msync(mp, MNT_NOWAIT);
		VFS_SYNC(mp, MNT_NOWAIT);
		curthread_pflags_restore(save);
		vn_finished_write(mp);
	}
	vfs_unbusy(mp);

 out:
	vrele(vp);
	return (error);
}