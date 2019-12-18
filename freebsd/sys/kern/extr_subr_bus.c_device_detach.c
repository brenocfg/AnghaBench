#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
struct TYPE_15__ {scalar_t__ state; int flags; int /*<<< orphan*/  devclass; scalar_t__ parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_CHILD_DETACHED (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  DEVICENAME (TYPE_1__*) ; 
 int DEVICE_DETACH (TYPE_1__*) ; 
 int DF_FIXEDCLASS ; 
 scalar_t__ DS_ATTACHED ; 
 scalar_t__ DS_ATTACHING ; 
 scalar_t__ DS_BUSY ; 
 scalar_t__ DS_NOTPRESENT ; 
 int EBUSY ; 
 int /*<<< orphan*/  EVENTHANDLER_DIRECT_INVOKE (int (*) (TYPE_1__*),TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVHDEV_DETACH_BEGIN ; 
 int /*<<< orphan*/  EVHDEV_DETACH_COMPLETE ; 
 int /*<<< orphan*/  EVHDEV_DETACH_FAILED ; 
 int /*<<< orphan*/  GIANT_REQUIRED ; 
 int /*<<< orphan*/  PDEBUG (char*) ; 
 int /*<<< orphan*/  devclass_delete_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  device_is_quiet (TYPE_1__*) ; 
 int /*<<< orphan*/  device_printf (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  device_set_driver (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_sysctl_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  device_verbose (TYPE_1__*) ; 
 int /*<<< orphan*/  devremoved (TYPE_1__*) ; 

int
device_detach(device_t dev)
{
	int error;

	GIANT_REQUIRED;

	PDEBUG(("%s", DEVICENAME(dev)));
	if (dev->state == DS_BUSY)
		return (EBUSY);
	if (dev->state == DS_ATTACHING) {
		device_printf(dev, "device in attaching state! Deferring detach.\n");
		return (EBUSY);
	}
	if (dev->state != DS_ATTACHED)
		return (0);

	EVENTHANDLER_DIRECT_INVOKE(device_detach, dev, EVHDEV_DETACH_BEGIN);
	if ((error = DEVICE_DETACH(dev)) != 0) {
		EVENTHANDLER_DIRECT_INVOKE(device_detach, dev,
		    EVHDEV_DETACH_FAILED);
		return (error);
	} else {
		EVENTHANDLER_DIRECT_INVOKE(device_detach, dev,
		    EVHDEV_DETACH_COMPLETE);
	}
	devremoved(dev);
	if (!device_is_quiet(dev))
		device_printf(dev, "detached\n");
	if (dev->parent)
		BUS_CHILD_DETACHED(dev->parent, dev);

	if (!(dev->flags & DF_FIXEDCLASS))
		devclass_delete_device(dev->devclass, dev);

	device_verbose(dev);
	dev->state = DS_NOTPRESENT;
	(void)device_set_driver(dev, NULL);
	device_sysctl_fini(dev);

	return (0);
}