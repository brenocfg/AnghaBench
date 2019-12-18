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
 int ENXIO ; 
 scalar_t__ PCIC_BRIDGE ; 
 scalar_t__ PCIS_BRIDGE_ISA ; 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_get_subclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
isab_pci_probe(device_t dev)
{
    int		matched = 0;

    /*
     * Try for a generic match based on class/subclass.
     */
    if ((pci_get_class(dev) == PCIC_BRIDGE) &&
	(pci_get_subclass(dev) == PCIS_BRIDGE_ISA)) {
	matched = 1;
    } else {
	/*
	 * These are devices that we *know* are PCI:ISA bridges. 
	 * Sometimes, however, they don't report themselves as
	 * such.  Check in case one of them is pretending to be
	 * something else.
	 */
	switch (pci_get_devid(dev)) {
	case 0x04848086:	/* Intel 82378ZB/82378IB */
	case 0x122e8086:	/* Intel 82371FB */
	case 0x70008086:	/* Intel 82371SB */
	case 0x71108086:	/* Intel 82371AB */
	case 0x71988086:	/* Intel 82443MX */
	case 0x24108086:	/* Intel 82801AA (ICH) */
	case 0x24208086:	/* Intel 82801AB (ICH0) */
	case 0x24408086:	/* Intel 82801AB (ICH2) */
	case 0x00061004:	/* VLSI 82C593 */
	case 0x05861106:	/* VIA 82C586 */
	case 0x05961106:	/* VIA 82C596 */
	case 0x06861106:	/* VIA 82C686 */
	case 0x153310b9:	/* AcerLabs M1533 */
	case 0x154310b9:	/* AcerLabs M1543 */
	case 0x00081039:	/* SiS 85c503 */
	case 0x00001078:	/* Cyrix Cx5510 */
	case 0x01001078:	/* Cyrix Cx5530 */
	case 0xc7001045:	/* OPTi 82C700 (FireStar) */
	case 0x886a1060:	/* UMC UM8886 ISA */
	case 0x02001166:	/* ServerWorks IB6566 PCI */
	    if (bootverbose)
		printf("PCI-ISA bridge with incorrect subclass 0x%x\n",
		       pci_get_subclass(dev));
	    matched = 1;
	    break;
	
	default:
	    break;
	}
    }

    if (matched) {
	device_set_desc(dev, "PCI-ISA bridge");
	return(-10000);
    }
    return(ENXIO);
}