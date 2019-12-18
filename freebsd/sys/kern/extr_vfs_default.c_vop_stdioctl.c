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
struct vop_ioctl_args {int a_command; int /*<<< orphan*/ * a_data; int /*<<< orphan*/  a_cred; struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/  v_type; } ;
struct vattr {int /*<<< orphan*/  va_size; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int EBADF ; 
 int ENOTTY ; 
 int ENXIO ; 
#define  FIOSEEKDATA 129 
#define  FIOSEEKHOLE 128 
 int /*<<< orphan*/  LK_SHARED ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VREG ; 
 int vn_lock (struct vnode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vop_stdioctl(struct vop_ioctl_args *ap)
{
	struct vnode *vp;
	struct vattr va;
	off_t *offp;
	int error;

	switch (ap->a_command) {
	case FIOSEEKDATA:
	case FIOSEEKHOLE:
		vp = ap->a_vp;
		error = vn_lock(vp, LK_SHARED);
		if (error != 0)
			return (EBADF);
		if (vp->v_type == VREG)
			error = VOP_GETATTR(vp, &va, ap->a_cred);
		else
			error = ENOTTY;
		if (error == 0) {
			offp = ap->a_data;
			if (*offp < 0 || *offp >= va.va_size)
				error = ENXIO;
			else if (ap->a_command == FIOSEEKHOLE)
				*offp = va.va_size;
		}
		VOP_UNLOCK(vp, 0);
		break;
	default:
		error = ENOTTY;
		break;
	}
	return (error);
}