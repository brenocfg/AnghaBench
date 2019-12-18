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
struct device_driver {int name; } ;
struct device {TYPE_1__* p; int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {struct device_driver* async_driver; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  __driver_attach_async_helper ; 
 int /*<<< orphan*/  async_schedule_dev (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  device_driver_attach (struct device_driver*,struct device*) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 scalar_t__ driver_allows_async_probing (struct device_driver*) ; 
 int /*<<< orphan*/  driver_deferred_probe_add (struct device*) ; 
 int driver_match_device (struct device_driver*,struct device*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 

__attribute__((used)) static int __driver_attach(struct device *dev, void *data)
{
	struct device_driver *drv = data;
	int ret;

	/*
	 * Lock device and try to bind to it. We drop the error
	 * here and always return 0, because we need to keep trying
	 * to bind to devices and some drivers will return an error
	 * simply if it didn't support the device.
	 *
	 * driver_probe_device() will spit a warning if there
	 * is an error.
	 */

	ret = driver_match_device(drv, dev);
	if (ret == 0) {
		/* no match */
		return 0;
	} else if (ret == -EPROBE_DEFER) {
		dev_dbg(dev, "Device match requests probe deferral\n");
		driver_deferred_probe_add(dev);
	} else if (ret < 0) {
		dev_dbg(dev, "Bus failed to match device: %d", ret);
		return ret;
	} /* ret > 0 means positive match */

	if (driver_allows_async_probing(drv)) {
		/*
		 * Instead of probing the device synchronously we will
		 * probe it asynchronously to allow for more parallelism.
		 *
		 * We only take the device lock here in order to guarantee
		 * that the dev->driver and async_driver fields are protected
		 */
		dev_dbg(dev, "probing driver %s asynchronously\n", drv->name);
		device_lock(dev);
		if (!dev->driver) {
			get_device(dev);
			dev->p->async_driver = drv;
			async_schedule_dev(__driver_attach_async_helper, dev);
		}
		device_unlock(dev);
		return 0;
	}

	device_driver_attach(drv, dev);

	return 0;
}