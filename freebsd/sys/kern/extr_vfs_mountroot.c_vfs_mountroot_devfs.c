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
struct vfsoptlist {int dummy; } ;
struct vfsconf {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct mount {struct vfsoptlist* mnt_opt; int /*<<< orphan*/  mnt_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int ENOENT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_MOUNT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NULLVP ; 
 int /*<<< orphan*/  TAILQ_INIT (struct vfsoptlist*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VFS_MOUNT (struct mount*) ; 
 int VFS_STATFS (struct mount*,int /*<<< orphan*/ *) ; 
 int kern_symlinkat (struct thread*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct vfsoptlist* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_list ; 
 int /*<<< orphan*/  mountlist ; 
 int /*<<< orphan*/  mountlist_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 struct mount* rootdevmp ; 
 int /*<<< orphan*/  set_rootvnode () ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 struct vfsconf* vfs_byname (char*) ; 
 struct mount* vfs_mount_alloc (int /*<<< orphan*/ ,struct vfsconf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_op_exit (struct mount*) ; 

__attribute__((used)) static int
vfs_mountroot_devfs(struct thread *td, struct mount **mpp)
{
	struct vfsoptlist *opts;
	struct vfsconf *vfsp;
	struct mount *mp;
	int error;

	*mpp = NULL;

	if (rootdevmp != NULL) {
		/*
		 * Already have /dev; this happens during rerooting.
		 */
		error = vfs_busy(rootdevmp, 0);
		if (error != 0)
			return (error);
		*mpp = rootdevmp;
	} else {
		vfsp = vfs_byname("devfs");
		KASSERT(vfsp != NULL, ("Could not find devfs by name"));
		if (vfsp == NULL)
			return (ENOENT);

		mp = vfs_mount_alloc(NULLVP, vfsp, "/dev", td->td_ucred);

		error = VFS_MOUNT(mp);
		KASSERT(error == 0, ("VFS_MOUNT(devfs) failed %d", error));
		if (error)
			return (error);

		error = VFS_STATFS(mp, &mp->mnt_stat);
		KASSERT(error == 0, ("VFS_STATFS(devfs) failed %d", error));
		if (error)
			return (error);

		opts = malloc(sizeof(struct vfsoptlist), M_MOUNT, M_WAITOK);
		TAILQ_INIT(opts);
		mp->mnt_opt = opts;

		mtx_lock(&mountlist_mtx);
		TAILQ_INSERT_HEAD(&mountlist, mp, mnt_list);
		mtx_unlock(&mountlist_mtx);

		*mpp = mp;
		rootdevmp = mp;
		vfs_op_exit(mp);
	}

	set_rootvnode();

	error = kern_symlinkat(td, "/", AT_FDCWD, "dev", UIO_SYSSPACE);
	if (error)
		printf("kern_symlink /dev -> / returns %d\n", error);

	return (error);
}