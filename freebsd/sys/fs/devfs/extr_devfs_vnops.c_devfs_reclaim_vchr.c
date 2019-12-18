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
struct vop_reclaim_args {struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; scalar_t__ v_usecount; struct cdev* v_rdev; } ;
struct cdev {int /*<<< orphan*/  si_usecount; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ VCHR ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_rel (struct cdev*) ; 
 int /*<<< orphan*/  dev_unlock () ; 
 int /*<<< orphan*/  devfs_reclaim (struct vop_reclaim_args*) ; 

__attribute__((used)) static int
devfs_reclaim_vchr(struct vop_reclaim_args *ap)
{
	struct vnode *vp;
	struct cdev *dev;

	vp = ap->a_vp;
	MPASS(vp->v_type == VCHR);

	devfs_reclaim(ap);

	VI_LOCK(vp);
	dev_lock();
	dev = vp->v_rdev;
	vp->v_rdev = NULL;
	if (dev != NULL)
		dev->si_usecount -= vp->v_usecount;
	dev_unlock();
	VI_UNLOCK(vp);
	if (dev != NULL)
		dev_rel(dev);
	return (0);
}