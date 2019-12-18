#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_mount; TYPE_2__* v_rdev; } ;
struct statfs {int dummy; } ;
struct TYPE_6__ {struct vnode* um_devvp; } ;
struct TYPE_5__ {TYPE_1__* si_mountpt; } ;
struct TYPE_4__ {struct statfs const mnt_stat; } ;

/* Variables and functions */
 scalar_t__ VCHR ; 
 TYPE_3__* VFSTOUFS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct statfs *
ffs_getmntstat(struct vnode *devvp)
{

	if (devvp->v_type == VCHR)
		return (&devvp->v_rdev->si_mountpt->mnt_stat);
	return (ffs_getmntstat(VFSTOUFS(devvp->v_mount)->um_devvp));
}