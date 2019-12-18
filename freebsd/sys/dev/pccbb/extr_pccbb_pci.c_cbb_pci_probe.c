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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int BUS_PROBE_GENERIC ; 
 scalar_t__ CB_UNKNOWN ; 
 int ENXIO ; 
 scalar_t__ PCIC_BRIDGE ; 
 scalar_t__ PCIS_BRIDGE_CARDBUS ; 
 scalar_t__ cbb_chipset (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_progif (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cbb_pci_probe(device_t brdev)
{
	const char *name;
	uint32_t progif;
	uint32_t baseclass;
	uint32_t subclass;

	/*
	 * Do we know that we support the chipset?  If so, then we
	 * accept the device.
	 */
	if (cbb_chipset(pci_get_devid(brdev), &name) != CB_UNKNOWN) {
		device_set_desc(brdev, name);
		return (BUS_PROBE_DEFAULT);
	}

	/*
	 * We do support generic CardBus bridges.  All that we've seen
	 * to date have progif 0 (the Yenta spec, and successors mandate
	 * this).
	 */
	baseclass = pci_get_class(brdev);
	subclass = pci_get_subclass(brdev);
	progif = pci_get_progif(brdev);
	if (baseclass == PCIC_BRIDGE &&
	    subclass == PCIS_BRIDGE_CARDBUS && progif == 0) {
		device_set_desc(brdev, "PCI-CardBus Bridge");
		return (BUS_PROBE_GENERIC);
	}
	return (ENXIO);
}