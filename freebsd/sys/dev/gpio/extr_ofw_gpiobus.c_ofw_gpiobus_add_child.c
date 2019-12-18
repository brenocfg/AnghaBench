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
struct TYPE_2__ {int obd_node; int /*<<< orphan*/ * obd_model; int /*<<< orphan*/ * obd_type; int /*<<< orphan*/ * obd_compat; int /*<<< orphan*/ * obd_name; } ;
struct ofw_gpiobus_devinfo {TYPE_1__ opd_obdinfo; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * device_add_child_ordered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct ofw_gpiobus_devinfo*) ; 
 struct ofw_gpiobus_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static device_t
ofw_gpiobus_add_child(device_t dev, u_int order, const char *name, int unit)
{
	device_t child;
	struct ofw_gpiobus_devinfo *devi;

	child = device_add_child_ordered(dev, order, name, unit);
	if (child == NULL)
		return (child);
	devi = malloc(sizeof(struct ofw_gpiobus_devinfo), M_DEVBUF,
	    M_NOWAIT | M_ZERO);
	if (devi == NULL) {
		device_delete_child(dev, child);
		return (0);
	}

	/*
	 * NULL all the OFW-related parts of the ivars for non-OFW
	 * children.
	 */
	devi->opd_obdinfo.obd_node = -1;
	devi->opd_obdinfo.obd_name = NULL;
	devi->opd_obdinfo.obd_compat = NULL;
	devi->opd_obdinfo.obd_type = NULL;
	devi->opd_obdinfo.obd_model = NULL;

	device_set_ivars(child, devi);

	return (child);
}