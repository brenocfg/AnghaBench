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
struct ofw_bus_iinfo {scalar_t__ opi_imapsz; } ;
struct ofw_pcib_softc {struct ofw_bus_iinfo ops_iinfo; } ;
struct ofw_pci_register {int phys_hi; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  pintr ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  mintr ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int cell_t ;

/* Variables and functions */
 int OFW_PCI_PHYS_HI_BUSSHIFT ; 
 int OFW_PCI_PHYS_HI_DEVICESHIFT ; 
 int OFW_PCI_PHYS_HI_FUNCTIONSHIFT ; 
 int PCIB_ROUTE_INTERRUPT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct ofw_pci_register*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ofw_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ofw_bus_lookup_imap (int /*<<< orphan*/ ,struct ofw_bus_iinfo*,struct ofw_pci_register*,int,int*,int,int*,int,int /*<<< orphan*/ *) ; 
 int ofw_bus_map_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int pci_get_bus (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 
 int pcib_route_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ofw_pcib_pci_route_interrupt(device_t bridge, device_t dev, int intpin)
{
	struct ofw_pcib_softc *sc;
	struct ofw_bus_iinfo *ii;
	struct ofw_pci_register reg;
	cell_t pintr, mintr[2];
	int intrcells;
	phandle_t iparent;

	sc = device_get_softc(bridge);
	ii = &sc->ops_iinfo;
	if (ii->opi_imapsz > 0) {
		pintr = intpin;

		/* Fabricate imap information if this isn't an OFW device */
		bzero(&reg, sizeof(reg));
		reg.phys_hi = (pci_get_bus(dev) << OFW_PCI_PHYS_HI_BUSSHIFT) |
		    (pci_get_slot(dev) << OFW_PCI_PHYS_HI_DEVICESHIFT) |
		    (pci_get_function(dev) << OFW_PCI_PHYS_HI_FUNCTIONSHIFT);

		intrcells = ofw_bus_lookup_imap(ofw_bus_get_node(dev), ii, &reg,
		    sizeof(reg), &pintr, sizeof(pintr), mintr, sizeof(mintr),
		    &iparent);
		if (intrcells) {
			/*
			 * If we've found a mapping, return it and don't map
			 * it again on higher levels - that causes problems
			 * in some cases, and never seems to be required.
			 */
			mintr[0] = ofw_bus_map_intr(dev, iparent, intrcells,
			    mintr);
			return (mintr[0]);
		}
	} else if (intpin >= 1 && intpin <= 4) {
		/*
		 * When an interrupt map is missing, we need to do the
		 * standard PCI swizzle and continue mapping at the parent.
		 */
		return (pcib_route_interrupt(bridge, dev, intpin));
	}
	return (PCIB_ROUTE_INTERRUPT(device_get_parent(device_get_parent(
	    bridge)), bridge, intpin));
}