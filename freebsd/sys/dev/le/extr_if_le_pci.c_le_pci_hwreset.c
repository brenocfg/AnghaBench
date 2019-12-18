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
struct lance_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LE_B20_SSTYLE_PCNETPCI2 ; 
 int /*<<< orphan*/  LE_BCR20 ; 
 int /*<<< orphan*/  le_pci_wrbcr (struct lance_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
le_pci_hwreset(struct lance_softc *sc)
{

	/*
	 * Chip is stopped. Set software style to PCnet-PCI (32-bit).
	 * Actually, am79900.c implements ILACC support (hence its
	 * name) but unfortunately VMware does not. As far as this
	 * driver is concerned that should not make a difference
	 * though, as the settings used have the same meaning for
	 * both, ILACC and PCnet-PCI (note that there would be a
	 * difference for the ADD_FCS/NO_FCS bit if used).
	 */
	le_pci_wrbcr(sc, LE_BCR20, LE_B20_SSTYLE_PCNETPCI2);
}