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
struct ofw_compat_data {scalar_t__ ocd_data; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
#define  CM1_INSTANCE 130 
#define  CM2_INSTANCE 129 
 int ENXIO ; 
#define  PRM_INSTANCE 128 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 struct ofw_compat_data* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
omap4_prcm_probe(device_t dev)
{
	const struct ofw_compat_data *ocd;

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	ocd = ofw_bus_search_compatible(dev, compat_data);
	if ((int)ocd->ocd_data == 0)
		return (ENXIO);

	switch ((int)ocd->ocd_data) {
		case PRM_INSTANCE:
			device_set_desc(dev, "TI OMAP Power, Reset and Clock Management (PRM)");
			break;
		case CM1_INSTANCE:
			device_set_desc(dev, "TI OMAP Power, Reset and Clock Management (C1)");
			break;
		case CM2_INSTANCE:
			device_set_desc(dev, "TI OMAP Power, Reset and Clock Management (C2)");
			break;
		default:
			device_printf(dev, "unknown instance type: %d\n", (int)ocd->ocd_data);
			return (ENXIO);
	}

	return (BUS_PROBE_DEFAULT);
}