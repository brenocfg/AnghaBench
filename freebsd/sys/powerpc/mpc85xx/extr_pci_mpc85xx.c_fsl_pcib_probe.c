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
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
fsl_pcib_probe(device_t dev)
{

	if (ofw_bus_get_type(dev) == NULL ||
	    strcmp(ofw_bus_get_type(dev), "pci") != 0)
		return (ENXIO);

	if (!(ofw_bus_is_compatible(dev, "fsl,mpc8540-pci") ||
	    ofw_bus_is_compatible(dev, "fsl,mpc8540-pcie") ||
	    ofw_bus_is_compatible(dev, "fsl,mpc8548-pcie") ||
	    ofw_bus_is_compatible(dev, "fsl,p5020-pcie") ||
	    ofw_bus_is_compatible(dev, "fsl,qoriq-pcie-v2.2") ||
	    ofw_bus_is_compatible(dev, "fsl,qoriq-pcie")))
		return (ENXIO);

	device_set_desc(dev, "Freescale Integrated PCI/PCI-E Controller");
	return (BUS_PROBE_DEFAULT);
}