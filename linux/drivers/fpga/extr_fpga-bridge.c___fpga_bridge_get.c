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
struct fpga_image_info {int dummy; } ;
struct fpga_bridge {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; struct fpga_image_info* info; } ;
struct device {TYPE_2__* parent; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 struct fpga_bridge* ERR_PTR (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct fpga_bridge* to_fpga_bridge (struct device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fpga_bridge *__fpga_bridge_get(struct device *dev,
					     struct fpga_image_info *info)
{
	struct fpga_bridge *bridge;
	int ret = -ENODEV;

	bridge = to_fpga_bridge(dev);

	bridge->info = info;

	if (!mutex_trylock(&bridge->mutex)) {
		ret = -EBUSY;
		goto err_dev;
	}

	if (!try_module_get(dev->parent->driver->owner))
		goto err_ll_mod;

	dev_dbg(&bridge->dev, "get\n");

	return bridge;

err_ll_mod:
	mutex_unlock(&bridge->mutex);
err_dev:
	put_device(dev);
	return ERR_PTR(ret);
}