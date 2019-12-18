#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {scalar_t__ pcie_location; } ;
struct TYPE_4__ {TYPE_1__ pcie; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
typedef  TYPE_2__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCI_EXTCAP_ID (int /*<<< orphan*/ ) ; 
 int PCI_EXTCAP_NEXTPTR (int /*<<< orphan*/ ) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int,int) ; 

int
pci_find_next_extcap_method(device_t dev, device_t child, int capability,
    int start, int *capreg)
{
	struct pci_devinfo *dinfo = device_get_ivars(child);
	pcicfgregs *cfg = &dinfo->cfg;
	uint32_t ecap;
	uint16_t ptr;

	/* Only supported for PCI-express devices. */
	if (cfg->pcie.pcie_location == 0)
		return (ENXIO);

	ecap = pci_read_config(child, start, 4);
	KASSERT(PCI_EXTCAP_ID(ecap) == capability,
	    ("start extended capability is not expected capability"));
	ptr = PCI_EXTCAP_NEXTPTR(ecap);
	while (ptr != 0) {
		ecap = pci_read_config(child, ptr, 4);
		if (PCI_EXTCAP_ID(ecap) == capability) {
			if (capreg != NULL)
				*capreg = ptr;
			return (0);
		}
		ptr = PCI_EXTCAP_NEXTPTR(ecap);
	}

	return (ENOENT);
}