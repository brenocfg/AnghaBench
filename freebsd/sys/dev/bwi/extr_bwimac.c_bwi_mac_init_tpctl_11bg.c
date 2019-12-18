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
typedef  int /*<<< orphan*/  tpctl_orig ;
typedef  int /*<<< orphan*/  tpctl ;
struct bwi_tpctl {int bbp_atten; int rf_atten; scalar_t__ tp_ctrl1; } ;
struct bwi_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwi_rf {scalar_t__ rf_type; int rf_rev; scalar_t__ rf_idle_tssi; scalar_t__ rf_base_tssi; } ;
struct bwi_phy {scalar_t__ phy_mode; int phy_flags; int phy_rev; } ;
struct bwi_mac {int mac_flags; int /*<<< orphan*/  mac_tpctl; struct bwi_rf mac_rf; struct bwi_phy mac_phy; struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_BBP_ATTEN ; 
 int BWI_DBG_INIT ; 
 int BWI_DBG_MAC ; 
 int BWI_DBG_TXPOWER ; 
 scalar_t__ BWI_IS_BRCM_BU4306 (struct bwi_softc*) ; 
 int BWI_MAC_F_TPCTL_ERROR ; 
 int BWI_MAC_F_TPCTL_INITED ; 
 int BWI_PHY_F_LINKED ; 
 scalar_t__ BWI_RF_T_BCM2050 ; 
 int /*<<< orphan*/  CSR_CLRBITS_2 (struct bwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPRINTF (struct bwi_softc*,int,char*,scalar_t__) ; 
 scalar_t__ IEEE80211_MODE_11A ; 
 scalar_t__ IEEE80211_MODE_11B ; 
 scalar_t__ IEEE80211_MODE_11G ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PHY_READ (struct bwi_mac*,int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  RF_CLRBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  RF_SETBITS (struct bwi_mac*,int,int) ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct bwi_tpctl*,int) ; 
 int /*<<< orphan*/  bwi_mac_dummy_xmit (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_mac_set_tpctl_11bg (struct bwi_mac*,struct bwi_tpctl*) ; 
 int /*<<< orphan*/  bwi_rf_clear_tssi (struct bwi_mac*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

void
bwi_mac_init_tpctl_11bg(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	struct bwi_phy *phy = &mac->mac_phy;
	struct bwi_rf *rf = &mac->mac_rf;
	struct bwi_tpctl tpctl_orig;
	int restore_tpctl = 0;

	KASSERT(phy->phy_mode != IEEE80211_MODE_11A,
	    ("phy_mode %d", phy->phy_mode));

	if (BWI_IS_BRCM_BU4306(sc))
		return;

	PHY_WRITE(mac, 0x28, 0x8018);
	CSR_CLRBITS_2(sc, BWI_BBP_ATTEN, 0x20);

	if (phy->phy_mode == IEEE80211_MODE_11G) {
		if ((phy->phy_flags & BWI_PHY_F_LINKED) == 0)
			return;
		PHY_WRITE(mac, 0x47a, 0xc111);
	}
	if (mac->mac_flags & BWI_MAC_F_TPCTL_INITED)
		return;

	if (phy->phy_mode == IEEE80211_MODE_11B && phy->phy_rev >= 2 &&
	    rf->rf_type == BWI_RF_T_BCM2050) {
		RF_SETBITS(mac, 0x76, 0x84);
	} else {
		struct bwi_tpctl tpctl;

		/* Backup original TX power control variables */
		bcopy(&mac->mac_tpctl, &tpctl_orig, sizeof(tpctl_orig));
		restore_tpctl = 1;

		bcopy(&mac->mac_tpctl, &tpctl, sizeof(tpctl));
		tpctl.bbp_atten = 11;
		tpctl.tp_ctrl1 = 0;
#ifdef notyet
		if (rf->rf_rev >= 6 && rf->rf_rev <= 8)
			tpctl.rf_atten = 31;
		else
#endif
			tpctl.rf_atten = 9;

		bwi_mac_set_tpctl_11bg(mac, &tpctl);
	}

	bwi_mac_dummy_xmit(mac);

	mac->mac_flags |= BWI_MAC_F_TPCTL_INITED;
	rf->rf_base_tssi = PHY_READ(mac, 0x29);
	DPRINTF(sc, BWI_DBG_MAC | BWI_DBG_INIT | BWI_DBG_TXPOWER,
		"base tssi %d\n", rf->rf_base_tssi);

	if (abs(rf->rf_base_tssi - rf->rf_idle_tssi) >= 20) {
		device_printf(sc->sc_dev, "base tssi measure failed\n");
		mac->mac_flags |= BWI_MAC_F_TPCTL_ERROR;
	}

	if (restore_tpctl)
		bwi_mac_set_tpctl_11bg(mac, &tpctl_orig);
	else
		RF_CLRBITS(mac, 0x76, 0x84);

	bwi_rf_clear_tssi(mac);
}