#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ath_softc {int sc_pci_devinfo; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_6__ {int no_pll_pwrsave; } ;
struct TYPE_9__ {TYPE_1__ config; } ;
struct TYPE_8__ {int /*<<< orphan*/  hw_caps; } ;
struct TYPE_7__ {int ath_hal_ext_lna_ctl_gpio; int ath_hal_ant_ctrl_comm2g_switch_enable; int ath_hal_pcie_waen; void* ath_hal_min_gainidx; void* ath_hal_ext_atten_margin_cfg; } ;
typedef  TYPE_2__ HAL_OPS_CONFIG ;

/* Variables and functions */
 void* AH_TRUE ; 
 int /*<<< orphan*/  ATH9K_HW_CAP_ANT_DIV_COMB ; 
 int /*<<< orphan*/  ATH9K_HW_CAP_BT_ANT_DIV ; 
 int ATH9K_PCI_AR9565_1ANT ; 
 int ATH9K_PCI_AR9565_2ANT ; 
 int ATH9K_PCI_BT_ANT_DIV ; 
 int ATH9K_PCI_NO_PLL_PWRSAVE ; 
 int ATH_PCI_AR9565_1ANT ; 
 int ATH_PCI_AR9565_2ANT ; 
 int ATH_PCI_BT_ANT_DIV ; 
 int ATH_PCI_CUS198 ; 
 int ATH_PCI_CUS217 ; 
 int ATH_PCI_CUS230 ; 
 int ATH_PCI_CUS252 ; 
 int ATH_PCI_D3_L1_WAR ; 
 int ATH_PCI_KILLER ; 
 TYPE_5__* ah ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* pCap ; 

__attribute__((used)) static void
ath_setup_hal_config(struct ath_softc *sc, HAL_OPS_CONFIG *ah_config)
{
	/* XXX TODO: only for PCI devices? */

	if (sc->sc_pci_devinfo & (ATH_PCI_CUS198 | ATH_PCI_CUS230)) {
		ah_config->ath_hal_ext_lna_ctl_gpio = 0x200; /* bit 9 */
		ah_config->ath_hal_ext_atten_margin_cfg = AH_TRUE;
		ah_config->ath_hal_min_gainidx = AH_TRUE;
		ah_config->ath_hal_ant_ctrl_comm2g_switch_enable = 0x000bbb88;
		/* XXX low_rssi_thresh */
		/* XXX fast_div_bias */
		device_printf(sc->sc_dev, "configuring for %s\n",
		    (sc->sc_pci_devinfo & ATH_PCI_CUS198) ?
		    "CUS198" : "CUS230");
	}

	if (sc->sc_pci_devinfo & ATH_PCI_CUS217)
		device_printf(sc->sc_dev, "CUS217 card detected\n");

	if (sc->sc_pci_devinfo & ATH_PCI_CUS252)
		device_printf(sc->sc_dev, "CUS252 card detected\n");

	if (sc->sc_pci_devinfo & ATH_PCI_AR9565_1ANT)
		device_printf(sc->sc_dev, "WB335 1-ANT card detected\n");

	if (sc->sc_pci_devinfo & ATH_PCI_AR9565_2ANT)
		device_printf(sc->sc_dev, "WB335 2-ANT card detected\n");

	if (sc->sc_pci_devinfo & ATH_PCI_BT_ANT_DIV)
		device_printf(sc->sc_dev,
		    "Bluetooth Antenna Diversity card detected\n");

	if (sc->sc_pci_devinfo & ATH_PCI_KILLER)
		device_printf(sc->sc_dev, "Killer Wireless card detected\n");

#if 0
        /*
         * Some WB335 cards do not support antenna diversity. Since
         * we use a hardcoded value for AR9565 instead of using the
         * EEPROM/OTP data, remove the combining feature from
         * the HW capabilities bitmap.
         */
        if (sc->sc_pci_devinfo & (ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_AR9565_2ANT)) {
                if (!(sc->sc_pci_devinfo & ATH9K_PCI_BT_ANT_DIV))
                        pCap->hw_caps &= ~ATH9K_HW_CAP_ANT_DIV_COMB;
        }

        if (sc->sc_pci_devinfo & ATH9K_PCI_BT_ANT_DIV) {
                pCap->hw_caps |= ATH9K_HW_CAP_BT_ANT_DIV;
                device_printf(sc->sc_dev, "Set BT/WLAN RX diversity capability\n");
        }
#endif

        if (sc->sc_pci_devinfo & ATH_PCI_D3_L1_WAR) {
                ah_config->ath_hal_pcie_waen = 0x0040473b;
                device_printf(sc->sc_dev, "Enable WAR for ASPM D3/L1\n");
        }

#if 0
        if (sc->sc_pci_devinfo & ATH9K_PCI_NO_PLL_PWRSAVE) {
                ah->config.no_pll_pwrsave = true;
                device_printf(sc->sc_dev, "Disable PLL PowerSave\n");
        }
#endif

}