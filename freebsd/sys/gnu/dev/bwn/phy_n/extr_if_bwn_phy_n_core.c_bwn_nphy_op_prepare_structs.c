#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ board_vendor; int board_srom_rev; int board_flags2; scalar_t__ board_devid; } ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; TYPE_1__ sc_board_info; } ;
struct bwn_phy_n {int hang_avoid; int gain_boost; int txrx_chain; int phyrxchain; int perical; int* tx_pwr_idx; int txpwrctrl; int pwg_gain_5ghz; int ipa2g_on; int ipa5g_on; int /*<<< orphan*/  spur_avoid; } ;
struct bwn_phy {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {struct bwn_softc* mac_sc; struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int BHND_BFL2_5G_PWRGAIN ; 
 int BHND_BFL2_TXPWRCTRL_EN ; 
 int /*<<< orphan*/  BHND_NVAR_EXTPAGAIN2G ; 
 int /*<<< orphan*/  BHND_NVAR_EXTPAGAIN5G ; 
 int /*<<< orphan*/  BWN_ERRPRINTF (struct bwn_softc*,char*,int) ; 
 int /*<<< orphan*/  BWN_SPUR_AVOID_AUTO ; 
 int /*<<< orphan*/  BWN_SPUR_AVOID_DISABLE ; 
 scalar_t__ PCI_DEVID_BCM4321_D11N ; 
 scalar_t__ PCI_DEVID_BCM4321_D11N5G ; 
 scalar_t__ PCI_VENDOR_APPLE ; 
 int bhnd_get_hwrev (int /*<<< orphan*/ ) ; 
 int bhnd_nvram_getvar_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (struct bwn_phy_n*,int /*<<< orphan*/ ,int) ; 

int
bwn_nphy_op_prepare_structs(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_n *nphy = phy->phy_n;
	int error;

	memset(nphy, 0, sizeof(*nphy));

	nphy->hang_avoid = (phy->rev == 3 || phy->rev == 4);
	nphy->spur_avoid = (phy->rev >= 3) ?
				BWN_SPUR_AVOID_AUTO : BWN_SPUR_AVOID_DISABLE;
	nphy->gain_boost = true; /* this way we follow wl, assume it is true */
	nphy->txrx_chain = 2; /* sth different than 0 and 1 for now */
	nphy->phyrxchain = 3; /* to avoid bwn_nphy_set_rx_core_state like wl */
	nphy->perical = 2; /* avoid additional rssi cal on init (like wl) */
	/* 128 can mean disabled-by-default state of TX pwr ctl. Max value is
	 * 0x7f == 127 and we check for 128 when restoring TX pwr ctl. */
	nphy->tx_pwr_idx[0] = 128;
	nphy->tx_pwr_idx[1] = 128;

	/* Hardware TX power control and 5GHz power gain */
	nphy->txpwrctrl = false;
	nphy->pwg_gain_5ghz = false;
	if (mac->mac_phy.rev >= 3 ||
	    (sc->sc_board_info.board_vendor == PCI_VENDOR_APPLE &&
	     (bhnd_get_hwrev(sc->sc_dev) == 11 || bhnd_get_hwrev(sc->sc_dev) == 12))) {
		nphy->txpwrctrl = true;
		nphy->pwg_gain_5ghz = true;
	} else if (sc->sc_board_info.board_srom_rev >= 4) {
		if (mac->mac_phy.rev >= 2 &&
		    (sc->sc_board_info.board_flags2 & BHND_BFL2_TXPWRCTRL_EN)) {
			nphy->txpwrctrl = true;
			if ((sc->sc_board_info.board_devid == PCI_DEVID_BCM4321_D11N) ||
			    (sc->sc_board_info.board_devid == PCI_DEVID_BCM4321_D11N5G))
				nphy->pwg_gain_5ghz = true;
		} else if (sc->sc_board_info.board_flags2 & BHND_BFL2_5G_PWRGAIN) {
			nphy->pwg_gain_5ghz = true;
		}
	}

	if (mac->mac_phy.rev >= 3) {
		uint8_t extpa_gain2g, extpa_gain5g;

		error = bhnd_nvram_getvar_uint8(sc->sc_dev,
		    BHND_NVAR_EXTPAGAIN2G, &extpa_gain2g);
		if (error) {
			BWN_ERRPRINTF(mac->mac_sc, "Error reading 2GHz EPA "
			    "gain configuration from NVRAM: %d\n", error);
			return (error);
		}

		error = bhnd_nvram_getvar_uint8(sc->sc_dev,
		    BHND_NVAR_EXTPAGAIN5G, &extpa_gain5g);
		if (error) {
			BWN_ERRPRINTF(mac->mac_sc, "Error reading 5GHz EPA "
			    "gain configuration from NVRAM: %d\n", error);
			return (error);
		}

		nphy->ipa2g_on = (extpa_gain2g == 2);
		nphy->ipa5g_on = (extpa_gain5g == 2);
	}

	return (0);
}