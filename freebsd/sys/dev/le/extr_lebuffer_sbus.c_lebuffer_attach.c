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
struct TYPE_2__ {int /*<<< orphan*/  obd_name; } ;
struct lebuffer_devinfo {TYPE_1__ ldi_obdinfo; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 scalar_t__ OF_child (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct lebuffer_devinfo*) ; 
 int /*<<< orphan*/  lebuffer_destroy_dinfo (struct lebuffer_devinfo*) ; 
 struct lebuffer_devinfo* lebuffer_setup_dinfo (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lebuffer_attach(device_t dev)
{
	struct lebuffer_devinfo *ldi;
	device_t cdev;
	phandle_t child;
	int children;

	children = 0;
	for (child = OF_child(ofw_bus_get_node(dev)); child != 0;
	    child = OF_peer(child)) {
		if ((ldi = lebuffer_setup_dinfo(dev, child)) == NULL)
			continue;
		if (children != 0) {
			device_printf(dev,
			    "<%s>: only one child per buffer supported\n",
			    ldi->ldi_obdinfo.obd_name);
			lebuffer_destroy_dinfo(ldi);
			continue;
		}
		if ((cdev = device_add_child(dev, NULL, -1)) == NULL) {
			device_printf(dev, "<%s>: device_add_child failed\n",
			    ldi->ldi_obdinfo.obd_name);
			lebuffer_destroy_dinfo(ldi);
			continue;
		}
		device_set_ivars(cdev, ldi);
		children++;
	}
	return (bus_generic_attach(dev));
}