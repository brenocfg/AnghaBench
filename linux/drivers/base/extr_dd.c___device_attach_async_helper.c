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
struct device_attach_data {int check_async; int want_async; struct device* dev; } ;
struct device {scalar_t__ parent; int /*<<< orphan*/  bus; scalar_t__ driver; TYPE_1__* p; } ;
typedef  int /*<<< orphan*/  async_cookie_t ;
struct TYPE_2__ {scalar_t__ dead; } ;

/* Variables and functions */
 int /*<<< orphan*/  __device_attach_driver ; 
 int /*<<< orphan*/  bus_for_each_drv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device_attach_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  pm_request_idle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_put (scalar_t__) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static void __device_attach_async_helper(void *_dev, async_cookie_t cookie)
{
	struct device *dev = _dev;
	struct device_attach_data data = {
		.dev		= dev,
		.check_async	= true,
		.want_async	= true,
	};

	device_lock(dev);

	/*
	 * Check if device has already been removed or claimed. This may
	 * happen with driver loading, device discovery/registration,
	 * and deferred probe processing happens all at once with
	 * multiple threads.
	 */
	if (dev->p->dead || dev->driver)
		goto out_unlock;

	if (dev->parent)
		pm_runtime_get_sync(dev->parent);

	bus_for_each_drv(dev->bus, NULL, &data, __device_attach_driver);
	dev_dbg(dev, "async probe completed\n");

	pm_request_idle(dev);

	if (dev->parent)
		pm_runtime_put(dev->parent);
out_unlock:
	device_unlock(dev);

	put_device(dev);
}