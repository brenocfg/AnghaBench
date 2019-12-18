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
struct vattr {scalar_t__ va_size; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {struct vnode* ni_vp; } ;
struct mount {int dummy; } ;
typedef  scalar_t__ off_t ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int AUDITVNODE1 ; 
 int EINVAL ; 
 int EISDIR ; 
 int FOLLOW ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int,char const*,struct thread*) ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  OFF_MAX ; 
 int PCATCH ; 
 int /*<<< orphan*/  VATTR_NULL (struct vattr*) ; 
 scalar_t__ VDIR ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int VOP_SETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VWRITE ; 
 int V_WAIT ; 
 int mac_vnode_check_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode*) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vn_rangelock_unlock (struct vnode*,void*) ; 
 void* vn_rangelock_wlock (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vn_start_write (struct vnode*,struct mount**,int) ; 
 int vn_writechk (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
kern_truncate(struct thread *td, const char *path, enum uio_seg pathseg,
    off_t length)
{
	struct mount *mp;
	struct vnode *vp;
	void *rl_cookie;
	struct vattr vattr;
	struct nameidata nd;
	int error;

	if (length < 0)
		return(EINVAL);
	NDINIT(&nd, LOOKUP, FOLLOW | AUDITVNODE1, pathseg, path, td);
	if ((error = namei(&nd)) != 0)
		return (error);
	vp = nd.ni_vp;
	rl_cookie = vn_rangelock_wlock(vp, 0, OFF_MAX);
	if ((error = vn_start_write(vp, &mp, V_WAIT | PCATCH)) != 0) {
		vn_rangelock_unlock(vp, rl_cookie);
		vrele(vp);
		return (error);
	}
	NDFREE(&nd, NDF_ONLY_PNBUF);
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	if (vp->v_type == VDIR)
		error = EISDIR;
#ifdef MAC
	else if ((error = mac_vnode_check_write(td->td_ucred, NOCRED, vp))) {
	}
#endif
	else if ((error = vn_writechk(vp)) == 0 &&
	    (error = VOP_ACCESS(vp, VWRITE, td->td_ucred, td)) == 0) {
		VATTR_NULL(&vattr);
		vattr.va_size = length;
		error = VOP_SETATTR(vp, &vattr, td->td_ucred);
	}
	VOP_UNLOCK(vp, 0);
	vn_finished_write(mp);
	vn_rangelock_unlock(vp, rl_cookie);
	vrele(vp);
	return (error);
}