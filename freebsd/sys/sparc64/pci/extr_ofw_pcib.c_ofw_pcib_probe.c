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
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ ISDTYPE (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OFW_TYPE_PCIE ; 
 scalar_t__ PCIC_BRIDGE ; 
 scalar_t__ PCIS_BRIDGE_PCI ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int
ofw_pcib_probe(device_t dev)
{
	char desc[sizeof("OFW PCIe-PCIe bridge")];
	const char *dtype, *pbdtype;

#define	ISDTYPE(dtype, type)						\
	(((dtype) != NULL) && strcmp((dtype), (type)) == 0)

	if ((pci_get_class(dev) == PCIC_BRIDGE) &&
	    (pci_get_subclass(dev) == PCIS_BRIDGE_PCI) &&
	    ofw_bus_get_node(dev) != 0) {
		dtype = ofw_bus_get_type(dev);
		pbdtype = ofw_bus_get_type(device_get_parent(
		    device_get_parent(dev)));
		snprintf(desc, sizeof(desc), "OFW PCI%s-PCI%s bridge",
		    ISDTYPE(pbdtype, OFW_TYPE_PCIE) ? "e" : "",
		    ISDTYPE(dtype, OFW_TYPE_PCIE) ? "e" : "");
		device_set_desc_copy(dev, desc);
		return (BUS_PROBE_DEFAULT);
	}

#undef ISDTYPE

	return (ENXIO);
}