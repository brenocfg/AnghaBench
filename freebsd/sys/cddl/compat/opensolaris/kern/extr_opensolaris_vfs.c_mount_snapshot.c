#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ v_type; int v_iflag; struct mount* v_mountedhere; TYPE_1__* v_mount; } ;
typedef  TYPE_2__ vnode_t ;
struct vfsconf {int dummy; } ;
struct ucred {int dummy; } ;
struct mount {int mnt_flag; int /*<<< orphan*/ * mnt_optnew; int /*<<< orphan*/  mnt_stat; int /*<<< orphan*/ * mnt_opt; int /*<<< orphan*/ * mnt_vnodecovered; } ;
struct TYPE_18__ {struct ucred* td_ucred; } ;
typedef  TYPE_3__ kthread_t ;
struct TYPE_16__ {int /*<<< orphan*/  mnt_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (TYPE_2__*,char*) ; 
 int EBUSY ; 
 int ENAMETOOLONG ; 
 int ENODEV ; 
 int ENOTDIR ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 scalar_t__ MFSNAMELEN ; 
 scalar_t__ MNAMELEN ; 
 int MNT_IGNORE ; 
 int MNT_NOSUID ; 
 int MNT_RDONLY ; 
 int MNT_UPDATEMASK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct mount*,int /*<<< orphan*/ ) ; 
 scalar_t__ VDIR ; 
 int VFS_MOUNT (struct mount*) ; 
 scalar_t__ VFS_ROOT (struct mount*,int,TYPE_2__**) ; 
 int /*<<< orphan*/  VFS_STATFS (struct mount*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VI_LOCK (TYPE_2__*) ; 
 int VI_MOUNT ; 
 int /*<<< orphan*/  VI_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VQ_MOUNT ; 
 int /*<<< orphan*/  cache_purge (TYPE_2__*) ; 
 struct ucred* kcred ; 
 int /*<<< orphan*/  mnt_list ; 
 int /*<<< orphan*/  mountlist ; 
 int /*<<< orphan*/  mountlist_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ strlen (char const*) ; 
 struct vfsconf* vfs_byname_kld (char const*,TYPE_3__*,int*) ; 
 int /*<<< orphan*/  vfs_event_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_freeopts (int /*<<< orphan*/ *) ; 
 struct mount* vfs_mount_alloc (TYPE_2__*,struct vfsconf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_mount_destroy (struct mount*) ; 
 int /*<<< orphan*/  vfs_op_exit (struct mount*) ; 
 int /*<<< orphan*/  vfs_setmntopt (struct mount*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vput (TYPE_2__*) ; 

int
mount_snapshot(kthread_t *td, vnode_t **vpp, const char *fstype, char *fspath,
    char *fspec, int fsflags)
{
	struct vfsconf *vfsp;
	struct mount *mp;
	vnode_t *vp, *mvp;
	struct ucred *cr;
	int error;

	ASSERT_VOP_ELOCKED(*vpp, "mount_snapshot");

	vp = *vpp;
	*vpp = NULL;
	error = 0;

	/*
	 * Be ultra-paranoid about making sure the type and fspath
	 * variables will fit in our mp buffers, including the
	 * terminating NUL.
	 */
	if (strlen(fstype) >= MFSNAMELEN || strlen(fspath) >= MNAMELEN)
		error = ENAMETOOLONG;
	if (error == 0 && (vfsp = vfs_byname_kld(fstype, td, &error)) == NULL)
		error = ENODEV;
	if (error == 0 && vp->v_type != VDIR)
		error = ENOTDIR;
	/*
	 * We need vnode lock to protect v_mountedhere and vnode interlock
	 * to protect v_iflag.
	 */
	if (error == 0) {
		VI_LOCK(vp);
		if ((vp->v_iflag & VI_MOUNT) == 0 && vp->v_mountedhere == NULL)
			vp->v_iflag |= VI_MOUNT;
		else
			error = EBUSY;
		VI_UNLOCK(vp);
	}
	if (error != 0) {
		vput(vp);
		return (error);
	}
	VOP_UNLOCK(vp, 0);

	/*
	 * Allocate and initialize the filesystem.
	 * We don't want regular user that triggered snapshot mount to be able
	 * to unmount it, so pass credentials of the parent mount.
	 */
	mp = vfs_mount_alloc(vp, vfsp, fspath, vp->v_mount->mnt_cred);

	mp->mnt_optnew = NULL;
	vfs_setmntopt(mp, "from", fspec, 0);
	mp->mnt_optnew = mp->mnt_opt;
	mp->mnt_opt = NULL;

	/*
	 * Set the mount level flags.
	 */
	mp->mnt_flag = fsflags & MNT_UPDATEMASK;
	/*
	 * Snapshots are always read-only.
	 */
	mp->mnt_flag |= MNT_RDONLY;
	/*
	 * We don't want snapshots to allow access to vulnerable setuid
	 * programs, so we turn off setuid when mounting snapshots.
	 */
	mp->mnt_flag |= MNT_NOSUID;
	/*
	 * We don't want snapshots to be visible in regular
	 * mount(8) and df(1) output.
	 */
	mp->mnt_flag |= MNT_IGNORE;
	/*
	 * XXX: This is evil, but we can't mount a snapshot as a regular user.
	 * XXX: Is is safe when snapshot is mounted from within a jail?
	 */
	cr = td->td_ucred;
	td->td_ucred = kcred;
	error = VFS_MOUNT(mp);
	td->td_ucred = cr;

	if (error != 0) {
		/*
		 * Clear VI_MOUNT and decrement the use count "atomically",
		 * under the vnode lock.  This is not strictly required,
		 * but makes it easier to reason about the life-cycle and
		 * ownership of the covered vnode.
		 */
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
		VI_LOCK(vp);
		vp->v_iflag &= ~VI_MOUNT;
		VI_UNLOCK(vp);
		vput(vp);
		vfs_unbusy(mp);
		vfs_freeopts(mp->mnt_optnew);
		mp->mnt_vnodecovered = NULL;
		vfs_mount_destroy(mp);
		return (error);
	}

	if (mp->mnt_opt != NULL)
		vfs_freeopts(mp->mnt_opt);
	mp->mnt_opt = mp->mnt_optnew;
	(void)VFS_STATFS(mp, &mp->mnt_stat);

	/*
	 * Prevent external consumers of mount options from reading
	 * mnt_optnew.
	*/
	mp->mnt_optnew = NULL;

	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
#ifdef FREEBSD_NAMECACHE
	cache_purge(vp);
#endif
	VI_LOCK(vp);
	vp->v_iflag &= ~VI_MOUNT;
	VI_UNLOCK(vp);

	vp->v_mountedhere = mp;
	/* Put the new filesystem on the mount list. */
	mtx_lock(&mountlist_mtx);
	TAILQ_INSERT_TAIL(&mountlist, mp, mnt_list);
	mtx_unlock(&mountlist_mtx);
	vfs_event_signal(NULL, VQ_MOUNT, 0);
	if (VFS_ROOT(mp, LK_EXCLUSIVE, &mvp))
		panic("mount: lost mount");
	VOP_UNLOCK(vp, 0);
	vfs_op_exit(mp);
	vfs_unbusy(mp);
	*vpp = mvp;
	return (0);
}