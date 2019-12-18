#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vop_closeextattr_args {int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_cred; scalar_t__ a_commit; TYPE_2__* a_vp; } ;
struct TYPE_4__ {scalar_t__ v_type; TYPE_1__* v_mount; } ;
struct TYPE_3__ {int mnt_flag; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EROFS ; 
 int MNT_RDONLY ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 
 int ffs_close_ea (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ffs_closeextattr(struct vop_closeextattr_args *ap)
/*
struct vop_closeextattr_args {
	struct vnodeop_desc *a_desc;
	struct vnode *a_vp;
	int a_commit;
	IN struct ucred *a_cred;
	IN struct thread *a_td;
};
*/
{

	if (ap->a_vp->v_type == VCHR || ap->a_vp->v_type == VBLK)
		return (EOPNOTSUPP);

	if (ap->a_commit && (ap->a_vp->v_mount->mnt_flag & MNT_RDONLY))
		return (EROFS);

	return (ffs_close_ea(ap->a_vp, ap->a_commit, ap->a_cred, ap->a_td));
}