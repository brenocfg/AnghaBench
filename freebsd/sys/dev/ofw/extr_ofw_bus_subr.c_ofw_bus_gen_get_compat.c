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
struct ofw_bus_devinfo {char const* obd_compat; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ofw_bus_devinfo* OFW_BUS_GET_DEVINFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
ofw_bus_gen_get_compat(device_t bus, device_t dev)
{
	const struct ofw_bus_devinfo *obd;

	obd = OFW_BUS_GET_DEVINFO(bus, dev);
	if (obd == NULL)
		return (NULL);
	return (obd->obd_compat);
}