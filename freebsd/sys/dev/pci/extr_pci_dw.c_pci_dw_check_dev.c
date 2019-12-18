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
typedef  scalar_t__ u_int ;
struct pci_dw_softc {scalar_t__ bus_start; scalar_t__ bus_end; scalar_t__ root_bus; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PCI_DW_GET_LINK (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ PCI_FUNCMAX ; 
 scalar_t__ PCI_REGMAX ; 
 scalar_t__ PCI_SLOTMAX ; 

__attribute__((used)) static bool
pci_dw_check_dev(struct pci_dw_softc *sc, u_int bus, u_int slot, u_int func,
    u_int reg)
{
	bool status;
	int rv;

	if (bus < sc->bus_start || bus > sc->bus_end || slot > PCI_SLOTMAX ||
	    func > PCI_FUNCMAX || reg > PCI_REGMAX)
		return (false);

	/* link is needed for access to all non-root busses */
	if (bus != sc->root_bus) {
		rv = PCI_DW_GET_LINK(sc->dev, &status);
		if (rv != 0 || !status)
			return (false);
		return (true);
	}

	/* we have only 1 device with 1 function root port */
	if (slot > 0 || func > 0)
		return (false);
	return (true);
}