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
struct vnode {scalar_t__ v_type; struct mount* v_mountedhere; int /*<<< orphan*/  v_iflag; } ;
struct thread {int dummy; } ;
struct nameidata {struct vnode* ni_vp; } ;
struct TYPE_3__ {int /*<<< orphan*/  f_mntonname; } ;
struct mount {struct vnode* mnt_vnodecovered; TYPE_1__ mnt_stat; int /*<<< orphan*/  mnt_flag; } ;
struct TYPE_4__ {struct mount* v_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  FD_NONE ; 
 int FOLLOW ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int LOCKLEAF ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  MNAMELEN ; 
 int /*<<< orphan*/  MNT_ROOTFS ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,struct thread*) ; 
 struct mount* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct mount*,int /*<<< orphan*/ ) ; 
 struct mount* TAILQ_NEXT (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 scalar_t__ VDIR ; 
 scalar_t__ VFS_ROOT (struct mount*,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_MOUNT ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_SAVE ; 
 int /*<<< orphan*/  cache_purge (struct vnode*) ; 
 int /*<<< orphan*/  cache_purgevfs (struct mount*,int) ; 
 int kern_funlinkat (struct thread*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_list ; 
 int /*<<< orphan*/  mountlist ; 
 int /*<<< orphan*/  mountlist_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 TYPE_2__* rootvnode ; 
 int /*<<< orphan*/  set_rootvnode () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int vinvalbuf (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static void
vfs_mountroot_shuffle(struct thread *td, struct mount *mpdevfs)
{
	struct nameidata nd;
	struct mount *mporoot, *mpnroot;
	struct vnode *vp, *vporoot, *vpdevfs;
	char *fspath;
	int error;

	mpnroot = TAILQ_NEXT(mpdevfs, mnt_list);

	/* Shuffle the mountlist. */
	mtx_lock(&mountlist_mtx);
	mporoot = TAILQ_FIRST(&mountlist);
	TAILQ_REMOVE(&mountlist, mpdevfs, mnt_list);
	if (mporoot != mpdevfs) {
		TAILQ_REMOVE(&mountlist, mpnroot, mnt_list);
		TAILQ_INSERT_HEAD(&mountlist, mpnroot, mnt_list);
	}
	TAILQ_INSERT_TAIL(&mountlist, mpdevfs, mnt_list);
	mtx_unlock(&mountlist_mtx);

	cache_purgevfs(mporoot, true);
	if (mporoot != mpdevfs)
		cache_purgevfs(mpdevfs, true);

	if (VFS_ROOT(mporoot, LK_EXCLUSIVE, &vporoot))
		panic("vfs_mountroot_shuffle: Cannot find root vnode");

	VI_LOCK(vporoot);
	vporoot->v_iflag &= ~VI_MOUNT;
	VI_UNLOCK(vporoot);
	vporoot->v_mountedhere = NULL;
	mporoot->mnt_flag &= ~MNT_ROOTFS;
	mporoot->mnt_vnodecovered = NULL;
	vput(vporoot);

	/* Set up the new rootvnode, and purge the cache */
	mpnroot->mnt_vnodecovered = NULL;
	set_rootvnode();
	cache_purgevfs(rootvnode->v_mount, true);

	if (mporoot != mpdevfs) {
		/* Remount old root under /.mount or /mnt */
		fspath = "/.mount";
		NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_SYSSPACE,
		    fspath, td);
		error = namei(&nd);
		if (error) {
			NDFREE(&nd, NDF_ONLY_PNBUF);
			fspath = "/mnt";
			NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_SYSSPACE,
			    fspath, td);
			error = namei(&nd);
		}
		if (!error) {
			vp = nd.ni_vp;
			error = (vp->v_type == VDIR) ? 0 : ENOTDIR;
			if (!error)
				error = vinvalbuf(vp, V_SAVE, 0, 0);
			if (!error) {
				cache_purge(vp);
				mporoot->mnt_vnodecovered = vp;
				vp->v_mountedhere = mporoot;
				strlcpy(mporoot->mnt_stat.f_mntonname,
				    fspath, MNAMELEN);
				VOP_UNLOCK(vp, 0);
			} else
				vput(vp);
		}
		NDFREE(&nd, NDF_ONLY_PNBUF);

		if (error)
			printf("mountroot: unable to remount previous root "
			    "under /.mount or /mnt (error %d)\n", error);
	}

	/* Remount devfs under /dev */
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_SYSSPACE, "/dev", td);
	error = namei(&nd);
	if (!error) {
		vp = nd.ni_vp;
		error = (vp->v_type == VDIR) ? 0 : ENOTDIR;
		if (!error)
			error = vinvalbuf(vp, V_SAVE, 0, 0);
		if (!error) {
			vpdevfs = mpdevfs->mnt_vnodecovered;
			if (vpdevfs != NULL) {
				cache_purge(vpdevfs);
				vpdevfs->v_mountedhere = NULL;
				vrele(vpdevfs);
			}
			mpdevfs->mnt_vnodecovered = vp;
			vp->v_mountedhere = mpdevfs;
			VOP_UNLOCK(vp, 0);
		} else
			vput(vp);
	}
	if (error)
		printf("mountroot: unable to remount devfs under /dev "
		    "(error %d)\n", error);
	NDFREE(&nd, NDF_ONLY_PNBUF);

	if (mporoot == mpdevfs) {
		vfs_unbusy(mpdevfs);
		/* Unlink the no longer needed /dev/dev -> / symlink */
		error = kern_funlinkat(td, AT_FDCWD, "/dev/dev", FD_NONE,
		    UIO_SYSSPACE, 0, 0);
		if (error)
			printf("mountroot: unable to unlink /dev/dev "
			    "(error %d)\n", error);
	}
}