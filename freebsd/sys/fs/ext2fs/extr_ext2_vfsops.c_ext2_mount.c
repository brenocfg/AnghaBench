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
struct vnode {int /*<<< orphan*/  v_rdev; } ;
struct vfsoptlist {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {struct vnode* ni_vp; } ;
struct mount {int mnt_flag; struct vfsoptlist* mnt_optnew; } ;
struct m_ext2fs {int e2fs_ronly; char* e2fs_fsmnt; TYPE_1__* e2fs; scalar_t__ e2fs_wasvalid; } ;
struct ext2mount {struct m_ext2fs* um_e2fs; struct vnode* um_devvp; int /*<<< orphan*/  um_cp; } ;
typedef  int accmode_t ;
struct TYPE_2__ {int e2fs_state; } ;

/* Variables and functions */
 int E2FS_ERRORS ; 
 int E2FS_ISCLEAN ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int EPERM ; 
 int FOLLOW ; 
 int FORCECLOSE ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LOCKLEAF ; 
 int /*<<< orphan*/  LOOKUP ; 
 int MAXMNTLEN ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int MNT_RDONLY ; 
 int MNT_RELOAD ; 
 int MNT_UPDATE ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,struct thread*) ; 
 int /*<<< orphan*/  PRIV_VFS_MOUNT_PERM ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 struct ext2mount* VFSTOEXT2 (struct mount*) ; 
 int VFS_SYNC (struct mount*,int /*<<< orphan*/ ) ; 
 int VOP_ACCESS (struct vnode*,int,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int VREAD ; 
 int VWRITE ; 
 int WRITECLOSE ; 
 struct thread* curthread ; 
 scalar_t__ ext2_cgupdate (struct ext2mount*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2_check_sb_compat (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext2_flushfiles (struct mount*,int,struct thread*) ; 
 int ext2_mountfs (struct vnode*,struct mount*) ; 
 int /*<<< orphan*/  ext2_opts ; 
 int ext2_reload (struct mount*,struct thread*) ; 
 int /*<<< orphan*/  ext2_sbupdate (struct ext2mount*,int /*<<< orphan*/ ) ; 
 int g_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 scalar_t__ vfs_filteropt (struct vfsoptlist*,int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_flagopt (struct vfsoptlist*,char*,int*,int) ; 
 int vfs_getopt (struct vfsoptlist*,char*,void**,int*) ; 
 int /*<<< orphan*/  vfs_mountedfrom (struct mount*,char*) ; 
 int /*<<< orphan*/  vn_isdisk (struct vnode*,int*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
ext2_mount(struct mount *mp)
{
	struct vfsoptlist *opts;
	struct vnode *devvp;
	struct thread *td;
	struct ext2mount *ump = NULL;
	struct m_ext2fs *fs;
	struct nameidata nd, *ndp = &nd;
	accmode_t accmode;
	char *path, *fspec;
	int error, flags, len;

	td = curthread;
	opts = mp->mnt_optnew;

	if (vfs_filteropt(opts, ext2_opts))
		return (EINVAL);

	vfs_getopt(opts, "fspath", (void **)&path, NULL);
	/* Double-check the length of path.. */
	if (strlen(path) >= MAXMNTLEN)
		return (ENAMETOOLONG);

	fspec = NULL;
	error = vfs_getopt(opts, "from", (void **)&fspec, &len);
	if (!error && fspec[len - 1] != '\0')
		return (EINVAL);

	/*
	 * If updating, check whether changing from read-only to
	 * read/write; if there is no device name, that's all we do.
	 */
	if (mp->mnt_flag & MNT_UPDATE) {
		ump = VFSTOEXT2(mp);
		fs = ump->um_e2fs;
		error = 0;
		if (fs->e2fs_ronly == 0 &&
		    vfs_flagopt(opts, "ro", NULL, 0)) {
			error = VFS_SYNC(mp, MNT_WAIT);
			if (error)
				return (error);
			flags = WRITECLOSE;
			if (mp->mnt_flag & MNT_FORCE)
				flags |= FORCECLOSE;
			error = ext2_flushfiles(mp, flags, td);
			if (error == 0 && fs->e2fs_wasvalid &&
			    ext2_cgupdate(ump, MNT_WAIT) == 0) {
				fs->e2fs->e2fs_state |= E2FS_ISCLEAN;
				ext2_sbupdate(ump, MNT_WAIT);
			}
			fs->e2fs_ronly = 1;
			vfs_flagopt(opts, "ro", &mp->mnt_flag, MNT_RDONLY);
			g_topology_lock();
			g_access(ump->um_cp, 0, -1, 0);
			g_topology_unlock();
		}
		if (!error && (mp->mnt_flag & MNT_RELOAD))
			error = ext2_reload(mp, td);
		if (error)
			return (error);
		devvp = ump->um_devvp;
		if (fs->e2fs_ronly && !vfs_flagopt(opts, "ro", NULL, 0)) {
			if (ext2_check_sb_compat(fs->e2fs, devvp->v_rdev, 0))
				return (EPERM);

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
			g_topology_lock();
			error = g_access(ump->um_cp, 0, 1, 0);
			g_topology_unlock();
			if (error)
				return (error);

			if ((fs->e2fs->e2fs_state & E2FS_ISCLEAN) == 0 ||
			    (fs->e2fs->e2fs_state & E2FS_ERRORS)) {
				if (mp->mnt_flag & MNT_FORCE) {
					printf(
"WARNING: %s was not properly dismounted\n", fs->e2fs_fsmnt);
				} else {
					printf(
"WARNING: R/W mount of %s denied.  Filesystem is not clean - run fsck\n",
					    fs->e2fs_fsmnt);
					return (EPERM);
				}
			}
			fs->e2fs->e2fs_state &= ~E2FS_ISCLEAN;
			(void)ext2_cgupdate(ump, MNT_WAIT);
			fs->e2fs_ronly = 0;
			MNT_ILOCK(mp);
			mp->mnt_flag &= ~MNT_RDONLY;
			MNT_IUNLOCK(mp);
		}
		if (vfs_flagopt(opts, "export", NULL, 0)) {
			/* Process export requests in vfs_mount.c. */
			return (error);
		}
	}

	/*
	 * Not an update, or updating the name: look up the name
	 * and verify that it refers to a sensible disk device.
	 */
	if (fspec == NULL)
		return (EINVAL);
	NDINIT(ndp, LOOKUP, FOLLOW | LOCKLEAF, UIO_SYSSPACE, fspec, td);
	if ((error = namei(ndp)) != 0)
		return (error);
	NDFREE(ndp, NDF_ONLY_PNBUF);
	devvp = ndp->ni_vp;

	if (!vn_isdisk(devvp, &error)) {
		vput(devvp);
		return (error);
	}

	/*
	 * If mount by non-root, then verify that user has necessary
	 * permissions on the device.
	 *
	 * XXXRW: VOP_ACCESS() enough?
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
		error = ext2_mountfs(devvp, mp);
	} else {
		if (devvp != ump->um_devvp) {
			vput(devvp);
			return (EINVAL);	/* needs translation */
		} else
			vput(devvp);
	}
	if (error) {
		vrele(devvp);
		return (error);
	}
	ump = VFSTOEXT2(mp);
	fs = ump->um_e2fs;

	/*
	 * Note that this strncpy() is ok because of a check at the start
	 * of ext2_mount().
	 */
	strncpy(fs->e2fs_fsmnt, path, MAXMNTLEN);
	fs->e2fs_fsmnt[MAXMNTLEN - 1] = '\0';
	vfs_mountedfrom(mp, fspec);
	return (0);
}