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
struct vnode {scalar_t__ v_type; TYPE_2__* v_rdev; } ;
struct TYPE_4__ {TYPE_1__* si_devsw; } ;
struct TYPE_3__ {int d_flags; } ;

/* Variables and functions */
 int D_DISK ; 
 int ENOTBLK ; 
 int ENXIO ; 
 scalar_t__ VCHR ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_unlock () ; 

int
vn_isdisk(struct vnode *vp, int *errp)
{
	int error;

	if (vp->v_type != VCHR) {
		error = ENOTBLK;
		goto out;
	}
	error = 0;
	dev_lock();
	if (vp->v_rdev == NULL)
		error = ENXIO;
	else if (vp->v_rdev->si_devsw == NULL)
		error = ENXIO;
	else if (!(vp->v_rdev->si_devsw->d_flags & D_DISK))
		error = ENOTBLK;
	dev_unlock();
out:
	if (errp != NULL)
		*errp = error;
	return (error == 0);
}