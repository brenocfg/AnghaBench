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
typedef  int uint32_t ;
struct ofw_pci_softc {int /*<<< orphan*/  sc_pci_iinfo; } ;
struct ofw_pci_register {int phys_hi; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  pintr ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  mintr ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int OFW_PCI_PHYS_HI_BUSSHIFT ; 
 int OFW_PCI_PHYS_HI_DEVICESHIFT ; 
 int OFW_PCI_PHYS_HI_FUNCTIONSHIFT ; 
 int PCI_INTR_PINS ; 
 int PCI_INVALID_IRQ ; 
 int PCI_MAP_INTR ; 
 int /*<<< orphan*/  bzero (struct ofw_pci_register*,int) ; 
 struct ofw_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ofw_bus_lookup_imap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ofw_pci_register*,int,int*,int,int*,int,int /*<<< orphan*/ *) ; 
 int ofw_bus_map_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int pci_get_bus (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 

int
ofw_pci_route_interrupt(device_t bus, device_t dev, int pin)
{
	struct ofw_pci_softc *sc;
	struct ofw_pci_register reg;
	uint32_t pintr, mintr[PCI_MAP_INTR];
	int intrcells;
	phandle_t iparent;

	sc = device_get_softc(bus);
	pintr = pin;

	/* Fabricate imap information in case this isn't an OFW device */
	bzero(&reg, sizeof(reg));
	reg.phys_hi = (pci_get_bus(dev) << OFW_PCI_PHYS_HI_BUSSHIFT) |
	    (pci_get_slot(dev) << OFW_PCI_PHYS_HI_DEVICESHIFT) |
	    (pci_get_function(dev) << OFW_PCI_PHYS_HI_FUNCTIONSHIFT);

	intrcells = ofw_bus_lookup_imap(ofw_bus_get_node(dev),
	    &sc->sc_pci_iinfo, &reg, sizeof(reg), &pintr, sizeof(pintr),
	    mintr, sizeof(mintr), &iparent);
	if (intrcells != 0) {
		pintr = ofw_bus_map_intr(dev, iparent, intrcells, mintr);
		return (pintr);
	}

	/*
	 * Maybe it's a real interrupt, not an intpin
	 */
	if (pin > PCI_INTR_PINS)
		return (pin);

	device_printf(bus, "could not route pin %d for device %d.%d\n",
	    pin, pci_get_slot(dev), pci_get_function(dev));
	return (PCI_INVALID_IRQ);
}