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
struct mount {int mnt_flag; int /*<<< orphan*/  mnt_optnew; } ;
struct iso_mnt {struct vnode* im_devvp; } ;
typedef  int /*<<< orphan*/  accmode_t ;

/* Variables and functions */
 int EINVAL ; 
 int FOLLOW ; 
 int LOCKLEAF ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int MNT_RDONLY ; 
 int MNT_UPDATE ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,struct thread*) ; 
 int /*<<< orphan*/  PRIV_VFS_MOUNT_PERM ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 struct iso_mnt* VFSTOISOFS (struct mount*) ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  VREAD ; 
 struct thread* curthread ; 
 int iso_mountfs (struct vnode*,struct mount*) ; 
 int namei (struct nameidata*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_flagopt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* vfs_getopts (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  vfs_mountedfrom (struct mount*,char*) ; 
 int /*<<< orphan*/  vn_isdisk (struct vnode*,int*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
cd9660_mount(struct mount *mp)
{
	struct vnode *devvp;
	struct thread *td;
	char *fspec;
	int error;
	accmode_t accmode;
	struct nameidata ndp;
	struct iso_mnt *imp = NULL;

	td = curthread;

	/*
	 * Unconditionally mount as read-only.
	 */
	MNT_ILOCK(mp);
	mp->mnt_flag |= MNT_RDONLY;
	MNT_IUNLOCK(mp);

	fspec = vfs_getopts(mp->mnt_optnew, "from", &error);
	if (error)
		return (error);

	imp = VFSTOISOFS(mp);

	if (mp->mnt_flag & MNT_UPDATE) {
		if (vfs_flagopt(mp->mnt_optnew, "export", NULL, 0))
			return (0);
	}
	/*
	 * Not an update, or updating the name: look up the name
	 * and verify that it refers to a sensible block device.
	 */
	NDINIT(&ndp, LOOKUP, FOLLOW | LOCKLEAF, UIO_SYSSPACE, fspec, td);
	if ((error = namei(&ndp)))
		return (error);
	NDFREE(&ndp, NDF_ONLY_PNBUF);
	devvp = ndp.ni_vp;

	if (!vn_isdisk(devvp, &error)) {
		vput(devvp);
		return (error);
	}

	/*
	 * Verify that user has necessary permissions on the device,
	 * or has superuser abilities
	 */
	accmode = VREAD;
	error = VOP_ACCESS(devvp, accmode, td->td_ucred, td);
	if (error)
		error = priv_check(td, PRIV_VFS_MOUNT_PERM);
	if (error) {
		vput(devvp);
		return (error);
	}

	if ((mp->mnt_flag & MNT_UPDATE) == 0) {
		error = iso_mountfs(devvp, mp);
		if (error)
			vrele(devvp);
	} else {
		if (devvp != imp->im_devvp)
			error = EINVAL;	/* needs translation */
		vput(devvp);
	}
	if (error)
		return (error);
	vfs_mountedfrom(mp, fspec);
	return (0);
}