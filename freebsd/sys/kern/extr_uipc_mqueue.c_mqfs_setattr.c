#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
struct vop_setattr_args {TYPE_3__* a_cred; struct vnode* a_vp; struct vattr* a_vap; } ;
struct vnode {int dummy; } ;
struct TYPE_6__ {int tv_sec; } ;
struct TYPE_5__ {int tv_sec; } ;
struct vattr {scalar_t__ va_type; int va_nlink; int va_fsid; int va_fileid; int va_blocksize; int va_flags; int va_rdev; int va_gen; scalar_t__ va_uid; scalar_t__ va_gid; scalar_t__ va_mode; int va_vaflags; TYPE_2__ va_mtime; TYPE_1__ va_atime; scalar_t__ va_bytes; } ;
struct thread {int dummy; } ;
struct mqfs_node {scalar_t__ mn_uid; scalar_t__ mn_gid; scalar_t__ mn_mode; int /*<<< orphan*/  mn_ctime; TYPE_2__ mn_mtime; TYPE_1__ mn_atime; } ;
typedef  scalar_t__ mode_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_7__ {scalar_t__ cr_uid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PRIV_MQ_ADMIN ; 
 int /*<<< orphan*/  VADMIN ; 
 int VA_UTIMES_NULL ; 
 scalar_t__ VNON ; 
 int VNOVAL ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,TYPE_3__*,struct thread*) ; 
 struct mqfs_node* VTON (struct vnode*) ; 
 int /*<<< orphan*/  VWRITE ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  groupmember (scalar_t__,TYPE_3__*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_timestamp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mqfs_setattr(struct vop_setattr_args *ap)
{
	struct mqfs_node *pn;
	struct vattr *vap;
	struct vnode *vp;
	struct thread *td;
	int c, error;
	uid_t uid;
	gid_t gid;

	td = curthread;
	vap = ap->a_vap;
	vp = ap->a_vp;
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

	pn = VTON(vp);

	error = c = 0;
	if (vap->va_uid == (uid_t)VNOVAL)
		uid = pn->mn_uid;
	else
		uid = vap->va_uid;
	if (vap->va_gid == (gid_t)VNOVAL)
		gid = pn->mn_gid;
	else
		gid = vap->va_gid;

	if (uid != pn->mn_uid || gid != pn->mn_gid) {
		/*
		 * To modify the ownership of a file, must possess VADMIN
		 * for that file.
		 */
		if ((error = VOP_ACCESS(vp, VADMIN, ap->a_cred, td)))
			return (error);

		/*
		 * XXXRW: Why is there a privilege check here: shouldn't the
		 * check in VOP_ACCESS() be enough?  Also, are the group bits
		 * below definitely right?
		 */
		if (((ap->a_cred->cr_uid != pn->mn_uid) || uid != pn->mn_uid ||
		    (gid != pn->mn_gid && !groupmember(gid, ap->a_cred))) &&
		    (error = priv_check(td, PRIV_MQ_ADMIN)) != 0)
			return (error);
		pn->mn_uid = uid;
		pn->mn_gid = gid;
		c = 1;
	}

	if (vap->va_mode != (mode_t)VNOVAL) {
		if ((ap->a_cred->cr_uid != pn->mn_uid) &&
		    (error = priv_check(td, PRIV_MQ_ADMIN)))
			return (error);
		pn->mn_mode = vap->va_mode;
		c = 1;
	}

	if (vap->va_atime.tv_sec != VNOVAL || vap->va_mtime.tv_sec != VNOVAL) {
		/* See the comment in ufs_vnops::ufs_setattr(). */
		if ((error = VOP_ACCESS(vp, VADMIN, ap->a_cred, td)) &&
		    ((vap->va_vaflags & VA_UTIMES_NULL) == 0 ||
		    (error = VOP_ACCESS(vp, VWRITE, ap->a_cred, td))))
			return (error);
		if (vap->va_atime.tv_sec != VNOVAL) {
			pn->mn_atime = vap->va_atime;
		}
		if (vap->va_mtime.tv_sec != VNOVAL) {
			pn->mn_mtime = vap->va_mtime;
		}
		c = 1;
	}
	if (c) {
		vfs_timestamp(&pn->mn_ctime);
	}
	return (0);
}