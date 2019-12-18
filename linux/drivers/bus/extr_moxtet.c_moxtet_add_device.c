#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct moxtet_device {scalar_t__ idx; int id; TYPE_1__* moxtet; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TURRIS_MOX_MAX_MODULES ; 
 int bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct moxtet_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mox_module_name (int) ; 
 int /*<<< orphan*/  moxtet_bus_type ; 
 int /*<<< orphan*/  moxtet_dev_check ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int moxtet_add_device(struct moxtet_device *dev)
{
	static DEFINE_MUTEX(add_mutex);
	int ret;

	if (dev->idx >= TURRIS_MOX_MAX_MODULES || dev->id > 0xf)
		return -EINVAL;

	dev_set_name(&dev->dev, "moxtet-%s.%u", mox_module_name(dev->id),
		     dev->idx);

	mutex_lock(&add_mutex);

	ret = bus_for_each_dev(&moxtet_bus_type, NULL, dev,
			       moxtet_dev_check);
	if (ret)
		goto done;

	ret = device_add(&dev->dev);
	if (ret < 0)
		dev_err(dev->moxtet->dev, "can't add %s, status %d\n",
			dev_name(dev->moxtet->dev), ret);

done:
	mutex_unlock(&add_mutex);
	return ret;
}