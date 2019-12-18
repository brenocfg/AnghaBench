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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct bwi_softc {scalar_t__ sc_bbp_id; int sc_bbp_rev; int /*<<< orphan*/  sc_dev; } ;
struct bwi_rf {int rf_ctrl_adj; int rf_rev; int /*<<< orphan*/  rf_ant_mode; int /*<<< orphan*/  rf_curchan; void* rf_manu; void* rf_type; void* rf_lo_update; void* rf_calc_noise; void* rf_calc_rssi; int /*<<< orphan*/  rf_set_nrssi_thr; int /*<<< orphan*/  rf_calc_nrssi_slope; void* rf_off; void* rf_on; void* rf_ctrl_rd; } ;
struct bwi_phy {int phy_mode; int phy_rev; } ;
struct bwi_mac {int mac_rev; struct bwi_rf mac_rf; struct bwi_phy mac_phy; struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_ANT_MODE_AUTO ; 
 scalar_t__ BWI_BBPID_BCM4317 ; 
 int /*<<< orphan*/  BWI_RFINFO_MANUFACT_MASK ; 
 int /*<<< orphan*/  BWI_RFINFO_REV_MASK ; 
 int /*<<< orphan*/  BWI_RFINFO_TYPE_MASK ; 
 int /*<<< orphan*/  BWI_RF_CTRL ; 
 void* BWI_RF_CTRL_RD_11A ; 
 void* BWI_RF_CTRL_RD_11BG ; 
 int /*<<< orphan*/  BWI_RF_CTRL_RFINFO ; 
 int /*<<< orphan*/  BWI_RF_DATA_HI ; 
 int /*<<< orphan*/  BWI_RF_DATA_LO ; 
 void* BWI_RF_MANUFACT_BCM ; 
 void* BWI_RF_T_BCM2050 ; 
 void* BWI_RF_T_BCM2053 ; 
 void* BWI_RF_T_BCM2060 ; 
 int CSR_READ_2 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  IEEE80211_CHAN_ANY ; 
#define  IEEE80211_MODE_11A 130 
#define  IEEE80211_MODE_11B 129 
#define  IEEE80211_MODE_11G 128 
 void* __SHIFTOUT (int,int /*<<< orphan*/ ) ; 
 void* bwi_rf_calc_noise_bcm2050 ; 
 void* bwi_rf_calc_noise_bcm2053 ; 
 void* bwi_rf_calc_noise_bcm2060 ; 
 int /*<<< orphan*/  bwi_rf_calc_nrssi_slope_11b ; 
 int /*<<< orphan*/  bwi_rf_calc_nrssi_slope_11g ; 
 void* bwi_rf_calc_rssi_bcm2050 ; 
 void* bwi_rf_calc_rssi_bcm2053 ; 
 void* bwi_rf_calc_rssi_bcm2060 ; 
 void* bwi_rf_lo_update_11b ; 
 void* bwi_rf_lo_update_11g ; 
 void* bwi_rf_off_11a ; 
 void* bwi_rf_off_11bg ; 
 void* bwi_rf_off_11g_rev5 ; 
 void* bwi_rf_on_11a ; 
 void* bwi_rf_on_11bg ; 
 int /*<<< orphan*/  bwi_rf_set_nrssi_thr_11b ; 
 int /*<<< orphan*/  bwi_rf_set_nrssi_thr_11g ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

int
bwi_rf_attach(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	struct bwi_phy *phy = &mac->mac_phy;
	struct bwi_rf *rf = &mac->mac_rf;
	uint16_t type, manu;
	uint8_t rev;

	/*
	 * Get RF manufacture/type/revision
	 */
	if (sc->sc_bbp_id == BWI_BBPID_BCM4317) {
		/*
		 * Fake a BCM2050 RF
		 */
		manu = BWI_RF_MANUFACT_BCM;
		type = BWI_RF_T_BCM2050;
		if (sc->sc_bbp_rev == 0)
			rev = 3;
		else if (sc->sc_bbp_rev == 1)
			rev = 4;
		else
			rev = 5;
	} else {
		uint32_t val;

		CSR_WRITE_2(sc, BWI_RF_CTRL, BWI_RF_CTRL_RFINFO);
		val = CSR_READ_2(sc, BWI_RF_DATA_HI);
		val <<= 16;

		CSR_WRITE_2(sc, BWI_RF_CTRL, BWI_RF_CTRL_RFINFO);
		val |= CSR_READ_2(sc, BWI_RF_DATA_LO);

		manu = __SHIFTOUT(val, BWI_RFINFO_MANUFACT_MASK);
		type = __SHIFTOUT(val, BWI_RFINFO_TYPE_MASK);
		rev = __SHIFTOUT(val, BWI_RFINFO_REV_MASK);
	}
	device_printf(sc->sc_dev, "RF: manu 0x%03x, type 0x%04x, rev %u\n",
		      manu, type, rev);

	/*
	 * Verify whether the RF is supported
	 */
	rf->rf_ctrl_rd = 0;
	rf->rf_ctrl_adj = 0;
	switch (phy->phy_mode) {
	case IEEE80211_MODE_11A:
		if (manu != BWI_RF_MANUFACT_BCM ||
		    type != BWI_RF_T_BCM2060 ||
		    rev != 1) {
			device_printf(sc->sc_dev, "only BCM2060 rev 1 RF "
				      "is supported for 11A PHY\n");
			return ENXIO;
		}
		rf->rf_ctrl_rd = BWI_RF_CTRL_RD_11A;
		rf->rf_on = bwi_rf_on_11a;
		rf->rf_off = bwi_rf_off_11a;
		rf->rf_calc_rssi = bwi_rf_calc_rssi_bcm2060;
		rf->rf_calc_noise = bwi_rf_calc_noise_bcm2060;
		break;
	case IEEE80211_MODE_11B:
		if (type == BWI_RF_T_BCM2050) {
			rf->rf_ctrl_rd = BWI_RF_CTRL_RD_11BG;
			rf->rf_calc_rssi = bwi_rf_calc_rssi_bcm2050;
			rf->rf_calc_noise = bwi_rf_calc_noise_bcm2050;
		} else if (type == BWI_RF_T_BCM2053) {
			rf->rf_ctrl_adj = 1;
			rf->rf_calc_rssi = bwi_rf_calc_rssi_bcm2053;
			rf->rf_calc_noise = bwi_rf_calc_noise_bcm2053;
		} else {
			device_printf(sc->sc_dev, "only BCM2050/BCM2053 RF "
				      "is supported for 11B PHY\n");
			return ENXIO;
		}
		rf->rf_on = bwi_rf_on_11bg;
		rf->rf_off = bwi_rf_off_11bg;
		rf->rf_calc_nrssi_slope = bwi_rf_calc_nrssi_slope_11b;
		rf->rf_set_nrssi_thr = bwi_rf_set_nrssi_thr_11b;
		if (phy->phy_rev == 6)
			rf->rf_lo_update = bwi_rf_lo_update_11g;
		else
			rf->rf_lo_update = bwi_rf_lo_update_11b;
		break;
	case IEEE80211_MODE_11G:
		if (type != BWI_RF_T_BCM2050) {
			device_printf(sc->sc_dev, "only BCM2050 RF "
				      "is supported for 11G PHY\n");
			return ENXIO;
		}
		rf->rf_ctrl_rd = BWI_RF_CTRL_RD_11BG;
		rf->rf_on = bwi_rf_on_11bg;
		if (mac->mac_rev >= 5)
			rf->rf_off = bwi_rf_off_11g_rev5;
		else
			rf->rf_off = bwi_rf_off_11bg;
		rf->rf_calc_nrssi_slope = bwi_rf_calc_nrssi_slope_11g;
		rf->rf_set_nrssi_thr = bwi_rf_set_nrssi_thr_11g;
		rf->rf_calc_rssi = bwi_rf_calc_rssi_bcm2050;
		rf->rf_calc_noise = bwi_rf_calc_noise_bcm2050;
		rf->rf_lo_update = bwi_rf_lo_update_11g;
		break;
	default:
		device_printf(sc->sc_dev, "unsupported PHY mode\n");
		return ENXIO;
	}

	rf->rf_type = type;
	rf->rf_rev = rev;
	rf->rf_manu = manu;
	rf->rf_curchan = IEEE80211_CHAN_ANY;
	rf->rf_ant_mode = BWI_ANT_MODE_AUTO;
	return 0;
}