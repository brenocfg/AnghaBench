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
struct vnode {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {struct vnode* ni_vp; } ;
struct msdosfsmount {int pm_flags; int pm_fmod; int /*<<< orphan*/  pm_inusemap; struct vnode* pm_devvp; int /*<<< orphan*/  pm_cp; } ;
struct mount {int mnt_flag; int /*<<< orphan*/  mnt_optnew; } ;
typedef  int accmode_t ;

/* Variables and functions */
 int EINVAL ; 
 int FOLLOW ; 
 int FORCECLOSE ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LOCKLEAF ; 
 int /*<<< orphan*/  LOOKUP ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int MNT_RDONLY ; 
 int MNT_UPDATE ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int MSDOSFSMNT_RONLY ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,struct thread*) ; 
 int /*<<< orphan*/  PRIV_VFS_MOUNT_PERM ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 struct msdosfsmount* VFSTOMSDOSFS (struct mount*) ; 
 int VFS_SYNC (struct mount*,int /*<<< orphan*/ ) ; 
 int VOP_ACCESS (struct vnode*,int,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int VREAD ; 
 int VWRITE ; 
 int WRITECLOSE ; 
 struct thread* curthread ; 
 int g_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int markvoldirty (struct msdosfsmount*,int) ; 
 int markvoldirty_upgrade (struct msdosfsmount*,int,int) ; 
 int mountmsdosfs (struct vnode*,struct mount*) ; 
 int /*<<< orphan*/  msdosfs_opts ; 
 int /*<<< orphan*/  msdosfs_unmount (struct mount*,int) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  printf (char*,struct mount*,struct msdosfsmount*,int /*<<< orphan*/ ) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int update_mp (struct mount*,struct thread*) ; 
 int vflush (struct mount*,int /*<<< orphan*/ ,int,struct thread*) ; 
 scalar_t__ vfs_filteropt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_flagopt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_getopt (int /*<<< orphan*/ ,char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_mountedfrom (struct mount*,char*) ; 
 int /*<<< orphan*/  vn_isdisk (struct vnode*,int*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
msdosfs_mount(struct mount *mp)
{
	struct vnode *devvp;	  /* vnode for blk device to mount */
	struct thread *td;
	/* msdosfs specific mount control block */
	struct msdosfsmount *pmp = NULL;
	struct nameidata ndp;
	int error, flags;
	accmode_t accmode;
	char *from;

	td = curthread;
	if (vfs_filteropt(mp->mnt_optnew, msdosfs_opts))
		return (EINVAL);

	/*
	 * If updating, check whether changing from read-only to
	 * read/write; if there is no device name, that's all we do.
	 */
	if (mp->mnt_flag & MNT_UPDATE) {
		pmp = VFSTOMSDOSFS(mp);
		if (!(pmp->pm_flags & MSDOSFSMNT_RONLY) &&
		    vfs_flagopt(mp->mnt_optnew, "ro", NULL, 0)) {
			error = VFS_SYNC(mp, MNT_WAIT);
			if (error)
				return (error);
			flags = WRITECLOSE;
			if (mp->mnt_flag & MNT_FORCE)
				flags |= FORCECLOSE;
			error = vflush(mp, 0, flags, td);
			if (error)
				return (error);

			/*
			 * Now the volume is clean.  Mark it so while the
			 * device is still rw.
			 */
			error = markvoldirty(pmp, 0);
			if (error) {
				(void)markvoldirty(pmp, 1);
				return (error);
			}

			/* Downgrade the device from rw to ro. */
			g_topology_lock();
			error = g_access(pmp->pm_cp, 0, -1, 0);
			g_topology_unlock();
			if (error) {
				(void)markvoldirty(pmp, 1);
				return (error);
			}

			/*
			 * Backing out after an error was painful in the
			 * above.  Now we are committed to succeeding.
			 */
			pmp->pm_fmod = 0;
			pmp->pm_flags |= MSDOSFSMNT_RONLY;
			MNT_ILOCK(mp);
			mp->mnt_flag |= MNT_RDONLY;
			MNT_IUNLOCK(mp);
		} else if ((pmp->pm_flags & MSDOSFSMNT_RONLY) &&
		    !vfs_flagopt(mp->mnt_optnew, "ro", NULL, 0)) {
			/*
			 * If upgrade to read-write by non-root, then verify
			 * that user has necessary permissions on the device.
			 */
			devvp = pmp->pm_devvp;
			vn_lock(devvp, LK_EXCLUSIVE | LK_RETRY);
			error = VOP_ACCESS(devvp, VREAD | VWRITE,
			    td->td_ucred, td);
			if (error)
				error = priv_check(td, PRIV_VFS_MOUNT_PERM);
			if (error) {
				VOP_UNLOCK(devvp, 0);
				return (error);
			}
			VOP_UNLOCK(devvp, 0);
			g_topology_lock();
			error = g_access(pmp->pm_cp, 0, 1, 0);
			g_topology_unlock();
			if (error)
				return (error);

			/* Now that the volume is modifiable, mark it dirty. */
			error = markvoldirty_upgrade(pmp, true, true);
			if (error) {
				/*
				 * If dirtying the superblock failed, drop GEOM
				 * 'w' refs (we're still RO).
				 */
				g_topology_lock();
				(void)g_access(pmp->pm_cp, 0, -1, 0);
				g_topology_unlock();

				return (error);
			}

			pmp->pm_fmod = 1;
			pmp->pm_flags &= ~MSDOSFSMNT_RONLY;
			MNT_ILOCK(mp);
			mp->mnt_flag &= ~MNT_RDONLY;
			MNT_IUNLOCK(mp);
		}
	}
	/*
	 * Not an update, or updating the name: look up the name
	 * and verify that it refers to a sensible disk device.
	 */
	if (vfs_getopt(mp->mnt_optnew, "from", (void **)&from, NULL))
		return (EINVAL);
	NDINIT(&ndp, LOOKUP, FOLLOW | LOCKLEAF, UIO_SYSSPACE, from, td);
	error = namei(&ndp);
	if (error)
		return (error);
	devvp = ndp.ni_vp;
	NDFREE(&ndp, NDF_ONLY_PNBUF);

	if (!vn_isdisk(devvp, &error)) {
		vput(devvp);
		return (error);
	}
	/*
	 * If mount by non-root, then verify that user has necessary
	 * permissions on the device.
	 */
	accmode = VREAD;
	if ((mp->mnt_flag & MNT_RDONLY) == 0)
		accmode |= VWRITE;
	error = VOP_ACCESS(devvp, accmode, td->td_ucred, td);
	if (error)
		error = priv_check(td, PRIV_VFS_MOUNT_PERM);
	if (error) {
		vput(devvp);
		return (error);
	}
	if ((mp->mnt_flag & MNT_UPDATE) == 0) {
		error = mountmsdosfs(devvp, mp);
#ifdef MSDOSFS_DEBUG		/* only needed for the printf below */
		pmp = VFSTOMSDOSFS(mp);
#endif
	} else {
		vput(devvp);
		if (devvp != pmp->pm_devvp)
			return (EINVAL);	/* XXX needs translation */
	}
	if (error) {
		vrele(devvp);
		return (error);
	}

	error = update_mp(mp, td);
	if (error) {
		if ((mp->mnt_flag & MNT_UPDATE) == 0)
			msdosfs_unmount(mp, MNT_FORCE);
		return error;
	}

	vfs_mountedfrom(mp, from);
#ifdef MSDOSFS_DEBUG
	printf("msdosfs_mount(): mp %p, pmp %p, inusemap %p\n", mp, pmp, pmp->pm_inusemap);
#endif
	return (0);
}