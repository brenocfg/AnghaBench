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
typedef  int uint64_t ;
struct vnode {scalar_t__ v_rdev; } ;
struct ufsmount {int um_fsckpid; int /*<<< orphan*/  um_cp; struct fs* um_fs; struct vnode* um_devvp; } ;
struct ufs2_dinode {int dummy; } ;
struct ufs1_dinode {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {struct vnode* ni_vp; } ;
struct mount {int mnt_flag; int /*<<< orphan*/  mnt_optnew; int /*<<< orphan*/  mnt_opt; } ;
struct inode {int dummy; } ;
struct fs {scalar_t__ fs_ronly; scalar_t__ fs_pendingblocks; scalar_t__ fs_pendinginodes; char* fs_fsmnt; int fs_flags; int fs_clean; scalar_t__* fs_snapinum; int fs_fmod; void* fs_mtime; } ;
typedef  int pid_t ;
typedef  int intmax_t ;
typedef  int accmode_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int FOLLOW ; 
 int FORCECLOSE ; 
 int FS_ACLS ; 
 int FS_DOSOFTDEP ; 
 int FS_NEEDSFSCK ; 
 int FS_NFS4ACLS ; 
 int FS_SUJ ; 
 int FS_UNCLEAN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LOCKLEAF ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  MBF_NOWAIT ; 
 int MNT_ACLS ; 
 int MNT_ASYNC ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int MNT_NFS4ACLS ; 
 int MNT_RDONLY ; 
 int MNT_RELOAD ; 
 int MNT_SNAPSHOT ; 
 int MNT_UNTRUSTED ; 
 int MNT_UPDATE ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 scalar_t__ MOUNTEDSOFTDEP (struct mount*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,struct thread*) ; 
 int /*<<< orphan*/  PRIV_VFS_MOUNT_PERM ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 struct ufsmount* VFSTOUFS (struct mount*) ; 
 int VOP_ACCESS (struct vnode*,int,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int VREAD ; 
 int VWRITE ; 
 int /*<<< orphan*/  V_WAIT ; 
 int WRITECLOSE ; 
 struct thread* curthread ; 
 int ffs_flushfiles (struct mount*,int,struct thread*) ; 
 int ffs_mountfs (struct vnode*,struct mount*,struct thread*) ; 
 int /*<<< orphan*/  ffs_opts ; 
 int ffs_reload (struct mount*,struct thread*,int /*<<< orphan*/ ) ; 
 int ffs_sbupdate (struct ufsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ffs_snapshot (struct mount*,char*) ; 
 int /*<<< orphan*/  ffs_snapshot_mount (struct mount*) ; 
 int g_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int softdep_flushfiles (struct mount*,int,struct thread*) ; 
 int softdep_mount (struct vnode*,struct mount*,struct fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  softdep_unmount (struct mount*) ; 
 void* time_second ; 
 int /*<<< orphan*/ * uma_inode ; 
 void* uma_ufs1 ; 
 void* uma_ufs2 ; 
 void* uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_deleteopt (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vfs_filteropt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_flagopt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_getopt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* vfs_getopts (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  vfs_mount_error (struct mount*,char*,...) ; 
 int /*<<< orphan*/  vfs_mountedfrom (struct mount*,char*) ; 
 int vfs_scanopt (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vfs_write_resume (struct mount*,int /*<<< orphan*/ ) ; 
 int vfs_write_suspend_umnt (struct mount*) ; 
 int /*<<< orphan*/  vn_isdisk (struct vnode*,int*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int vn_start_write (int /*<<< orphan*/ *,struct mount**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
ffs_mount(struct mount *mp)
{
	struct vnode *devvp;
	struct thread *td;
	struct ufsmount *ump = NULL;
	struct fs *fs;
	pid_t fsckpid = 0;
	int error, error1, flags;
	uint64_t mntorflags, saved_mnt_flag;
	accmode_t accmode;
	struct nameidata ndp;
	char *fspec;

	td = curthread;
	if (vfs_filteropt(mp->mnt_optnew, ffs_opts))
		return (EINVAL);
	if (uma_inode == NULL) {
		uma_inode = uma_zcreate("FFS inode",
		    sizeof(struct inode), NULL, NULL, NULL, NULL,
		    UMA_ALIGN_PTR, 0);
		uma_ufs1 = uma_zcreate("FFS1 dinode",
		    sizeof(struct ufs1_dinode), NULL, NULL, NULL, NULL,
		    UMA_ALIGN_PTR, 0);
		uma_ufs2 = uma_zcreate("FFS2 dinode",
		    sizeof(struct ufs2_dinode), NULL, NULL, NULL, NULL,
		    UMA_ALIGN_PTR, 0);
	}

	vfs_deleteopt(mp->mnt_optnew, "groupquota");
	vfs_deleteopt(mp->mnt_optnew, "userquota");

	fspec = vfs_getopts(mp->mnt_optnew, "from", &error);
	if (error)
		return (error);

	mntorflags = 0;
	if (vfs_getopt(mp->mnt_optnew, "untrusted", NULL, NULL) == 0)
		mntorflags |= MNT_UNTRUSTED;

	if (vfs_getopt(mp->mnt_optnew, "acls", NULL, NULL) == 0)
		mntorflags |= MNT_ACLS;

	if (vfs_getopt(mp->mnt_optnew, "snapshot", NULL, NULL) == 0) {
		mntorflags |= MNT_SNAPSHOT;
		/*
		 * Once we have set the MNT_SNAPSHOT flag, do not
		 * persist "snapshot" in the options list.
		 */
		vfs_deleteopt(mp->mnt_optnew, "snapshot");
		vfs_deleteopt(mp->mnt_opt, "snapshot");
	}

	if (vfs_getopt(mp->mnt_optnew, "fsckpid", NULL, NULL) == 0 &&
	    vfs_scanopt(mp->mnt_optnew, "fsckpid", "%d", &fsckpid) == 1) {
		/*
		 * Once we have set the restricted PID, do not
		 * persist "fsckpid" in the options list.
		 */
		vfs_deleteopt(mp->mnt_optnew, "fsckpid");
		vfs_deleteopt(mp->mnt_opt, "fsckpid");
		if (mp->mnt_flag & MNT_UPDATE) {
			if (VFSTOUFS(mp)->um_fs->fs_ronly == 0 &&
			     vfs_flagopt(mp->mnt_optnew, "ro", NULL, 0) == 0) {
				vfs_mount_error(mp,
				    "Checker enable: Must be read-only");
				return (EINVAL);
			}
		} else if (vfs_flagopt(mp->mnt_optnew, "ro", NULL, 0) == 0) {
			vfs_mount_error(mp,
			    "Checker enable: Must be read-only");
			return (EINVAL);
		}
		/* Set to -1 if we are done */
		if (fsckpid == 0)
			fsckpid = -1;
	}

	if (vfs_getopt(mp->mnt_optnew, "nfsv4acls", NULL, NULL) == 0) {
		if (mntorflags & MNT_ACLS) {
			vfs_mount_error(mp,
			    "\"acls\" and \"nfsv4acls\" options "
			    "are mutually exclusive");
			return (EINVAL);
		}
		mntorflags |= MNT_NFS4ACLS;
	}

	MNT_ILOCK(mp);
	mp->mnt_flag |= mntorflags;
	MNT_IUNLOCK(mp);
	/*
	 * If updating, check whether changing from read-only to
	 * read/write; if there is no device name, that's all we do.
	 */
	if (mp->mnt_flag & MNT_UPDATE) {
		ump = VFSTOUFS(mp);
		fs = ump->um_fs;
		devvp = ump->um_devvp;
		if (fsckpid == -1 && ump->um_fsckpid > 0) {
			if ((error = ffs_flushfiles(mp, WRITECLOSE, td)) != 0 ||
			    (error = ffs_sbupdate(ump, MNT_WAIT, 0)) != 0)
				return (error);
			g_topology_lock();
			/*
			 * Return to normal read-only mode.
			 */
			error = g_access(ump->um_cp, 0, -1, 0);
			g_topology_unlock();
			ump->um_fsckpid = 0;
		}
		if (fs->fs_ronly == 0 &&
		    vfs_flagopt(mp->mnt_optnew, "ro", NULL, 0)) {
			/*
			 * Flush any dirty data and suspend filesystem.
			 */
			if ((error = vn_start_write(NULL, &mp, V_WAIT)) != 0)
				return (error);
			error = vfs_write_suspend_umnt(mp);
			if (error != 0)
				return (error);
			/*
			 * Check for and optionally get rid of files open
			 * for writing.
			 */
			flags = WRITECLOSE;
			if (mp->mnt_flag & MNT_FORCE)
				flags |= FORCECLOSE;
			if (MOUNTEDSOFTDEP(mp)) {
				error = softdep_flushfiles(mp, flags, td);
			} else {
				error = ffs_flushfiles(mp, flags, td);
			}
			if (error) {
				vfs_write_resume(mp, 0);
				return (error);
			}
			if (fs->fs_pendingblocks != 0 ||
			    fs->fs_pendinginodes != 0) {
				printf("WARNING: %s Update error: blocks %jd "
				    "files %d\n", fs->fs_fsmnt, 
				    (intmax_t)fs->fs_pendingblocks,
				    fs->fs_pendinginodes);
				fs->fs_pendingblocks = 0;
				fs->fs_pendinginodes = 0;
			}
			if ((fs->fs_flags & (FS_UNCLEAN | FS_NEEDSFSCK)) == 0)
				fs->fs_clean = 1;
			if ((error = ffs_sbupdate(ump, MNT_WAIT, 0)) != 0) {
				fs->fs_ronly = 0;
				fs->fs_clean = 0;
				vfs_write_resume(mp, 0);
				return (error);
			}
			if (MOUNTEDSOFTDEP(mp))
				softdep_unmount(mp);
			g_topology_lock();
			/*
			 * Drop our write and exclusive access.
			 */
			g_access(ump->um_cp, 0, -1, -1);
			g_topology_unlock();
			fs->fs_ronly = 1;
			MNT_ILOCK(mp);
			mp->mnt_flag |= MNT_RDONLY;
			MNT_IUNLOCK(mp);
			/*
			 * Allow the writers to note that filesystem
			 * is ro now.
			 */
			vfs_write_resume(mp, 0);
		}
		if ((mp->mnt_flag & MNT_RELOAD) &&
		    (error = ffs_reload(mp, td, 0)) != 0)
			return (error);
		if (fs->fs_ronly &&
		    !vfs_flagopt(mp->mnt_optnew, "ro", NULL, 0)) {
			/*
			 * If we are running a checker, do not allow upgrade.
			 */
			if (ump->um_fsckpid > 0) {
				vfs_mount_error(mp,
				    "Active checker, cannot upgrade to write");
				return (EINVAL);
			}
			/*
			 * If upgrade to read-write by non-root, then verify
			 * that user has necessary permissions on the device.
			 */
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
			fs->fs_flags &= ~FS_UNCLEAN;
			if (fs->fs_clean == 0) {
				fs->fs_flags |= FS_UNCLEAN;
				if ((mp->mnt_flag & MNT_FORCE) ||
				    ((fs->fs_flags &
				     (FS_SUJ | FS_NEEDSFSCK)) == 0 &&
				     (fs->fs_flags & FS_DOSOFTDEP))) {
					printf("WARNING: %s was not properly "
					   "dismounted\n", fs->fs_fsmnt);
				} else {
					vfs_mount_error(mp,
					   "R/W mount of %s denied. %s.%s",
					   fs->fs_fsmnt,
					   "Filesystem is not clean - run fsck",
					   (fs->fs_flags & FS_SUJ) == 0 ? "" :
					   " Forced mount will invalidate"
					   " journal contents");
					return (EPERM);
				}
			}
			g_topology_lock();
			/*
			 * Request exclusive write access.
			 */
			error = g_access(ump->um_cp, 0, 1, 1);
			g_topology_unlock();
			if (error)
				return (error);
			if ((error = vn_start_write(NULL, &mp, V_WAIT)) != 0)
				return (error);
			error = vfs_write_suspend_umnt(mp);
			if (error != 0)
				return (error);
			fs->fs_ronly = 0;
			MNT_ILOCK(mp);
			saved_mnt_flag = MNT_RDONLY;
			if (MOUNTEDSOFTDEP(mp) && (mp->mnt_flag &
			    MNT_ASYNC) != 0)
				saved_mnt_flag |= MNT_ASYNC;
			mp->mnt_flag &= ~saved_mnt_flag;
			MNT_IUNLOCK(mp);
			fs->fs_mtime = time_second;
			/* check to see if we need to start softdep */
			if ((fs->fs_flags & FS_DOSOFTDEP) &&
			    (error = softdep_mount(devvp, mp, fs, td->td_ucred))){
				fs->fs_ronly = 1;
				MNT_ILOCK(mp);
				mp->mnt_flag |= saved_mnt_flag;
				MNT_IUNLOCK(mp);
				vfs_write_resume(mp, 0);
				return (error);
			}
			fs->fs_clean = 0;
			if ((error = ffs_sbupdate(ump, MNT_WAIT, 0)) != 0) {
				fs->fs_ronly = 1;
				MNT_ILOCK(mp);
				mp->mnt_flag |= saved_mnt_flag;
				MNT_IUNLOCK(mp);
				vfs_write_resume(mp, 0);
				return (error);
			}
			if (fs->fs_snapinum[0] != 0)
				ffs_snapshot_mount(mp);
			vfs_write_resume(mp, 0);
		}
		/*
		 * Soft updates is incompatible with "async",
		 * so if we are doing softupdates stop the user
		 * from setting the async flag in an update.
		 * Softdep_mount() clears it in an initial mount
		 * or ro->rw remount.
		 */
		if (MOUNTEDSOFTDEP(mp)) {
			/* XXX: Reset too late ? */
			MNT_ILOCK(mp);
			mp->mnt_flag &= ~MNT_ASYNC;
			MNT_IUNLOCK(mp);
		}
		/*
		 * Keep MNT_ACLS flag if it is stored in superblock.
		 */
		if ((fs->fs_flags & FS_ACLS) != 0) {
			/* XXX: Set too late ? */
			MNT_ILOCK(mp);
			mp->mnt_flag |= MNT_ACLS;
			MNT_IUNLOCK(mp);
		}

		if ((fs->fs_flags & FS_NFS4ACLS) != 0) {
			/* XXX: Set too late ? */
			MNT_ILOCK(mp);
			mp->mnt_flag |= MNT_NFS4ACLS;
			MNT_IUNLOCK(mp);
		}
		/*
		 * If this is a request from fsck to clean up the filesystem,
		 * then allow the specified pid to proceed.
		 */
		if (fsckpid > 0) {
			if (ump->um_fsckpid != 0) {
				vfs_mount_error(mp,
				    "Active checker already running on %s",
				    fs->fs_fsmnt);
				return (EINVAL);
			}
			KASSERT(MOUNTEDSOFTDEP(mp) == 0,
			    ("soft updates enabled on read-only file system"));
			g_topology_lock();
			/*
			 * Request write access.
			 */
			error = g_access(ump->um_cp, 0, 1, 0);
			g_topology_unlock();
			if (error) {
				vfs_mount_error(mp,
				    "Checker activation failed on %s",
				    fs->fs_fsmnt);
				return (error);
			}
			ump->um_fsckpid = fsckpid;
			if (fs->fs_snapinum[0] != 0)
				ffs_snapshot_mount(mp);
			fs->fs_mtime = time_second;
			fs->fs_fmod = 1;
			fs->fs_clean = 0;
			(void) ffs_sbupdate(ump, MNT_WAIT, 0);
		}

		/*
		 * If this is a snapshot request, take the snapshot.
		 */
		if (mp->mnt_flag & MNT_SNAPSHOT)
			return (ffs_snapshot(mp, fspec));

		/*
		 * Must not call namei() while owning busy ref.
		 */
		vfs_unbusy(mp);
	}

	/*
	 * Not an update, or updating the name: look up the name
	 * and verify that it refers to a sensible disk device.
	 */
	NDINIT(&ndp, LOOKUP, FOLLOW | LOCKLEAF, UIO_SYSSPACE, fspec, td);
	error = namei(&ndp);
	if ((mp->mnt_flag & MNT_UPDATE) != 0) {
		/*
		 * Unmount does not start if MNT_UPDATE is set.  Mount
		 * update busies mp before setting MNT_UPDATE.  We
		 * must be able to retain our busy ref succesfully,
		 * without sleep.
		 */
		error1 = vfs_busy(mp, MBF_NOWAIT);
		MPASS(error1 == 0);
	}
	if (error != 0)
		return (error);
	NDFREE(&ndp, NDF_ONLY_PNBUF);
	devvp = ndp.ni_vp;
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

	if (mp->mnt_flag & MNT_UPDATE) {
		/*
		 * Update only
		 *
		 * If it's not the same vnode, or at least the same device
		 * then it's not correct.
		 */

		if (devvp->v_rdev != ump->um_devvp->v_rdev)
			error = EINVAL;	/* needs translation */
		vput(devvp);
		if (error)
			return (error);
	} else {
		/*
		 * New mount
		 *
		 * We need the name for the mount point (also used for
		 * "last mounted on") copied in. If an error occurs,
		 * the mount point is discarded by the upper level code.
		 * Note that vfs_mount_alloc() populates f_mntonname for us.
		 */
		if ((error = ffs_mountfs(devvp, mp, td)) != 0) {
			vrele(devvp);
			return (error);
		}
		if (fsckpid > 0) {
			KASSERT(MOUNTEDSOFTDEP(mp) == 0,
			    ("soft updates enabled on read-only file system"));
			ump = VFSTOUFS(mp);
			fs = ump->um_fs;
			g_topology_lock();
			/*
			 * Request write access.
			 */
			error = g_access(ump->um_cp, 0, 1, 0);
			g_topology_unlock();
			if (error) {
				printf("WARNING: %s: Checker activation "
				    "failed\n", fs->fs_fsmnt);
			} else { 
				ump->um_fsckpid = fsckpid;
				if (fs->fs_snapinum[0] != 0)
					ffs_snapshot_mount(mp);
				fs->fs_mtime = time_second;
				fs->fs_clean = 0;
				(void) ffs_sbupdate(ump, MNT_WAIT, 0);
			}
		}
	}
	vfs_mountedfrom(mp, fspec);
	return (0);
}