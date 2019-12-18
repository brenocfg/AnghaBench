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
typedef  scalar_t__ uid_t ;
struct vop_setattr_args {struct vnode* a_vp; struct ucred* a_cred; struct vattr* a_vap; } ;
struct vnode {int v_vflag; int v_type; TYPE_1__* v_mount; } ;
struct TYPE_4__ {scalar_t__ tv_sec; } ;
struct vattr {int va_type; scalar_t__ va_nlink; scalar_t__ va_fsid; scalar_t__ va_fileid; scalar_t__ va_blocksize; scalar_t__ va_rdev; scalar_t__ va_bytes; scalar_t__ va_gen; int va_uid; int va_gid; scalar_t__ va_flags; scalar_t__ va_size; int va_mode; TYPE_2__ va_mtime; TYPE_2__ va_atime; } ;
struct ucred {scalar_t__ cr_uid; } ;
struct thread {int dummy; } ;
struct msdosfsmount {scalar_t__ pm_uid; int pm_gid; int pm_flags; } ;
struct denode {int /*<<< orphan*/  de_flag; int /*<<< orphan*/  de_Attributes; int /*<<< orphan*/  de_MTime; int /*<<< orphan*/  de_MDate; int /*<<< orphan*/  de_ADate; struct msdosfsmount* de_pmp; } ;
typedef  int mode_t ;
typedef  int gid_t ;
struct TYPE_3__ {int mnt_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ARCHIVE ; 
 int /*<<< orphan*/  ATTR_HIDDEN ; 
 int /*<<< orphan*/  ATTR_READONLY ; 
 int /*<<< orphan*/  ATTR_SYSTEM ; 
 int /*<<< orphan*/  DE_ACCESS ; 
 int /*<<< orphan*/  DE_MODIFIED ; 
 int /*<<< orphan*/  DE_UPDATE ; 
 int EINVAL ; 
 int EISDIR ; 
 int EOPNOTSUPP ; 
 int EROFS ; 
 int MNT_RDONLY ; 
 int MSDOSFSMNT_NOWIN95 ; 
 int /*<<< orphan*/  PRIV_VFS_ADMIN ; 
 int /*<<< orphan*/  PRIV_VFS_CHOWN ; 
 int S_IWUSR ; 
 int UF_ARCHIVE ; 
 int UF_HIDDEN ; 
 int UF_READONLY ; 
 int UF_SYSTEM ; 
#define  VDIR 129 
 int VNON ; 
 scalar_t__ VNOVAL ; 
#define  VREG 128 
 struct denode* VTODE (struct vnode*) ; 
 int VV_ROOT ; 
 struct thread* curthread ; 
 int detrunc (struct denode*,scalar_t__,int /*<<< orphan*/ ,struct ucred*) ; 
 int deupdat (struct denode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  groupmember (int,struct ucred*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timespec2fattime (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vn_utimes_perm (struct vnode*,struct vattr*,struct ucred*,struct thread*) ; 

__attribute__((used)) static int
msdosfs_setattr(struct vop_setattr_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct denode *dep = VTODE(ap->a_vp);
	struct msdosfsmount *pmp = dep->de_pmp;
	struct vattr *vap = ap->a_vap;
	struct ucred *cred = ap->a_cred;
	struct thread *td = curthread;
	int error = 0;

#ifdef MSDOSFS_DEBUG
	printf("msdosfs_setattr(): vp %p, vap %p, cred %p\n",
	    ap->a_vp, vap, cred);
#endif

	/*
	 * Check for unsettable attributes.
	 */
	if ((vap->va_type != VNON) || (vap->va_nlink != VNOVAL) ||
	    (vap->va_fsid != VNOVAL) || (vap->va_fileid != VNOVAL) ||
	    (vap->va_blocksize != VNOVAL) || (vap->va_rdev != VNOVAL) ||
	    (vap->va_bytes != VNOVAL) || (vap->va_gen != VNOVAL)) {
#ifdef MSDOSFS_DEBUG
		printf("msdosfs_setattr(): returning EINVAL\n");
		printf("    va_type %d, va_nlink %llx, va_fsid %llx, va_fileid %llx\n",
		    vap->va_type, (unsigned long long)vap->va_nlink,
		    (unsigned long long)vap->va_fsid,
		    (unsigned long long)vap->va_fileid);
		printf("    va_blocksize %lx, va_rdev %llx, va_bytes %llx, va_gen %lx\n",
		    vap->va_blocksize, (unsigned long long)vap->va_rdev,
		    (unsigned long long)vap->va_bytes, vap->va_gen);
		printf("    va_uid %x, va_gid %x\n",
		    vap->va_uid, vap->va_gid);
#endif
		return (EINVAL);
	}

	/*
	 * We don't allow setting attributes on the root directory.
	 * The special case for the root directory is because before
	 * FAT32, the root directory didn't have an entry for itself
	 * (and was otherwise special).  With FAT32, the root
	 * directory is not so special, but still doesn't have an
	 * entry for itself.
	 */
	if (vp->v_vflag & VV_ROOT)
		return (EINVAL);

	if (vap->va_flags != VNOVAL) {
		if (vp->v_mount->mnt_flag & MNT_RDONLY)
			return (EROFS);
		if (cred->cr_uid != pmp->pm_uid) {
			error = priv_check_cred(cred, PRIV_VFS_ADMIN);
			if (error)
				return (error);
		}
		/*
		 * We are very inconsistent about handling unsupported
		 * attributes.  We ignored the access time and the
		 * read and execute bits.  We were strict for the other
		 * attributes.
		 */
		if (vap->va_flags & ~(UF_ARCHIVE | UF_HIDDEN | UF_READONLY |
		    UF_SYSTEM))
			return EOPNOTSUPP;
		if (vap->va_flags & UF_ARCHIVE)
			dep->de_Attributes |= ATTR_ARCHIVE;
		else
			dep->de_Attributes &= ~ATTR_ARCHIVE;
		if (vap->va_flags & UF_HIDDEN)
			dep->de_Attributes |= ATTR_HIDDEN;
		else
			dep->de_Attributes &= ~ATTR_HIDDEN;
		/* We don't allow changing the readonly bit on directories. */
		if (vp->v_type != VDIR) {
			if (vap->va_flags & UF_READONLY)
				dep->de_Attributes |= ATTR_READONLY;
			else
				dep->de_Attributes &= ~ATTR_READONLY;
		}
		if (vap->va_flags & UF_SYSTEM)
			dep->de_Attributes |= ATTR_SYSTEM;
		else
			dep->de_Attributes &= ~ATTR_SYSTEM;
		dep->de_flag |= DE_MODIFIED;
	}

	if (vap->va_uid != (uid_t)VNOVAL || vap->va_gid != (gid_t)VNOVAL) {
		uid_t uid;
		gid_t gid;

		if (vp->v_mount->mnt_flag & MNT_RDONLY)
			return (EROFS);
		uid = vap->va_uid;
		if (uid == (uid_t)VNOVAL)
			uid = pmp->pm_uid;
		gid = vap->va_gid;
		if (gid == (gid_t)VNOVAL)
			gid = pmp->pm_gid;
		if (cred->cr_uid != pmp->pm_uid || uid != pmp->pm_uid ||
		    (gid != pmp->pm_gid && !groupmember(gid, cred))) {
			error = priv_check_cred(cred, PRIV_VFS_CHOWN);
			if (error)
				return (error);
		}
		if (uid != pmp->pm_uid || gid != pmp->pm_gid)
			return EINVAL;
	}

	if (vap->va_size != VNOVAL) {
		switch (vp->v_type) {
		case VDIR:
			return (EISDIR);
		case VREG:
			/*
			 * Truncation is only supported for regular files,
			 * Disallow it if the filesystem is read-only.
			 */
			if (vp->v_mount->mnt_flag & MNT_RDONLY)
				return (EROFS);
			break;
		default:
			/*
			 * According to POSIX, the result is unspecified
			 * for file types other than regular files,
			 * directories and shared memory objects.  We
			 * don't support any file types except regular
			 * files and directories in this file system, so
			 * this (default) case is unreachable and can do
			 * anything.  Keep falling through to detrunc()
			 * for now.
			 */
			break;
		}
		error = detrunc(dep, vap->va_size, 0, cred);
		if (error)
			return error;
	}
	if (vap->va_atime.tv_sec != VNOVAL || vap->va_mtime.tv_sec != VNOVAL) {
		if (vp->v_mount->mnt_flag & MNT_RDONLY)
			return (EROFS);
		error = vn_utimes_perm(vp, vap, cred, td);
		if (error != 0)
			return (error);
		if ((pmp->pm_flags & MSDOSFSMNT_NOWIN95) == 0 &&
		    vap->va_atime.tv_sec != VNOVAL) {
			dep->de_flag &= ~DE_ACCESS;
			timespec2fattime(&vap->va_atime, 0,
			    &dep->de_ADate, NULL, NULL);
		}
		if (vap->va_mtime.tv_sec != VNOVAL) {
			dep->de_flag &= ~DE_UPDATE;
			timespec2fattime(&vap->va_mtime, 0,
			    &dep->de_MDate, &dep->de_MTime, NULL);
		}
		/*
		 * We don't set the archive bit when modifying the time of
		 * a directory to emulate the Windows/DOS behavior.
		 */
		if (vp->v_type != VDIR)
			dep->de_Attributes |= ATTR_ARCHIVE;
		dep->de_flag |= DE_MODIFIED;
	}
	/*
	 * DOS files only have the ability to have their writability
	 * attribute set, so we use the owner write bit to set the readonly
	 * attribute.
	 */
	if (vap->va_mode != (mode_t)VNOVAL) {
		if (vp->v_mount->mnt_flag & MNT_RDONLY)
			return (EROFS);
		if (cred->cr_uid != pmp->pm_uid) {
			error = priv_check_cred(cred, PRIV_VFS_ADMIN);
			if (error)
				return (error);
		}
		if (vp->v_type != VDIR) {
			/* We ignore the read and execute bits. */
			if (vap->va_mode & S_IWUSR)
				dep->de_Attributes &= ~ATTR_READONLY;
			else
				dep->de_Attributes |= ATTR_READONLY;
			dep->de_Attributes |= ATTR_ARCHIVE;
			dep->de_flag |= DE_MODIFIED;
		}
	}
	return (deupdat(dep, 0));
}