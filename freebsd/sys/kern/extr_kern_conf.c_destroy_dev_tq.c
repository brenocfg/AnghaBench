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
struct cdev {int dummy; } ;
struct cdev_priv {int cdp_flags; void (* cdp_dtr_cb ) (void*) ;void* cdp_dtr_cb_arg; struct cdev cdp_c; } ;

/* Variables and functions */
 int CDP_SCHED_DTR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct cdev_priv* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cdev_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdp_dtr_list ; 
 int /*<<< orphan*/  destroy_devl (struct cdev*) ; 
 int /*<<< orphan*/  dev_ddtr ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_rel (struct cdev*) ; 
 int /*<<< orphan*/  dev_unlock () ; 
 int /*<<< orphan*/  dev_unlock_and_free () ; 

__attribute__((used)) static void
destroy_dev_tq(void *ctx, int pending)
{
	struct cdev_priv *cp;
	struct cdev *dev;
	void (*cb)(void *);
	void *cb_arg;

	dev_lock();
	while (!TAILQ_EMPTY(&dev_ddtr)) {
		cp = TAILQ_FIRST(&dev_ddtr);
		dev = &cp->cdp_c;
		KASSERT(cp->cdp_flags & CDP_SCHED_DTR,
		    ("cdev %p in dev_destroy_tq without CDP_SCHED_DTR", cp));
		TAILQ_REMOVE(&dev_ddtr, cp, cdp_dtr_list);
		cb = cp->cdp_dtr_cb;
		cb_arg = cp->cdp_dtr_cb_arg;
		destroy_devl(dev);
		dev_unlock_and_free();
		dev_rel(dev);
		if (cb != NULL)
			cb(cb_arg);
		dev_lock();
	}
	dev_unlock();
}