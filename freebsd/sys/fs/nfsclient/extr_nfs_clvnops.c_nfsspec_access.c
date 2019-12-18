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
struct vop_access_args {int a_accmode; struct vnode* a_vp; struct ucred* a_cred; } ;
struct vnode {int v_type; TYPE_1__* v_mount; } ;
struct vattr {int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; int /*<<< orphan*/  va_mode; } ;
struct ucred {int dummy; } ;
typedef  int accmode_t ;
struct TYPE_2__ {int mnt_flag; } ;

/* Variables and functions */
 int EROFS ; 
 int MNT_RDONLY ; 
#define  VDIR 130 
#define  VLNK 129 
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
#define  VREG 128 
 int VWRITE ; 
 int vaccess (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ucred*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfsspec_access(struct vop_access_args *ap)
{
	struct vattr *vap;
	struct ucred *cred = ap->a_cred;
	struct vnode *vp = ap->a_vp;
	accmode_t accmode = ap->a_accmode;
	struct vattr vattr;
	int error;

	/*
	 * Disallow write attempts on filesystems mounted read-only;
	 * unless the file is a socket, fifo, or a block or character
	 * device resident on the filesystem.
	 */
	if ((accmode & VWRITE) && (vp->v_mount->mnt_flag & MNT_RDONLY)) {
		switch (vp->v_type) {
		case VREG:
		case VDIR:
		case VLNK:
			return (EROFS);
		default:
			break;
		}
	}
	vap = &vattr;
	error = VOP_GETATTR(vp, vap, cred);
	if (error)
		goto out;
	error  = vaccess(vp->v_type, vap->va_mode, vap->va_uid, vap->va_gid,
	    accmode, cred, NULL);
out:
	return error;
}