#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
typedef  int /*<<< orphan*/  devclass_t ;
struct TYPE_5__ {scalar_t__ devclass; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_data_generation_update () ; 
 int devclass_add_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  devclass_delete_device (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  devclass_find_internal (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
device_set_devclass(device_t dev, const char *classname)
{
	devclass_t dc;
	int error;

	if (!classname) {
		if (dev->devclass)
			devclass_delete_device(dev->devclass, dev);
		return (0);
	}

	if (dev->devclass) {
		printf("device_set_devclass: device class already set\n");
		return (EINVAL);
	}

	dc = devclass_find_internal(classname, NULL, TRUE);
	if (!dc)
		return (ENOMEM);

	error = devclass_add_device(dc, dev);

	bus_data_generation_update();
	return (error);
}