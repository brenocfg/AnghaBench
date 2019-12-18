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
struct vop_mkdir_args {struct vattr* a_vap; struct componentname* a_cnp; struct vnode** a_vpp; struct vnode* a_dvp; } ;
struct vnode {int dummy; } ;
struct vattr {int /*<<< orphan*/  va_mode; int /*<<< orphan*/  va_type; } ;
struct fuse_mkdir_in {int /*<<< orphan*/  umask; int /*<<< orphan*/  mode; } ;
struct componentname {int dummy; } ;
typedef  int /*<<< orphan*/  fmdi ;
struct TYPE_6__ {TYPE_2__* td_proc; } ;
struct TYPE_5__ {TYPE_1__* p_fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd_cmask; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  FUSE_MKDIR ; 
 int /*<<< orphan*/  MAKEIMODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VDIR ; 
 TYPE_3__* curthread ; 
 int fuse_internal_newentry (struct vnode*,struct vnode**,struct componentname*,int /*<<< orphan*/ ,struct fuse_mkdir_in*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 

__attribute__((used)) static int
fuse_vnop_mkdir(struct vop_mkdir_args *ap)
{
	struct vnode *dvp = ap->a_dvp;
	struct vnode **vpp = ap->a_vpp;
	struct componentname *cnp = ap->a_cnp;
	struct vattr *vap = ap->a_vap;

	struct fuse_mkdir_in fmdi;

	if (fuse_isdeadfs(dvp)) {
		return ENXIO;
	}
	fmdi.mode = MAKEIMODE(vap->va_type, vap->va_mode);
	fmdi.umask = curthread->td_proc->p_fd->fd_cmask;

	return (fuse_internal_newentry(dvp, vpp, cnp, FUSE_MKDIR, &fmdi,
	    sizeof(fmdi), VDIR));
}