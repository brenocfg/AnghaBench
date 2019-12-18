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
struct opal_dev {int supported; int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int opal_discovery0_step (struct opal_dev*) ; 
 int /*<<< orphan*/  setup_opal_dev (struct opal_dev*) ; 

__attribute__((used)) static int check_opal_support(struct opal_dev *dev)
{
	int ret;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = opal_discovery0_step(dev);
	dev->supported = !ret;
	mutex_unlock(&dev->dev_lock);

	return ret;
}