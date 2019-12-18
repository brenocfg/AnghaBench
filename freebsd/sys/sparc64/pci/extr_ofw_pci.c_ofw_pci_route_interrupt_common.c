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
struct ofw_pci_softc {int /*<<< orphan*/  sc_pci_iinfo; } ;
struct ofw_pci_register {int dummy; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  pintr ;
typedef  int ofw_pci_intr_t ;
typedef  int /*<<< orphan*/  mintr ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCI_INVALID_IRQ ; 
 struct ofw_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_lookup_imap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ofw_pci_register*,int,int*,int,int*,int,int /*<<< orphan*/ *) ; 

ofw_pci_intr_t
ofw_pci_route_interrupt_common(device_t bridge, device_t dev, int pin)
{
	struct ofw_pci_softc *sc;
	struct ofw_pci_register reg;
	ofw_pci_intr_t pintr, mintr;

	sc = device_get_softc(bridge);
	pintr = pin;
	if (ofw_bus_lookup_imap(ofw_bus_get_node(dev), &sc->sc_pci_iinfo,
	    &reg, sizeof(reg), &pintr, sizeof(pintr), &mintr, sizeof(mintr),
	    NULL) != 0)
		return (mintr);
	return (PCI_INVALID_IRQ);
}