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
struct vop_ioctl_args {int a_command; int /*<<< orphan*/  a_cred; scalar_t__ a_data; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int EBADF ; 
 int ENOTTY ; 
#define  FIOSEEKDATA 129 
#define  FIOSEEKHOLE 128 
 int /*<<< orphan*/  LK_SHARED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int ufs_bmap_seekdata (struct vnode*,int /*<<< orphan*/ *) ; 
 int vn_bmap_seekhole (struct vnode*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vn_lock (struct vnode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ufs_ioctl(struct vop_ioctl_args *ap)
{
	struct vnode *vp;
	int error;

	vp = ap->a_vp;
	switch (ap->a_command) {
	case FIOSEEKDATA:
		error = vn_lock(vp, LK_SHARED);
		if (error == 0) {
			error = ufs_bmap_seekdata(vp, (off_t *)ap->a_data);
			VOP_UNLOCK(vp, 0);
		} else
			error = EBADF;
		return (error);
	case FIOSEEKHOLE:
		return (vn_bmap_seekhole(vp, ap->a_command, (off_t *)ap->a_data,
		    ap->a_cred));
	default:
		return (ENOTTY);
	}
}