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
struct cdev_priv {int cdp_flags; void (* cdp_dtr_cb ) (void*) ;void* cdp_dtr_cb_arg; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int CDP_SCHED_DTR ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cdev_priv*,int /*<<< orphan*/ ) ; 
 struct cdev_priv* cdev2priv (struct cdev*) ; 
 int /*<<< orphan*/  cdp_dtr_list ; 
 int /*<<< orphan*/  dev_ddtr ; 
 int /*<<< orphan*/  dev_dtr_task ; 
 int /*<<< orphan*/  dev_refl (struct cdev*) ; 
 int /*<<< orphan*/  dev_unlock () ; 
 int /*<<< orphan*/  devmtx ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi_giant ; 

__attribute__((used)) static int
destroy_dev_sched_cbl(struct cdev *dev, void (*cb)(void *), void *arg)
{
	struct cdev_priv *cp;

	mtx_assert(&devmtx, MA_OWNED);
	cp = cdev2priv(dev);
	if (cp->cdp_flags & CDP_SCHED_DTR) {
		dev_unlock();
		return (0);
	}
	dev_refl(dev);
	cp->cdp_flags |= CDP_SCHED_DTR;
	cp->cdp_dtr_cb = cb;
	cp->cdp_dtr_cb_arg = arg;
	TAILQ_INSERT_TAIL(&dev_ddtr, cp, cdp_dtr_list);
	dev_unlock();
	taskqueue_enqueue(taskqueue_swi_giant, &dev_dtr_task);
	return (1);
}