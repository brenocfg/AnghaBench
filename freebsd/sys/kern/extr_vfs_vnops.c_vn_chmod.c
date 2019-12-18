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
struct file {struct vnode* f_vnode; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_VNODE1 (struct vnode*) ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int setfmode (struct thread*,struct ucred*,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

int
vn_chmod(struct file *fp, mode_t mode, struct ucred *active_cred,
    struct thread *td)
{
	struct vnode *vp;

	vp = fp->f_vnode;
#ifdef AUDIT
	vn_lock(vp, LK_SHARED | LK_RETRY);
	AUDIT_ARG_VNODE1(vp);
	VOP_UNLOCK(vp, 0);
#endif
	return (setfmode(td, active_cred, vp, mode));
}