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
typedef  int /*<<< orphan*/  uint16_t ;
struct le_pci_softc {int /*<<< orphan*/  sc_rres; } ;
struct lance_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  PCNET_PCI_BDP ; 
 int /*<<< orphan*/  PCNET_PCI_RAP ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
le_pci_wrbcr(struct lance_softc *sc, uint16_t port, uint16_t val)
{
	struct le_pci_softc *lesc = (struct le_pci_softc *)sc;

	bus_write_2(lesc->sc_rres, PCNET_PCI_RAP, port);
	bus_barrier(lesc->sc_rres, PCNET_PCI_RAP, 2, BUS_SPACE_BARRIER_WRITE);
	bus_write_2(lesc->sc_rres, PCNET_PCI_BDP, val);
}