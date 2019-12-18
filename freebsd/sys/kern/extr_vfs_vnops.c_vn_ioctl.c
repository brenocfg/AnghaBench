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
typedef  int /*<<< orphan*/  u_long ;
struct vnode {int v_type; } ;
struct vattr {int va_size; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct fiobmap2_arg {int /*<<< orphan*/  runb; int /*<<< orphan*/  runp; int /*<<< orphan*/  bn; } ;
struct file {int f_offset; int /*<<< orphan*/  f_flag; int /*<<< orphan*/  f_cred; struct vnode* f_vnode; } ;

/* Variables and functions */
 int ENOTTY ; 
#define  FIOASYNC 134 
#define  FIOBMAP2 133 
#define  FIONBIO 132 
#define  FIONREAD 131 
 int LK_RETRY ; 
 int LK_SHARED ; 
#define  VCHR 130 
#define  VDIR 129 
 int VOP_BMAP (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 int VOP_IOCTL (struct vnode*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
#define  VREG 128 
 int mac_vnode_check_read (struct ucred*,int /*<<< orphan*/ ,struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
vn_ioctl(struct file *fp, u_long com, void *data, struct ucred *active_cred,
    struct thread *td)
{
	struct vattr vattr;
	struct vnode *vp;
	struct fiobmap2_arg *bmarg;
	int error;

	vp = fp->f_vnode;
	switch (vp->v_type) {
	case VDIR:
	case VREG:
		switch (com) {
		case FIONREAD:
			vn_lock(vp, LK_SHARED | LK_RETRY);
			error = VOP_GETATTR(vp, &vattr, active_cred);
			VOP_UNLOCK(vp, 0);
			if (error == 0)
				*(int *)data = vattr.va_size - fp->f_offset;
			return (error);
		case FIOBMAP2:
			bmarg = (struct fiobmap2_arg *)data;
			vn_lock(vp, LK_SHARED | LK_RETRY);
#ifdef MAC
			error = mac_vnode_check_read(active_cred, fp->f_cred,
			    vp);
			if (error == 0)
#endif
				error = VOP_BMAP(vp, bmarg->bn, NULL,
				    &bmarg->bn, &bmarg->runp, &bmarg->runb);
			VOP_UNLOCK(vp, 0);
			return (error);
		case FIONBIO:
		case FIOASYNC:
			return (0);
		default:
			return (VOP_IOCTL(vp, com, data, fp->f_flag,
			    active_cred, td));
		}
		break;
	case VCHR:
		return (VOP_IOCTL(vp, com, data, fp->f_flag,
		    active_cred, td));
	default:
		return (ENOTTY);
	}
}