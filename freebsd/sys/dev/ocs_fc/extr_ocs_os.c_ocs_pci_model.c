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
typedef  int uint16_t ;

/* Variables and functions */
#define  PCI_PRODUCT_EMULEX_OCE16002 131 
#define  PCI_PRODUCT_EMULEX_OCE1600_VF 130 
#define  PCI_PRODUCT_EMULEX_OCE50102 129 
#define  PCI_PRODUCT_EMULEX_OCE50102_VF 128 

const char *
ocs_pci_model(uint16_t vendor, uint16_t device)
{
	switch (device) {
	case PCI_PRODUCT_EMULEX_OCE16002:	return "OCE16002";
	case PCI_PRODUCT_EMULEX_OCE1600_VF:	return "OCE1600_VF";
	case PCI_PRODUCT_EMULEX_OCE50102:	return "OCE50102";
	case PCI_PRODUCT_EMULEX_OCE50102_VF:	return "OCE50102_VR";
	default:
		break;
	}

	return "unknown";
}