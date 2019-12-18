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
struct psycho_softc {int sc_half; } ;
typedef  int ofw_pci_intr_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int INTINO (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_INTERRUPT_VALID (int) ; 
 scalar_t__ PSR_PCIA0_INT_MAP ; 
 int /*<<< orphan*/  PSYCHO_READ8 (struct psycho_softc*,scalar_t__) ; 
 struct psycho_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int ofw_pci_route_interrupt_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
psycho_route_interrupt(device_t bridge, device_t dev, int pin)
{
	struct psycho_softc *sc;
	bus_addr_t intrmap;
	ofw_pci_intr_t mintr;

	mintr = ofw_pci_route_interrupt_common(bridge, dev, pin);
	if (PCI_INTERRUPT_VALID(mintr))
		return (mintr);
	/*
	 * If this is outside of the range for an intpin, it's likely a full
	 * INO, and no mapping is required at all; this happens on the U30,
	 * where there's no interrupt map at the Psycho node.  Fortunately,
	 * there seem to be no INOs in the intpin range on this boxen, so
	 * this easy heuristics will do.
	 */
	if (pin > 4)
		return (pin);
	/*
	 * Guess the INO; we always assume that this is a non-OBIO device,
	 * and that pin is a "real" intpin number.  Determine the mapping
	 * register to be used by the slot number.
	 * We only need to do this on E450s and U30s, though; here, the
	 * slot numbers for bus A are one-based, while those for bus B
	 * seemingly have an offset of 2 (hence the factor of 3 below).
	 */
	sc = device_get_softc(bridge);
	intrmap = PSR_PCIA0_INT_MAP +
	    8 * (pci_get_slot(dev) - 1 + 3 * sc->sc_half);
	mintr = INTINO(PSYCHO_READ8(sc, intrmap)) + pin - 1;
	device_printf(bridge,
	    "guessing interrupt %d for device %d.%d pin %d\n",
	    (int)mintr, pci_get_slot(dev), pci_get_function(dev), pin);
	return (mintr);
}