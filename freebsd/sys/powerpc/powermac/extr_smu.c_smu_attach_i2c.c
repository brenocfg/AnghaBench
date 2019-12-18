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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_SMU ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_getprop (scalar_t__,char*,char*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct ofw_bus_devinfo*) ; 
 int /*<<< orphan*/  free (struct ofw_bus_devinfo*,int /*<<< orphan*/ ) ; 
 struct ofw_bus_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (struct ofw_bus_devinfo*) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (struct ofw_bus_devinfo*,scalar_t__) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
smu_attach_i2c(device_t smu, phandle_t i2croot)
{
	phandle_t child;
	device_t cdev;
	struct ofw_bus_devinfo *dinfo;
	char name[32];

	for (child = OF_child(i2croot); child != 0; child = OF_peer(child)) {
		if (OF_getprop(child, "name", name, sizeof(name)) <= 0)
			continue;

		if (strcmp(name, "i2c-bus") != 0 && strcmp(name, "i2c") != 0)
			continue;

		dinfo = malloc(sizeof(struct ofw_bus_devinfo), M_SMU,
		    M_WAITOK | M_ZERO);
		if (ofw_bus_gen_setup_devinfo(dinfo, child) != 0) {
			free(dinfo, M_SMU);
			continue;
		}

		cdev = device_add_child(smu, NULL, -1);
		if (cdev == NULL) {
			device_printf(smu, "<%s>: device_add_child failed\n",
			    dinfo->obd_name);
			ofw_bus_gen_destroy_devinfo(dinfo);
			free(dinfo, M_SMU);
			continue;
		}
		device_set_ivars(cdev, dinfo);
	}
}