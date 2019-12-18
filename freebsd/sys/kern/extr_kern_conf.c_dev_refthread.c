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
struct cdevsw {int dummy; } ;
struct cdev_priv {int cdp_flags; } ;
struct cdev {int si_flags; int /*<<< orphan*/  si_threadcount; struct cdevsw* si_devsw; } ;

/* Variables and functions */
 int CDP_SCHED_DTR ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int SI_ETERNAL ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 struct cdev_priv* cdev2priv (struct cdev*) ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_unlock () ; 
 int /*<<< orphan*/  devmtx ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct cdevsw *
dev_refthread(struct cdev *dev, int *ref)
{
	struct cdevsw *csw;
	struct cdev_priv *cdp;

	mtx_assert(&devmtx, MA_NOTOWNED);
	if ((dev->si_flags & SI_ETERNAL) != 0) {
		*ref = 0;
		return (dev->si_devsw);
	}
	dev_lock();
	csw = dev->si_devsw;
	if (csw != NULL) {
		cdp = cdev2priv(dev);
		if ((cdp->cdp_flags & CDP_SCHED_DTR) == 0)
			atomic_add_long(&dev->si_threadcount, 1);
		else
			csw = NULL;
	}
	dev_unlock();
	if (csw != NULL)
		*ref = 1;
	return (csw);
}