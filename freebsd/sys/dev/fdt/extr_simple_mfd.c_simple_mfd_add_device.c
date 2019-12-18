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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int /*<<< orphan*/  obd_name; } ;
struct simplebus_devinfo {TYPE_1__ obdinfo; int /*<<< orphan*/  rl; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/ * device_add_child_ordered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct simplebus_devinfo*) ; 
 int /*<<< orphan*/  free (struct simplebus_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (TYPE_1__*) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 struct simplebus_devinfo* simple_mfd_setup_dinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct simplebus_devinfo*) ; 

device_t
simple_mfd_add_device(device_t dev, phandle_t node, u_int order,
    const char *name, int unit, struct simplebus_devinfo *di)
{
	struct simplebus_devinfo *ndi;
	device_t cdev;

	if ((ndi = simple_mfd_setup_dinfo(dev, node, di)) == NULL)
		return (NULL);
	cdev = device_add_child_ordered(dev, order, name, unit);
	if (cdev == NULL) {
		device_printf(dev, "<%s>: device_add_child failed\n",
		    ndi->obdinfo.obd_name);
		resource_list_free(&ndi->rl);
		ofw_bus_gen_destroy_devinfo(&ndi->obdinfo);
		if (di == NULL)
			free(ndi, M_DEVBUF);
		return (NULL);
	}
	device_set_ivars(cdev, ndi);

	return(cdev);
}