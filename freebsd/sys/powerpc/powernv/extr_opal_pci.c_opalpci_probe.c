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
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
 int /*<<< orphan*/  OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_check () ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
opalpci_probe(device_t dev)
{
	const char	*type;

	if (opal_check() != 0)
		return (ENXIO);

	type = ofw_bus_get_type(dev);

	if (type == NULL || (strcmp(type, "pci") != 0 &&
	    strcmp(type, "pciex") != 0))
		return (ENXIO);

	if (!OF_hasprop(ofw_bus_get_node(dev), "ibm,opal-phbid"))
		return (ENXIO); 

	device_set_desc(dev, "OPAL Host-PCI bridge");
	return (BUS_PROBE_GENERIC);
}