#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct vattr {int /*<<< orphan*/  va_type; int /*<<< orphan*/  va_rdev; int /*<<< orphan*/  va_mode; } ;
struct fuse_mknod_in {int /*<<< orphan*/  umask; int /*<<< orphan*/  rdev; int /*<<< orphan*/  mode; } ;
struct fuse_data {int dummy; } ;
struct componentname {int dummy; } ;
typedef  int /*<<< orphan*/  fmni ;
struct TYPE_6__ {TYPE_2__* td_proc; } ;
struct TYPE_5__ {TYPE_1__* p_fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd_cmask; } ;

/* Variables and functions */
 size_t FUSE_COMPAT_MKNOD_IN_SIZE ; 
 int /*<<< orphan*/  FUSE_MKNOD ; 
 int /*<<< orphan*/  MAKEIMODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* curthread ; 
 struct fuse_data* fuse_get_mpdata (int /*<<< orphan*/ ) ; 
 int fuse_internal_newentry (struct vnode*,struct vnode**,struct componentname*,int /*<<< orphan*/ ,struct fuse_mknod_in*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ fuse_libabi_geq (struct fuse_data*,int,int) ; 

int
fuse_internal_mknod(struct vnode *dvp, struct vnode **vpp,
	struct componentname *cnp, struct vattr *vap)
{
	struct fuse_data *data;
	struct fuse_mknod_in fmni;
	size_t insize;

	data = fuse_get_mpdata(dvp->v_mount);

	fmni.mode = MAKEIMODE(vap->va_type, vap->va_mode);
	fmni.rdev = vap->va_rdev;
	if (fuse_libabi_geq(data, 7, 12)) {
		insize = sizeof(fmni);
		fmni.umask = curthread->td_proc->p_fd->fd_cmask;
	} else {
		insize = FUSE_COMPAT_MKNOD_IN_SIZE;
	}
	return (fuse_internal_newentry(dvp, vpp, cnp, FUSE_MKNOD, &fmni,
	    insize, vap->va_type));
}