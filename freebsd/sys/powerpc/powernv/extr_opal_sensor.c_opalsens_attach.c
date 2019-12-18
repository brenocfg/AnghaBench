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
struct ofw_bus_devinfo {int /*<<< orphan*/  obd_name; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_child (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct ofw_bus_devinfo*) ; 
 int /*<<< orphan*/  free (struct ofw_bus_devinfo*,int /*<<< orphan*/ ) ; 
 struct ofw_bus_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (struct ofw_bus_devinfo*) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (struct ofw_bus_devinfo*,scalar_t__) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
opalsens_attach(device_t dev)
{
	phandle_t child;
	device_t cdev;
	struct ofw_bus_devinfo *dinfo;

	for (child = OF_child(ofw_bus_get_node(dev)); child != 0;
	    child = OF_peer(child)) {
		dinfo = malloc(sizeof(*dinfo), M_DEVBUF, M_WAITOK | M_ZERO);
		if (ofw_bus_gen_setup_devinfo(dinfo, child) != 0) {
			free(dinfo, M_DEVBUF);
			continue;
		}
		cdev = device_add_child(dev, NULL, -1);
		if (cdev == NULL) {
			device_printf(dev, "<%s>: device_add_child failed\n",
			    dinfo->obd_name);
			ofw_bus_gen_destroy_devinfo(dinfo);
			free(dinfo, M_DEVBUF);
			continue;
		}
		device_set_ivars(cdev, dinfo);
	}

	return (bus_generic_attach(dev));
}