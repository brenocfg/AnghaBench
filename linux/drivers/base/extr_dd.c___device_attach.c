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
struct device_attach_data {int check_async; int want_async; scalar_t__ have_async; struct device* dev; } ;
struct device {scalar_t__ parent; int /*<<< orphan*/  bus; int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  __device_attach_async_helper ; 
 int /*<<< orphan*/  __device_attach_driver ; 
 int /*<<< orphan*/  async_schedule_dev (int /*<<< orphan*/ ,struct device*) ; 
 int bus_for_each_drv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device_attach_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int device_bind_driver (struct device*) ; 
 scalar_t__ device_is_bound (struct device*) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  pm_request_idle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_put (scalar_t__) ; 

__attribute__((used)) static int __device_attach(struct device *dev, bool allow_async)
{
	int ret = 0;

	device_lock(dev);
	if (dev->driver) {
		if (device_is_bound(dev)) {
			ret = 1;
			goto out_unlock;
		}
		ret = device_bind_driver(dev);
		if (ret == 0)
			ret = 1;
		else {
			dev->driver = NULL;
			ret = 0;
		}
	} else {
		struct device_attach_data data = {
			.dev = dev,
			.check_async = allow_async,
			.want_async = false,
		};

		if (dev->parent)
			pm_runtime_get_sync(dev->parent);

		ret = bus_for_each_drv(dev->bus, NULL, &data,
					__device_attach_driver);
		if (!ret && allow_async && data.have_async) {
			/*
			 * If we could not find appropriate driver
			 * synchronously and we are allowed to do
			 * async probes and there are drivers that
			 * want to probe asynchronously, we'll
			 * try them.
			 */
			dev_dbg(dev, "scheduling asynchronous probe\n");
			get_device(dev);
			async_schedule_dev(__device_attach_async_helper, dev);
		} else {
			pm_request_idle(dev);
		}

		if (dev->parent)
			pm_runtime_put(dev->parent);
	}
out_unlock:
	device_unlock(dev);
	return ret;
}