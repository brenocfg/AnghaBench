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
struct resource {int dummy; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int ocd_data; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
#define  IMXSOC_51 129 
#define  IMXSOC_53 128 
 int /*<<< orphan*/  RF_UNMAPPED ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_free_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  compat_data ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__* imx51_epit_ioaddr ; 
 scalar_t__* imx53_epit_ioaddr ; 
 scalar_t__* imx6_epit_ioaddr ; 
 int imx_soc_family () ; 
 int imx_soc_type () ; 
 int /*<<< orphan*/  ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
epit_probe(device_t dev)
{
	struct resource *memres;
	rman_res_t ioaddr;
	int num_units, rid, unit;

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	/*
	 * The FDT data for imx5 and imx6 EPIT hardware is missing or broken,
	 * but it may get fixed some day, so first just do a normal check.  We
	 * return success if the compatible string matches and we haven't
	 * already instantiated the number of units needed on this platform.
	 */
	unit = device_get_unit(dev);
	num_units = ofw_bus_search_compatible(dev, compat_data)->ocd_data;
	if (unit < num_units) {
		device_set_desc(dev, "i.MX EPIT timer");
		return (BUS_PROBE_DEFAULT);
	}

	/*
	 * No compat string match, but for imx6 all the data we need is in the
	 * node except the compat string, so do our own compatibility check
	 * using the device name of the node and the register block address.
	 */
	if (strstr(ofw_bus_get_name(dev), "epit") == NULL)
		return (ENXIO);

	rid = 0;
	memres = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_UNMAPPED);
	if (memres == NULL)
		return (ENXIO);
	ioaddr = rman_get_start(memres);
	bus_free_resource(dev, SYS_RES_MEMORY, memres);

	if (imx_soc_family() == 6) {
		if (unit > 0)
			return (ENXIO);
		if (ioaddr != imx6_epit_ioaddr[unit])
			return (ENXIO);
	} else {
		if (unit > 1)
			return (ENXIO);
		switch (imx_soc_type()) {
		case IMXSOC_51:
			if (ioaddr != imx51_epit_ioaddr[unit])
				return (ENXIO);
			break;
		case IMXSOC_53:
			if (ioaddr != imx53_epit_ioaddr[unit])
				return (ENXIO);
			break;
		default:
			return (ENXIO);
		}
		/*
		 * XXX Right now we have no way to handle the fact that the
		 * entire EPIT node is missing, which means no interrupt data.
		 */
		return (ENXIO);
	}

	device_set_desc(dev, "i.MX EPIT timer");
	return (BUS_PROBE_DEFAULT);
}