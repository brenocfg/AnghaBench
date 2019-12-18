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
struct ofw_bus_devinfo {int /*<<< orphan*/  obd_node; int /*<<< orphan*/  obd_status; int /*<<< orphan*/  obd_model; int /*<<< orphan*/  obd_type; int /*<<< orphan*/  obd_compat; int /*<<< orphan*/  obd_name; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 

int
ofw_bus_gen_setup_devinfo(struct ofw_bus_devinfo *obd, phandle_t node)
{

	if (obd == NULL)
		return (ENOMEM);
	/* The 'name' property is considered mandatory. */
	if ((OF_getprop_alloc(node, "name", (void **)&obd->obd_name)) == -1)
		return (EINVAL);
	OF_getprop_alloc(node, "compatible", (void **)&obd->obd_compat);
	OF_getprop_alloc(node, "device_type", (void **)&obd->obd_type);
	OF_getprop_alloc(node, "model", (void **)&obd->obd_model);
	OF_getprop_alloc(node, "status", (void **)&obd->obd_status);
	obd->obd_node = node;
	return (0);
}