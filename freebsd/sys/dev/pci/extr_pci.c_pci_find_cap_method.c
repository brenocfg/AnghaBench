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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int hdrtype; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  TYPE_1__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int PCICAP_ID ; 
 int PCICAP_NEXTPTR ; 
 int PCIM_HDRTYPE ; 
#define  PCIM_HDRTYPE_BRIDGE 130 
#define  PCIM_HDRTYPE_CARDBUS 129 
#define  PCIM_HDRTYPE_NORMAL 128 
 int PCIM_STATUS_CAPPRESENT ; 
 int PCIR_CAP_PTR ; 
 int PCIR_CAP_PTR_2 ; 
 int PCIR_STATUS ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 

int
pci_find_cap_method(device_t dev, device_t child, int capability,
    int *capreg)
{
	struct pci_devinfo *dinfo = device_get_ivars(child);
	pcicfgregs *cfg = &dinfo->cfg;
	uint32_t status;
	uint8_t ptr;

	/*
	 * Check the CAP_LIST bit of the PCI status register first.
	 */
	status = pci_read_config(child, PCIR_STATUS, 2);
	if (!(status & PCIM_STATUS_CAPPRESENT))
		return (ENXIO);

	/*
	 * Determine the start pointer of the capabilities list.
	 */
	switch (cfg->hdrtype & PCIM_HDRTYPE) {
	case PCIM_HDRTYPE_NORMAL:
	case PCIM_HDRTYPE_BRIDGE:
		ptr = PCIR_CAP_PTR;
		break;
	case PCIM_HDRTYPE_CARDBUS:
		ptr = PCIR_CAP_PTR_2;
		break;
	default:
		/* XXX: panic? */
		return (ENXIO);		/* no extended capabilities support */
	}
	ptr = pci_read_config(child, ptr, 1);

	/*
	 * Traverse the capabilities list.
	 */
	while (ptr != 0) {
		if (pci_read_config(child, ptr + PCICAP_ID, 1) == capability) {
			if (capreg != NULL)
				*capreg = ptr;
			return (0);
		}
		ptr = pci_read_config(child, ptr + PCICAP_NEXTPTR, 1);
	}

	return (ENOENT);
}