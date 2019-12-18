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
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct file {int /*<<< orphan*/  f_cred; struct vnode* f_vnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_VNODE1 (struct vnode*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int VOP_POLL (struct vnode*,int,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int mac_vnode_check_poll (struct ucred*,int /*<<< orphan*/ ,struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
vn_poll(struct file *fp, int events, struct ucred *active_cred,
    struct thread *td)
{
	struct vnode *vp;
	int error;

	vp = fp->f_vnode;
#ifdef MAC
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	AUDIT_ARG_VNODE1(vp);
	error = mac_vnode_check_poll(active_cred, fp->f_cred, vp);
	VOP_UNLOCK(vp, 0);
	if (!error)
#endif

	error = VOP_POLL(vp, events, fp->f_cred, td);
	return (error);
}