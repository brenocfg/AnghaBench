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
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  od; } ;
struct platform_device {TYPE_2__ dev; TYPE_1__ archdata; } ;
struct omap_device {int _driver_status; int /*<<< orphan*/  _state; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  BUS_NOTIFY_ADD_DEVICE 131 
#define  BUS_NOTIFY_BIND_DRIVER 130 
#define  BUS_NOTIFY_REMOVED_DEVICE 129 
#define  BUS_NOTIFY_UNBOUND_DRIVER 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  OMAP_DEVICE_STATE_ENABLED ; 
 int /*<<< orphan*/  dev_err (void*,char*) ; 
 int /*<<< orphan*/  dev_info (void*,char*) ; 
 int /*<<< orphan*/  omap_auxdata_legacy_init (void*) ; 
 int /*<<< orphan*/  omap_device_build_from_dt (struct platform_device*) ; 
 int /*<<< orphan*/  omap_device_delete (int /*<<< orphan*/ ) ; 
 int omap_device_idle (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (void*) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (void*) ; 
 struct omap_device* to_omap_device (struct platform_device*) ; 
 struct platform_device* to_platform_device (void*) ; 

__attribute__((used)) static int _omap_device_notifier_call(struct notifier_block *nb,
				      unsigned long event, void *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct omap_device *od;
	int err;

	switch (event) {
	case BUS_NOTIFY_REMOVED_DEVICE:
		if (pdev->archdata.od)
			omap_device_delete(pdev->archdata.od);
		break;
	case BUS_NOTIFY_UNBOUND_DRIVER:
		od = to_omap_device(pdev);
		if (od && (od->_state == OMAP_DEVICE_STATE_ENABLED)) {
			dev_info(dev, "enabled after unload, idling\n");
			err = omap_device_idle(pdev);
			if (err)
				dev_err(dev, "failed to idle\n");
		}
		break;
	case BUS_NOTIFY_BIND_DRIVER:
		od = to_omap_device(pdev);
		if (od && (od->_state == OMAP_DEVICE_STATE_ENABLED) &&
		    pm_runtime_status_suspended(dev)) {
			od->_driver_status = BUS_NOTIFY_BIND_DRIVER;
			pm_runtime_set_active(dev);
		}
		break;
	case BUS_NOTIFY_ADD_DEVICE:
		if (pdev->dev.of_node)
			omap_device_build_from_dt(pdev);
		omap_auxdata_legacy_init(dev);
		/* fall through */
	default:
		od = to_omap_device(pdev);
		if (od)
			od->_driver_status = event;
	}

	return NOTIFY_DONE;
}