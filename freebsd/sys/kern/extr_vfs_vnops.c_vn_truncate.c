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
struct vnode {scalar_t__ v_type; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;
struct file {int f_flag; int /*<<< orphan*/  f_cred; struct vnode* f_vnode; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_VNODE1 (struct vnode*) ; 
 int EISDIR ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  OFF_MAX ; 
 int O_FSYNC ; 
 int PCATCH ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int V_WAIT ; 
 int mac_vnode_check_write (struct ucred*,int /*<<< orphan*/ ,struct vnode*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vn_rangelock_unlock (struct vnode*,void*) ; 
 void* vn_rangelock_wlock (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vn_start_write (struct vnode*,struct mount**,int) ; 
 int vn_truncate_locked (struct vnode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vn_truncate(struct file *fp, off_t length, struct ucred *active_cred,
    struct thread *td)
{
	struct mount *mp;
	struct vnode *vp;
	void *rl_cookie;
	int error;

	vp = fp->f_vnode;

	/*
	 * Lock the whole range for truncation.  Otherwise split i/o
	 * might happen partly before and partly after the truncation.
	 */
	rl_cookie = vn_rangelock_wlock(vp, 0, OFF_MAX);
	error = vn_start_write(vp, &mp, V_WAIT | PCATCH);
	if (error)
		goto out1;
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	AUDIT_ARG_VNODE1(vp);
	if (vp->v_type == VDIR) {
		error = EISDIR;
		goto out;
	}
#ifdef MAC
	error = mac_vnode_check_write(active_cred, fp->f_cred, vp);
	if (error)
		goto out;
#endif
	error = vn_truncate_locked(vp, length, (fp->f_flag & O_FSYNC) != 0,
	    fp->f_cred);
out:
	VOP_UNLOCK(vp, 0);
	vn_finished_write(mp);
out1:
	vn_rangelock_unlock(vp, rl_cookie);
	return (error);
}