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
struct vnode {int v_vflag; struct cdev* v_rdev; } ;
struct cdevsw {int dummy; } ;
struct cdev_priv {int cdp_flags; } ;
struct cdev {int si_flags; int /*<<< orphan*/  si_threadcount; struct cdevsw* si_devsw; } ;

/* Variables and functions */
 int CDP_SCHED_DTR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int SI_ETERNAL ; 
 int VV_ETERNALDEV ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 struct cdev_priv* cdev2priv (struct cdev*) ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_unlock () ; 
 int /*<<< orphan*/  devmtx ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct cdevsw *
devvn_refthread(struct vnode *vp, struct cdev **devp, int *ref)
{
	struct cdevsw *csw;
	struct cdev_priv *cdp;
	struct cdev *dev;

	mtx_assert(&devmtx, MA_NOTOWNED);
	if ((vp->v_vflag & VV_ETERNALDEV) != 0) {
		dev = vp->v_rdev;
		if (dev == NULL)
			return (NULL);
		KASSERT((dev->si_flags & SI_ETERNAL) != 0,
		    ("Not eternal cdev"));
		*ref = 0;
		csw = dev->si_devsw;
		KASSERT(csw != NULL, ("Eternal cdev is destroyed"));
		*devp = dev;
		return (csw);
	}

	csw = NULL;
	dev_lock();
	dev = vp->v_rdev;
	if (dev == NULL) {
		dev_unlock();
		return (NULL);
	}
	cdp = cdev2priv(dev);
	if ((cdp->cdp_flags & CDP_SCHED_DTR) == 0) {
		csw = dev->si_devsw;
		if (csw != NULL)
			atomic_add_long(&dev->si_threadcount, 1);
	}
	dev_unlock();
	if (csw != NULL) {
		*devp = dev;
		*ref = 1;
	}
	return (csw);
}