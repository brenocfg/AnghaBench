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
struct vop_openextattr_args {int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_cred; TYPE_1__* a_vp; } ;
struct TYPE_2__ {scalar_t__ v_type; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 
 int ffs_open_ea (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ffs_openextattr(struct vop_openextattr_args *ap)
/*
struct vop_openextattr_args {
	struct vnodeop_desc *a_desc;
	struct vnode *a_vp;
	IN struct ucred *a_cred;
	IN struct thread *a_td;
};
*/
{

	if (ap->a_vp->v_type == VCHR || ap->a_vp->v_type == VBLK)
		return (EOPNOTSUPP);

	return (ffs_open_ea(ap->a_vp, ap->a_cred, ap->a_td));
}