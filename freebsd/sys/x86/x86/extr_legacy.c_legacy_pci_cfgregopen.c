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
typedef  int uint64_t ;
typedef  int u_int16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CFGMECH_NONE ; 
 scalar_t__ CFGMECH_PCIE ; 
 int PCIR_DEVICE ; 
 int PCIR_VENDOR ; 
 scalar_t__ bootverbose ; 
 scalar_t__ cfgmech ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int pci_cfgregread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pcie_cfgregopen (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
legacy_pci_cfgregopen(device_t dev)
{
	uint64_t pciebar;
	u_int16_t did, vid;

	if (cfgmech == CFGMECH_NONE || cfgmech == CFGMECH_PCIE)
		return;

	/* Check for supported chipsets */
	vid = pci_cfgregread(0, 0, 0, PCIR_VENDOR, 2);
	did = pci_cfgregread(0, 0, 0, PCIR_DEVICE, 2);
	switch (vid) {
	case 0x8086:
		switch (did) {
		case 0x3590:
		case 0x3592:
			/* Intel 7520 or 7320 */
			pciebar = pci_cfgregread(0, 0, 0, 0xce, 2) << 16;
			pcie_cfgregopen(pciebar, 0, 255);
			break;
		case 0x2580:
		case 0x2584:
		case 0x2590:
			/* Intel 915, 925, or 915GM */
			pciebar = pci_cfgregread(0, 0, 0, 0x48, 4);
			pcie_cfgregopen(pciebar, 0, 255);
			break;
		}
	}

	if (bootverbose && cfgmech == CFGMECH_PCIE)
		device_printf(dev, "Enabled ECAM PCIe accesses\n");
}