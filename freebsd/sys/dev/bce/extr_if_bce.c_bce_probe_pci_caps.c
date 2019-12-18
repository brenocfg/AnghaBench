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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct bce_softc {int link_speed; int link_width; int /*<<< orphan*/  bce_cap_flags; int /*<<< orphan*/  bce_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_INFO_LOAD ; 
 int /*<<< orphan*/  BCE_MSIX_CAPABLE_FLAG ; 
 int /*<<< orphan*/  BCE_MSI_CAPABLE_FLAG ; 
 int /*<<< orphan*/  BCE_PCIE_CAPABLE_FLAG ; 
 int /*<<< orphan*/  BCE_PCIE_FLAG ; 
 int /*<<< orphan*/  BCE_PCIX_CAPABLE_FLAG ; 
 int /*<<< orphan*/  BCE_VERBOSE_LOAD ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBPRINT (struct bce_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int /*<<< orphan*/  PCIY_MSI ; 
 int /*<<< orphan*/  PCIY_MSIX ; 
 int /*<<< orphan*/  PCIY_PCIX ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
bce_probe_pci_caps(device_t dev, struct bce_softc *sc)
{
	u32 reg;

	DBENTER(BCE_VERBOSE_LOAD);

	/* Check if PCI-X capability is enabled. */
	if (pci_find_cap(dev, PCIY_PCIX, &reg) == 0) {
		if (reg != 0)
			sc->bce_cap_flags |= BCE_PCIX_CAPABLE_FLAG;
	}

	/* Check if PCIe capability is enabled. */
	if (pci_find_cap(dev, PCIY_EXPRESS, &reg) == 0) {
		if (reg != 0) {
			u16 link_status = pci_read_config(dev, reg + 0x12, 2);
			DBPRINT(sc, BCE_INFO_LOAD, "PCIe link_status = "
			    "0x%08X\n",	link_status);
			sc->link_speed = link_status & 0xf;
			sc->link_width = (link_status >> 4) & 0x3f;
			sc->bce_cap_flags |= BCE_PCIE_CAPABLE_FLAG;
			sc->bce_flags |= BCE_PCIE_FLAG;
		}
	}

	/* Check if MSI capability is enabled. */
	if (pci_find_cap(dev, PCIY_MSI, &reg) == 0) {
		if (reg != 0)
			sc->bce_cap_flags |= BCE_MSI_CAPABLE_FLAG;
	}

	/* Check if MSI-X capability is enabled. */
	if (pci_find_cap(dev, PCIY_MSIX, &reg) == 0) {
		if (reg != 0)
			sc->bce_cap_flags |= BCE_MSIX_CAPABLE_FLAG;
	}

	DBEXIT(BCE_VERBOSE_LOAD);
}