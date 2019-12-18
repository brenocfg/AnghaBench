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
struct vop_read_args {int a_ioflag; struct ucred* a_cred; struct uio* a_uio; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct uio {int dummy; } ;
struct ucred {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_6__ {int flag; } ;
struct TYPE_5__ {TYPE_1__* td_proc; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int ENXIO ; 
 int FN_DIRECTIO ; 
 int IO_DIRECT ; 
 TYPE_3__* VTOFUD (struct vnode*) ; 
 TYPE_2__* curthread ; 
 int fuse_io_dispatch (struct vnode*,struct uio*,int,struct ucred*,int /*<<< orphan*/ ) ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 

__attribute__((used)) static int
fuse_vnop_read(struct vop_read_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct uio *uio = ap->a_uio;
	int ioflag = ap->a_ioflag;
	struct ucred *cred = ap->a_cred;
	pid_t pid = curthread->td_proc->p_pid;

	if (fuse_isdeadfs(vp)) {
		return ENXIO;
	}

	if (VTOFUD(vp)->flag & FN_DIRECTIO) {
		ioflag |= IO_DIRECT;
	}

	return fuse_io_dispatch(vp, uio, ioflag, cred, pid);
}