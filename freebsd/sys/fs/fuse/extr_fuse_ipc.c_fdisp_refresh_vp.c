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
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct thread {TYPE_1__* td_proc; } ;
struct fuse_dispatcher {int dummy; } ;
typedef  enum fuse_opcode { ____Placeholder_fuse_opcode } fuse_opcode ;
struct TYPE_2__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECTIFY_TDCR (struct thread*,struct ucred*) ; 
 int /*<<< orphan*/  VTOI (struct vnode*) ; 
 void fdisp_refresh_pid (struct fuse_dispatcher*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*) ; 
 int /*<<< orphan*/  vnode_mount (struct vnode*) ; 

void
fdisp_refresh_vp(struct fuse_dispatcher *fdip, enum fuse_opcode op,
    struct vnode *vp, struct thread *td, struct ucred *cred)
{
	RECTIFY_TDCR(td, cred);
	return fdisp_refresh_pid(fdip, op, vnode_mount(vp), VTOI(vp),
	    td->td_proc->p_pid, cred);
}