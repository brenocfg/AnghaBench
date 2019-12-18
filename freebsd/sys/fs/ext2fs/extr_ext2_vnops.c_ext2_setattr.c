#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
struct vop_setattr_args {struct ucred* a_cred; struct vnode* a_vp; struct vattr* a_vap; } ;
struct vnode {int v_type; TYPE_4__* v_mount; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int tv_sec; int /*<<< orphan*/  tv_nsec; } ;
struct TYPE_5__ {int tv_sec; int /*<<< orphan*/  tv_nsec; } ;
struct vattr {scalar_t__ va_type; int va_nlink; int va_fsid; int va_fileid; int va_blocksize; int va_rdev; int va_gen; int va_flags; scalar_t__ va_uid; scalar_t__ va_gid; int va_size; int va_vaflags; scalar_t__ va_mode; TYPE_3__ va_birthtime; TYPE_2__ va_mtime; TYPE_1__ va_atime; scalar_t__ va_bytes; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct inode {int i_flags; int i_flag; int i_atime; int i_mtime; int /*<<< orphan*/  i_birthnsec; int /*<<< orphan*/  i_birthtime; int /*<<< orphan*/  i_mtimensec; int /*<<< orphan*/  i_atimensec; } ;
typedef  scalar_t__ mode_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_8__ {int mnt_flag; } ;

/* Variables and functions */
 int APPEND ; 
 int EINVAL ; 
 int EISDIR ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int EROFS ; 
 int IMMUTABLE ; 
 int IN_ACCESS ; 
 int IN_CHANGE ; 
 int IN_MODIFIED ; 
 int IN_UPDATE ; 
 int MNT_RDONLY ; 
 int /*<<< orphan*/  PRIV_VFS_SYSFLAGS ; 
 int SF_APPEND ; 
 int SF_IMMUTABLE ; 
 int SF_SETTABLE ; 
 int UF_NODUMP ; 
 int /*<<< orphan*/  VADMIN ; 
 int VA_UTIMES_NULL ; 
#define  VDIR 130 
#define  VLNK 129 
 scalar_t__ VNON ; 
 int VNOVAL ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
#define  VREG 128 
 struct inode* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  VWRITE ; 
 struct thread* curthread ; 
 int ext2_chmod (struct vnode*,int,struct ucred*,struct thread*) ; 
 int ext2_chown (struct vnode*,scalar_t__,scalar_t__,struct ucred*,struct thread*) ; 
 int ext2_truncate (struct vnode*,int,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 int ext2_update (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int securelevel_gt (struct ucred*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_setattr(struct vop_setattr_args *ap)
{
	struct vattr *vap = ap->a_vap;
	struct vnode *vp = ap->a_vp;
	struct inode *ip = VTOI(vp);
	struct ucred *cred = ap->a_cred;
	struct thread *td = curthread;
	int error;

	/*
	 * Check for unsettable attributes.
	 */
	if ((vap->va_type != VNON) || (vap->va_nlink != VNOVAL) ||
	    (vap->va_fsid != VNOVAL) || (vap->va_fileid != VNOVAL) ||
	    (vap->va_blocksize != VNOVAL) || (vap->va_rdev != VNOVAL) ||
	    ((int)vap->va_bytes != VNOVAL) || (vap->va_gen != VNOVAL)) {
		return (EINVAL);
	}
	if (vap->va_flags != VNOVAL) {
		/* Disallow flags not supported by ext2fs. */
		if (vap->va_flags & ~(SF_APPEND | SF_IMMUTABLE | UF_NODUMP))
			return (EOPNOTSUPP);

		if (vp->v_mount->mnt_flag & MNT_RDONLY)
			return (EROFS);
		/*
		 * Callers may only modify the file flags on objects they
		 * have VADMIN rights for.
		 */
		if ((error = VOP_ACCESS(vp, VADMIN, cred, td)))
			return (error);
		/*
		 * Unprivileged processes and privileged processes in
		 * jail() are not permitted to unset system flags, or
		 * modify flags if any system flags are set.
		 * Privileged non-jail processes may not modify system flags
		 * if securelevel > 0 and any existing system flags are set.
		 */
		if (!priv_check_cred(cred, PRIV_VFS_SYSFLAGS)) {
			if (ip->i_flags & (SF_IMMUTABLE | SF_APPEND)) {
				error = securelevel_gt(cred, 0);
				if (error)
					return (error);
			}
		} else {
			if (ip->i_flags & (SF_IMMUTABLE | SF_APPEND) ||
			    ((vap->va_flags ^ ip->i_flags) & SF_SETTABLE))
				return (EPERM);
		}
		ip->i_flags = vap->va_flags;
		ip->i_flag |= IN_CHANGE;
		if (ip->i_flags & (IMMUTABLE | APPEND))
			return (0);
	}
	if (ip->i_flags & (IMMUTABLE | APPEND))
		return (EPERM);
	/*
	 * Go through the fields and update iff not VNOVAL.
	 */
	if (vap->va_uid != (uid_t)VNOVAL || vap->va_gid != (gid_t)VNOVAL) {
		if (vp->v_mount->mnt_flag & MNT_RDONLY)
			return (EROFS);
		if ((error = ext2_chown(vp, vap->va_uid, vap->va_gid, cred,
		    td)) != 0)
			return (error);
	}
	if (vap->va_size != VNOVAL) {
		/*
		 * Disallow write attempts on read-only file systems;
		 * unless the file is a socket, fifo, or a block or
		 * character device resident on the file system.
		 */
		switch (vp->v_type) {
		case VDIR:
			return (EISDIR);
		case VLNK:
		case VREG:
			if (vp->v_mount->mnt_flag & MNT_RDONLY)
				return (EROFS);
			break;
		default:
			break;
		}
		if ((error = ext2_truncate(vp, vap->va_size, 0, cred, td)) != 0)
			return (error);
	}
	if (vap->va_atime.tv_sec != VNOVAL || vap->va_mtime.tv_sec != VNOVAL) {
		if (vp->v_mount->mnt_flag & MNT_RDONLY)
			return (EROFS);
		/*
		 * From utimes(2):
		 * If times is NULL, ... The caller must be the owner of
		 * the file, have permission to write the file, or be the
		 * super-user.
		 * If times is non-NULL, ... The caller must be the owner of
		 * the file or be the super-user.
		 */
		if ((error = VOP_ACCESS(vp, VADMIN, cred, td)) &&
		    ((vap->va_vaflags & VA_UTIMES_NULL) == 0 ||
		    (error = VOP_ACCESS(vp, VWRITE, cred, td))))
			return (error);
		ip->i_flag |= IN_CHANGE | IN_MODIFIED;
		if (vap->va_atime.tv_sec != VNOVAL) {
			ip->i_flag &= ~IN_ACCESS;
			ip->i_atime = vap->va_atime.tv_sec;
			ip->i_atimensec = vap->va_atime.tv_nsec;
		}
		if (vap->va_mtime.tv_sec != VNOVAL) {
			ip->i_flag &= ~IN_UPDATE;
			ip->i_mtime = vap->va_mtime.tv_sec;
			ip->i_mtimensec = vap->va_mtime.tv_nsec;
		}
		ip->i_birthtime = vap->va_birthtime.tv_sec;
		ip->i_birthnsec = vap->va_birthtime.tv_nsec;
		error = ext2_update(vp, 0);
		if (error)
			return (error);
	}
	error = 0;
	if (vap->va_mode != (mode_t)VNOVAL) {
		if (vp->v_mount->mnt_flag & MNT_RDONLY)
			return (EROFS);
		error = ext2_chmod(vp, (int)vap->va_mode, cred, td);
	}
	return (error);
}