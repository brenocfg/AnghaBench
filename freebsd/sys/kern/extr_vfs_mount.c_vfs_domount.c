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
struct vnode {int v_vflag; } ;
struct vfsoptlist {int dummy; } ;
struct vfsconf {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {struct vnode* ni_vp; } ;

/* Variables and functions */
 int AUDITVNODE1 ; 
 int EBUSY ; 
 int ENAMETOOLONG ; 
 int ENODEV ; 
 int FOLLOW ; 
 int LOCKLEAF ; 
 int /*<<< orphan*/  LOOKUP ; 
 scalar_t__ MFSNAMELEN ; 
 scalar_t__ MNAMELEN ; 
 int MNT_EXPORTED ; 
 int MNT_NOCOVER ; 
 int MNT_NOSUID ; 
 int MNT_ROOTFS ; 
 int MNT_SUIDDIR ; 
 int MNT_UPDATE ; 
 int MNT_USER ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,struct thread*) ; 
 int /*<<< orphan*/  PRIV_VFS_MOUNT ; 
 int /*<<< orphan*/  PRIV_VFS_MOUNT_EXPORTED ; 
 int /*<<< orphan*/  PRIV_VFS_MOUNT_NONUSER ; 
 int /*<<< orphan*/  PRIV_VFS_MOUNT_SUIDDIR ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VV_ROOT ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ jailed (int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int namei (struct nameidata*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ usermount ; 
 struct vfsconf* vfs_byname (char const*) ; 
 struct vfsconf* vfs_byname_kld (char const*,struct thread*,int*) ; 
 int vfs_domount_first (struct thread*,struct vfsconf*,char*,struct vnode*,int,struct vfsoptlist**) ; 
 int vfs_domount_update (struct thread*,struct vnode*,int,struct vfsoptlist**) ; 
 int vn_path_to_global_path (struct thread*,struct vnode*,char*,scalar_t__) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static int
vfs_domount(
	struct thread *td,		/* Calling thread. */
	const char *fstype,		/* Filesystem type. */
	char *fspath,			/* Mount path. */
	uint64_t fsflags,		/* Flags common to all filesystems. */
	struct vfsoptlist **optlist	/* Options local to the filesystem. */
	)
{
	struct vfsconf *vfsp;
	struct nameidata nd;
	struct vnode *vp;
	char *pathbuf;
	int error;

	/*
	 * Be ultra-paranoid about making sure the type and fspath
	 * variables will fit in our mp buffers, including the
	 * terminating NUL.
	 */
	if (strlen(fstype) >= MFSNAMELEN || strlen(fspath) >= MNAMELEN)
		return (ENAMETOOLONG);

	if (jailed(td->td_ucred) || usermount == 0) {
		if ((error = priv_check(td, PRIV_VFS_MOUNT)) != 0)
			return (error);
	}

	/*
	 * Do not allow NFS export or MNT_SUIDDIR by unprivileged users.
	 */
	if (fsflags & MNT_EXPORTED) {
		error = priv_check(td, PRIV_VFS_MOUNT_EXPORTED);
		if (error)
			return (error);
	}
	if (fsflags & MNT_SUIDDIR) {
		error = priv_check(td, PRIV_VFS_MOUNT_SUIDDIR);
		if (error)
			return (error);
	}
	/*
	 * Silently enforce MNT_NOSUID and MNT_USER for unprivileged users.
	 */
	if ((fsflags & (MNT_NOSUID | MNT_USER)) != (MNT_NOSUID | MNT_USER)) {
		if (priv_check(td, PRIV_VFS_MOUNT_NONUSER) != 0)
			fsflags |= MNT_NOSUID | MNT_USER;
	}

	/* Load KLDs before we lock the covered vnode to avoid reversals. */
	vfsp = NULL;
	if ((fsflags & MNT_UPDATE) == 0) {
		/* Don't try to load KLDs if we're mounting the root. */
		if (fsflags & MNT_ROOTFS)
			vfsp = vfs_byname(fstype);
		else
			vfsp = vfs_byname_kld(fstype, td, &error);
		if (vfsp == NULL)
			return (ENODEV);
	}

	/*
	 * Get vnode to be covered or mount point's vnode in case of MNT_UPDATE.
	 */
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF | AUDITVNODE1,
	    UIO_SYSSPACE, fspath, td);
	error = namei(&nd);
	if (error != 0)
		return (error);
	NDFREE(&nd, NDF_ONLY_PNBUF);
	vp = nd.ni_vp;
	if ((fsflags & MNT_UPDATE) == 0) {
		if ((vp->v_vflag & VV_ROOT) != 0 &&
		    (fsflags & MNT_NOCOVER) != 0) {
			vput(vp);
			return (EBUSY);
		}
		pathbuf = malloc(MNAMELEN, M_TEMP, M_WAITOK);
		strcpy(pathbuf, fspath);
		error = vn_path_to_global_path(td, vp, pathbuf, MNAMELEN);
		/* debug.disablefullpath == 1 results in ENODEV */
		if (error == 0 || error == ENODEV) {
			error = vfs_domount_first(td, vfsp, pathbuf, vp,
			    fsflags, optlist);
		}
		free(pathbuf, M_TEMP);
	} else
		error = vfs_domount_update(td, vp, fsflags, optlist);

	return (error);
}