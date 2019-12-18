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
struct bwi_softc {int sc_card_flags; scalar_t__ sc_pci_subvid; scalar_t__ sc_bbp_id; int sc_pci_revid; int sc_pci_subdid; } ;

/* Variables and functions */
 scalar_t__ BWI_BBPID_BCM4301 ; 
 int BWI_CARD_F_BT_COEXIST ; 
 int BWI_CARD_F_PA_GPIO9 ; 
 int /*<<< orphan*/  BWI_DBG_ATTACH ; 
 int /*<<< orphan*/  BWI_SPROM_CARD_FLAGS ; 
 int /*<<< orphan*/  DPRINTF (struct bwi_softc*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ PCI_VENDOR_APPLE ; 
 scalar_t__ PCI_VENDOR_DELL ; 
 int bwi_read_sprom (struct bwi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwi_get_card_flags(struct bwi_softc *sc)
{
#define	PCI_VENDOR_APPLE 0x106b
#define	PCI_VENDOR_DELL  0x1028
	sc->sc_card_flags = bwi_read_sprom(sc, BWI_SPROM_CARD_FLAGS);
	if (sc->sc_card_flags == 0xffff)
		sc->sc_card_flags = 0;

	if (sc->sc_pci_subvid == PCI_VENDOR_DELL &&
	    sc->sc_bbp_id == BWI_BBPID_BCM4301 &&
	    sc->sc_pci_revid == 0x74)
		sc->sc_card_flags |= BWI_CARD_F_BT_COEXIST;

	if (sc->sc_pci_subvid == PCI_VENDOR_APPLE &&
	    sc->sc_pci_subdid == 0x4e && /* XXX */
	    sc->sc_pci_revid > 0x40)
		sc->sc_card_flags |= BWI_CARD_F_PA_GPIO9;

	DPRINTF(sc, BWI_DBG_ATTACH, "card flags 0x%04x\n", sc->sc_card_flags);
#undef PCI_VENDOR_DELL
#undef PCI_VENDOR_APPLE
}