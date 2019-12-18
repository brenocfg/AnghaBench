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
struct ath_softc {int sc_pci_devinfo; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int ATH_MCI_ANT_ARCH_1_ANT_PA_LNA_SHARED ; 
 int ATH_MCI_ANT_ARCH_2_ANT_PA_LNA_NON_SHARED ; 
 int ATH_MCI_CONFIG_ANT_ARCH ; 
 int ATH_MCI_CONFIG_ANT_ARCH_S ; 
 int ATH_PCI_AR9565_1ANT ; 
 int ATH_PCI_AR9565_2ANT ; 
 int ATH_PCI_BT_ANT_DIV ; 
 int ath_btcoex_cfg_mci (struct ath_softc*,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ath_btcoex_cfg_wb335b(struct ath_softc *sc)
{
	uint32_t flags;
	int do_btdiv = 0;

	/* ath9k default */
	flags = 0xa4c1;

	/* 1-ant and 2-ant AR9565 */
	/*
	 * XXX TODO: ensure these actually make it down to the
	 * HAL correctly!
	 */
	if (sc->sc_pci_devinfo & ATH_PCI_AR9565_1ANT) {
		flags &= ~ATH_MCI_CONFIG_ANT_ARCH;
		flags |= ATH_MCI_ANT_ARCH_1_ANT_PA_LNA_SHARED <<
		    ATH_MCI_CONFIG_ANT_ARCH_S;
	} else if (sc->sc_pci_devinfo & ATH_PCI_AR9565_2ANT) {
		flags &= ~ATH_MCI_CONFIG_ANT_ARCH;
		flags |= ATH_MCI_ANT_ARCH_2_ANT_PA_LNA_NON_SHARED <<
		    ATH_MCI_CONFIG_ANT_ARCH_S;
	}

	if (sc->sc_pci_devinfo & ATH_PCI_BT_ANT_DIV) {
		do_btdiv = 1;
	}

	device_printf(sc->sc_dev, "Enabling WB335 BTCOEX\n");
	/* XXX from ath9k */
	return (ath_btcoex_cfg_mci(sc, flags, do_btdiv));
}