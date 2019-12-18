#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
struct vop_setattr_args {TYPE_3__* a_cred; struct vnode* a_vp; struct vattr* a_vap; } ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_mount; TYPE_2__* v_rdev; struct devfs_dirent* v_data; } ;
struct TYPE_10__ {int tv_sec; } ;
struct TYPE_7__ {int tv_sec; } ;
struct vattr {scalar_t__ va_type; int va_nlink; int va_fsid; int va_fileid; int va_blocksize; int va_flags; int va_rdev; int va_gen; scalar_t__ va_uid; scalar_t__ va_gid; scalar_t__ va_mode; TYPE_4__ va_mtime; TYPE_1__ va_atime; scalar_t__ va_bytes; } ;
struct thread {int dummy; } ;
struct devfs_dirent {scalar_t__ de_uid; scalar_t__ de_gid; scalar_t__ de_mode; TYPE_4__ de_mtime; TYPE_1__ de_atime; struct devfs_dirent* de_dir; } ;
typedef  scalar_t__ mode_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_11__ {int /*<<< orphan*/  dm_lock; } ;
struct TYPE_9__ {scalar_t__ cr_uid; } ;
struct TYPE_8__ {TYPE_4__ si_ctime; TYPE_4__ si_mtime; TYPE_1__ si_atime; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PRIV_VFS_ADMIN ; 
 int /*<<< orphan*/  PRIV_VFS_CHOWN ; 
 scalar_t__ VCHR ; 
 scalar_t__ VDIR ; 
 TYPE_6__* VFSTODEVFS (int /*<<< orphan*/ ) ; 
 scalar_t__ VNON ; 
 int VNOVAL ; 
 struct thread* curthread ; 
 int devfs_populate_vp (struct vnode*) ; 
 int /*<<< orphan*/  groupmember (scalar_t__,TYPE_3__*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_timestamp (TYPE_4__*) ; 
 int vn_utimes_perm (struct vnode*,struct vattr*,TYPE_3__*,struct thread*) ; 

__attribute__((used)) static int
devfs_setattr(struct vop_setattr_args *ap)
{
	struct devfs_dirent *de;
	struct vattr *vap;
	struct vnode *vp;
	struct thread *td;
	int c, error;
	uid_t uid;
	gid_t gid;

	vap = ap->a_vap;
	vp = ap->a_vp;
	td = curthread;
	if ((vap->va_type != VNON) ||
	    (vap->va_nlink != VNOVAL) ||
	    (vap->va_fsid != VNOVAL) ||
	    (vap->va_fileid != VNOVAL) ||
	    (vap->va_blocksize != VNOVAL) ||
	    (vap->va_flags != VNOVAL && vap->va_flags != 0) ||
	    (vap->va_rdev != VNOVAL) ||
	    ((int)vap->va_bytes != VNOVAL) ||
	    (vap->va_gen != VNOVAL)) {
		return (EINVAL);
	}

	error = devfs_populate_vp(vp);
	if (error != 0)
		return (error);

	de = vp->v_data;
	if (vp->v_type == VDIR)
		de = de->de_dir;

	c = 0;
	if (vap->va_uid == (uid_t)VNOVAL)
		uid = de->de_uid;
	else
		uid = vap->va_uid;
	if (vap->va_gid == (gid_t)VNOVAL)
		gid = de->de_gid;
	else
		gid = vap->va_gid;
	if (uid != de->de_uid || gid != de->de_gid) {
		if ((ap->a_cred->cr_uid != de->de_uid) || uid != de->de_uid ||
		    (gid != de->de_gid && !groupmember(gid, ap->a_cred))) {
			error = priv_check(td, PRIV_VFS_CHOWN);
			if (error != 0)
				goto ret;
		}
		de->de_uid = uid;
		de->de_gid = gid;
		c = 1;
	}

	if (vap->va_mode != (mode_t)VNOVAL) {
		if (ap->a_cred->cr_uid != de->de_uid) {
			error = priv_check(td, PRIV_VFS_ADMIN);
			if (error != 0)
				goto ret;
		}
		de->de_mode = vap->va_mode;
		c = 1;
	}

	if (vap->va_atime.tv_sec != VNOVAL || vap->va_mtime.tv_sec != VNOVAL) {
		error = vn_utimes_perm(vp, vap, ap->a_cred, td);
		if (error != 0)
			goto ret;
		if (vap->va_atime.tv_sec != VNOVAL) {
			if (vp->v_type == VCHR)
				vp->v_rdev->si_atime = vap->va_atime;
			else
				de->de_atime = vap->va_atime;
		}
		if (vap->va_mtime.tv_sec != VNOVAL) {
			if (vp->v_type == VCHR)
				vp->v_rdev->si_mtime = vap->va_mtime;
			else
				de->de_mtime = vap->va_mtime;
		}
		c = 1;
	}

	if (c) {
		if (vp->v_type == VCHR)
			vfs_timestamp(&vp->v_rdev->si_ctime);
		else
			vfs_timestamp(&de->de_mtime);
	}

ret:
	sx_xunlock(&VFSTODEVFS(vp->v_mount)->dm_lock);
	return (error);
}