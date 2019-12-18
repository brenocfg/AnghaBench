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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  AML_SOC_HW_REV_M8 129 
#define  AML_SOC_HW_REV_M8B 128 
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int aml8726_soc_hw_rev ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_usb_phy_probe(device_t dev)
{

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (!ofw_bus_is_compatible(dev, "amlogic,aml8726-m6-usb-phy") &&
	    !ofw_bus_is_compatible(dev, "amlogic,aml8726-m8-usb-phy"))
		return (ENXIO);

	switch (aml8726_soc_hw_rev) {
	case AML_SOC_HW_REV_M8:
	case AML_SOC_HW_REV_M8B:
		device_set_desc(dev, "Amlogic aml8726-m8 USB PHY");
		break;
	default:
		device_set_desc(dev, "Amlogic aml8726-m6 USB PHY");
		break;
	}

	return (BUS_PROBE_DEFAULT);
}