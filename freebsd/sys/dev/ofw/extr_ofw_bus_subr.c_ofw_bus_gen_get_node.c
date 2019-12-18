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
struct ofw_bus_devinfo {int /*<<< orphan*/  obd_node; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ofw_bus_devinfo* OFW_BUS_GET_DEVINFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

phandle_t
ofw_bus_gen_get_node(device_t bus, device_t dev)
{
	const struct ofw_bus_devinfo *obd;

	obd = OFW_BUS_GET_DEVINFO(bus, dev);
	if (obd == NULL)
		return (0);
	return (obd->obd_node);
}