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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
#define  MV_DEV_88F6282 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_id (int*,int*) ; 

__attribute__((used)) static int
ts_probe(device_t dev)
{
	uint32_t d, r;

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (!ofw_bus_is_compatible(dev, "mrvl,ts"))
		return (ENXIO);
	soc_id(&d, &r);
	switch (d) {
	case MV_DEV_88F6282:
		break;
	default:
		device_printf(dev, "unsupported SoC (ID: 0x%08X)!\n", d);
		return (ENXIO);
	}
	device_set_desc(dev, "Marvell Thermal Sensor");

	return (0);
}