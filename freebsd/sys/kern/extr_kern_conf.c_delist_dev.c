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

/* Variables and functions */
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  delist_dev_locked (struct cdev*) ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_unlock () ; 

void
delist_dev(struct cdev *dev)
{

	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL, "delist_dev");
	dev_lock();
	delist_dev_locked(dev);
	dev_unlock();
}