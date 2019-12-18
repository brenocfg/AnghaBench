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
struct vop_close_args {int a_fflag; struct thread* a_td; struct ucred* a_cred; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct thread {TYPE_1__* td_proc; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_4__ {int flag; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int FN_SIZECHANGE ; 
 int IO_NDELAY ; 
 TYPE_2__* VTOFUD (struct vnode*) ; 
 int fuse_flush (struct vnode*,struct ucred*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 
 int /*<<< orphan*/  fuse_vnode_savesize (struct vnode*,struct ucred*,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_isdir (struct vnode*) ; 

__attribute__((used)) static int
fuse_vnop_close(struct vop_close_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct ucred *cred = ap->a_cred;
	int fflag = ap->a_fflag;
	struct thread *td = ap->a_td;
	pid_t pid = td->td_proc->p_pid;
	int err = 0;

	if (fuse_isdeadfs(vp))
		return 0;
	if (vnode_isdir(vp))
		return 0;
	if (fflag & IO_NDELAY)
		return 0;

	err = fuse_flush(vp, cred, pid, fflag);
	/* TODO: close the file handle, if we're sure it's no longer used */
	if ((VTOFUD(vp)->flag & FN_SIZECHANGE) != 0) {
		fuse_vnode_savesize(vp, cred, td->td_proc->p_pid);
	}
	return err;
}