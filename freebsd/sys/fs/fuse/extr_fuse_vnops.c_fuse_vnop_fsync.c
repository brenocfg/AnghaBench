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
struct vop_fsync_args {int a_waitfor; struct thread* a_td; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int fuse_internal_fsync (struct vnode*,struct thread*,int,int) ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 
 int vop_stdfsync (struct vop_fsync_args*) ; 

__attribute__((used)) static int
fuse_vnop_fsync(struct vop_fsync_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct thread *td = ap->a_td;
	int waitfor = ap->a_waitfor;
	int err = 0;

	if (fuse_isdeadfs(vp)) {
		return 0;
	}
	if ((err = vop_stdfsync(ap)))
		return err;

	return fuse_internal_fsync(vp, td, waitfor, false);
}