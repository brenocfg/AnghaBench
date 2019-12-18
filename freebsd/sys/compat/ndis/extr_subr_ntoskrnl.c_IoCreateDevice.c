#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unicode_string ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_9__ {TYPE_3__* dro_devobj; } ;
typedef  TYPE_2__ driver_object ;
typedef  int /*<<< orphan*/  devobj_extension ;
struct TYPE_10__ {int do_type; int do_refcnt; int do_devtype; int do_stacksize; int do_alignreq; int do_characteristics; struct TYPE_10__* do_nextdev; TYPE_1__* do_devobj_ext; struct TYPE_10__* do_devext; int /*<<< orphan*/ * do_vpb; int /*<<< orphan*/  do_devlock; int /*<<< orphan*/ * do_iotimer; int /*<<< orphan*/ * do_attacheddev; int /*<<< orphan*/  do_size; scalar_t__ do_flags; int /*<<< orphan*/ * do_currirp; TYPE_2__* do_drvobj; } ;
typedef  TYPE_3__ device_object ;
struct TYPE_8__ {int dve_size; TYPE_3__* dve_devobj; scalar_t__ dve_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TYPE_SYNC ; 
 void* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_3__*) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int STATUS_INSUFFICIENT_RESOURCES ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 

uint32_t
IoCreateDevice(driver_object *drv, uint32_t devextlen, unicode_string *devname,
	uint32_t devtype, uint32_t devchars, uint8_t exclusive,
	device_object **newdev)
{
	device_object		*dev;

	dev = ExAllocatePoolWithTag(NonPagedPool, sizeof(device_object), 0);
	if (dev == NULL)
		return (STATUS_INSUFFICIENT_RESOURCES);

	dev->do_type = devtype;
	dev->do_drvobj = drv;
	dev->do_currirp = NULL;
	dev->do_flags = 0;

	if (devextlen) {
		dev->do_devext = ExAllocatePoolWithTag(NonPagedPool,
		    devextlen, 0);

		if (dev->do_devext == NULL) {
			ExFreePool(dev);
			return (STATUS_INSUFFICIENT_RESOURCES);
		}

		bzero(dev->do_devext, devextlen);
	} else
		dev->do_devext = NULL;

	dev->do_size = sizeof(device_object) + devextlen;
	dev->do_refcnt = 1;
	dev->do_attacheddev = NULL;
	dev->do_nextdev = NULL;
	dev->do_devtype = devtype;
	dev->do_stacksize = 1;
	dev->do_alignreq = 1;
	dev->do_characteristics = devchars;
	dev->do_iotimer = NULL;
	KeInitializeEvent(&dev->do_devlock, EVENT_TYPE_SYNC, TRUE);

	/*
	 * Vpd is used for disk/tape devices,
	 * but we don't support those. (Yet.)
	 */
	dev->do_vpb = NULL;

	dev->do_devobj_ext = ExAllocatePoolWithTag(NonPagedPool,
	    sizeof(devobj_extension), 0);

	if (dev->do_devobj_ext == NULL) {
		if (dev->do_devext != NULL)
			ExFreePool(dev->do_devext);
		ExFreePool(dev);
		return (STATUS_INSUFFICIENT_RESOURCES);
	}

	dev->do_devobj_ext->dve_type = 0;
	dev->do_devobj_ext->dve_size = sizeof(devobj_extension);
	dev->do_devobj_ext->dve_devobj = dev;

	/*
	 * Attach this device to the driver object's list
	 * of devices. Note: this is not the same as attaching
	 * the device to the device stack. The driver's AddDevice
	 * routine must explicitly call IoAddDeviceToDeviceStack()
	 * to do that.
	 */

	if (drv->dro_devobj == NULL) {
		drv->dro_devobj = dev;
		dev->do_nextdev = NULL;
	} else {
		dev->do_nextdev = drv->dro_devobj;
		drv->dro_devobj = dev;
	}

	*newdev = dev;

	return (STATUS_SUCCESS);
}