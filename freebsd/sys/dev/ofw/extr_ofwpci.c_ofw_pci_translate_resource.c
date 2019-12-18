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
struct ofw_pci_softc {int sc_nrange; struct ofw_pci_range* sc_range; } ;
struct ofw_pci_range {int pci_hi; scalar_t__ pci; scalar_t__ size; scalar_t__ host; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int OFW_PCI_PHYS_HI_SPACEMASK ; 
#define  OFW_PCI_PHYS_HI_SPACE_IO 130 
#define  OFW_PCI_PHYS_HI_SPACE_MEM32 129 
#define  OFW_PCI_PHYS_HI_SPACE_MEM64 128 
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 struct ofw_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofw_pci_translate_resource(device_t bus, int type, rman_res_t start,
	rman_res_t *newstart)
{
	struct ofw_pci_softc *sc;
	struct ofw_pci_range *rp;
	int space;

	sc = device_get_softc(bus);

	/*
	 * Map this through the ranges list
	 */
	for (rp = sc->sc_range; rp < sc->sc_range + sc->sc_nrange &&
	    rp->pci_hi != 0; rp++) {
		if (start < rp->pci || start >= rp->pci + rp->size)
			continue;

		switch (rp->pci_hi & OFW_PCI_PHYS_HI_SPACEMASK) {
		case OFW_PCI_PHYS_HI_SPACE_IO:
			space = SYS_RES_IOPORT;
			break;
		case OFW_PCI_PHYS_HI_SPACE_MEM32:
		case OFW_PCI_PHYS_HI_SPACE_MEM64:
			space = SYS_RES_MEMORY;
			break;
		default:
			space = -1;
		}

		if (type == space) {
			start += (rp->host - rp->pci);
			break;
		}
	}
	*newstart = start;
	return (0);
}