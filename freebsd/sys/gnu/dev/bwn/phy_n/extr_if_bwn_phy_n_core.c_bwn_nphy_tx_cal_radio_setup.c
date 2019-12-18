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
typedef  int uint16_t ;
struct bwn_phy_n {int* tx_rx_cal_radio_saveregs; scalar_t__ ipa2g_on; scalar_t__ ipa5g_on; } ;
struct bwn_phy {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int B2055_C1_PWRDET_RXTX ; 
 int /*<<< orphan*/  B2055_C1_TX_BB_MXGM ; 
 int B2055_C1_TX_RF_IQCAL1 ; 
 int B2055_C1_TX_RF_IQCAL2 ; 
 int B2055_C2_PWRDET_RXTX ; 
 int /*<<< orphan*/  B2055_C2_TX_BB_MXGM ; 
 int B2055_C2_TX_RF_IQCAL1 ; 
 int B2055_C2_TX_RF_IQCAL2 ; 
 int B2055_CAL_LPOCTL ; 
 int B2055_CAL_RCALRTS ; 
 int B2055_CAL_RCCALRTS ; 
 int B2055_CAL_RVARCTL ; 
 int B2055_CAL_TS ; 
 int B2055_PADDRV ; 
 int B2055_PLL_LFC1 ; 
 int B2055_XOCTL1 ; 
 int B2055_XOCTL2 ; 
 int B2055_XOMISC ; 
 int B2055_XOREGUL ; 
 scalar_t__ BWN_BAND_5G ; 
 int /*<<< orphan*/  BWN_NPHY_BANDCTL ; 
 int BWN_NPHY_BANDCTL_5GHZ ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_RF_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int BWN_RF_READ (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  BWN_RF_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int,int) ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_tx_cal_radio_setup_rev19 (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_tx_cal_radio_setup_rev7 (struct bwn_mac*) ; 

__attribute__((used)) static void bwn_nphy_tx_cal_radio_setup(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;
	uint16_t *save = nphy->tx_rx_cal_radio_saveregs;
	uint16_t tmp;
	uint8_t offset, i;

	if (phy->rev >= 19) {
		bwn_nphy_tx_cal_radio_setup_rev19(mac);
	} else if (phy->rev >= 7) {
		bwn_nphy_tx_cal_radio_setup_rev7(mac);
	} else if (phy->rev >= 3) {
	    for (i = 0; i < 2; i++) {
		tmp = (i == 0) ? 0x2000 : 0x3000;
		offset = i * 11;

		save[offset + 0] = BWN_RF_READ(mac, B2055_CAL_RVARCTL);
		save[offset + 1] = BWN_RF_READ(mac, B2055_CAL_LPOCTL);
		save[offset + 2] = BWN_RF_READ(mac, B2055_CAL_TS);
		save[offset + 3] = BWN_RF_READ(mac, B2055_CAL_RCCALRTS);
		save[offset + 4] = BWN_RF_READ(mac, B2055_CAL_RCALRTS);
		save[offset + 5] = BWN_RF_READ(mac, B2055_PADDRV);
		save[offset + 6] = BWN_RF_READ(mac, B2055_XOCTL1);
		save[offset + 7] = BWN_RF_READ(mac, B2055_XOCTL2);
		save[offset + 8] = BWN_RF_READ(mac, B2055_XOREGUL);
		save[offset + 9] = BWN_RF_READ(mac, B2055_XOMISC);
		save[offset + 10] = BWN_RF_READ(mac, B2055_PLL_LFC1);

		if (bwn_current_band(mac) == BWN_BAND_5G) {
			BWN_RF_WRITE(mac, tmp | B2055_CAL_RVARCTL, 0x0A);
			BWN_RF_WRITE(mac, tmp | B2055_CAL_LPOCTL, 0x40);
			BWN_RF_WRITE(mac, tmp | B2055_CAL_TS, 0x55);
			BWN_RF_WRITE(mac, tmp | B2055_CAL_RCCALRTS, 0);
			BWN_RF_WRITE(mac, tmp | B2055_CAL_RCALRTS, 0);
			if (nphy->ipa5g_on) {
				BWN_RF_WRITE(mac, tmp | B2055_PADDRV, 4);
				BWN_RF_WRITE(mac, tmp | B2055_XOCTL1, 1);
			} else {
				BWN_RF_WRITE(mac, tmp | B2055_PADDRV, 0);
				BWN_RF_WRITE(mac, tmp | B2055_XOCTL1, 0x2F);
			}
			BWN_RF_WRITE(mac, tmp | B2055_XOCTL2, 0);
		} else {
			BWN_RF_WRITE(mac, tmp | B2055_CAL_RVARCTL, 0x06);
			BWN_RF_WRITE(mac, tmp | B2055_CAL_LPOCTL, 0x40);
			BWN_RF_WRITE(mac, tmp | B2055_CAL_TS, 0x55);
			BWN_RF_WRITE(mac, tmp | B2055_CAL_RCCALRTS, 0);
			BWN_RF_WRITE(mac, tmp | B2055_CAL_RCALRTS, 0);
			BWN_RF_WRITE(mac, tmp | B2055_XOCTL1, 0);
			if (nphy->ipa2g_on) {
				BWN_RF_WRITE(mac, tmp | B2055_PADDRV, 6);
				BWN_RF_WRITE(mac, tmp | B2055_XOCTL2,
					(mac->mac_phy.rev < 5) ? 0x11 : 0x01);
			} else {
				BWN_RF_WRITE(mac, tmp | B2055_PADDRV, 0);
				BWN_RF_WRITE(mac, tmp | B2055_XOCTL2, 0);
			}
		}
		BWN_RF_WRITE(mac, tmp | B2055_XOREGUL, 0);
		BWN_RF_WRITE(mac, tmp | B2055_XOMISC, 0);
		BWN_RF_WRITE(mac, tmp | B2055_PLL_LFC1, 0);
	    }
	} else {
		save[0] = BWN_RF_READ(mac, B2055_C1_TX_RF_IQCAL1);
		BWN_RF_WRITE(mac, B2055_C1_TX_RF_IQCAL1, 0x29);

		save[1] = BWN_RF_READ(mac, B2055_C1_TX_RF_IQCAL2);
		BWN_RF_WRITE(mac, B2055_C1_TX_RF_IQCAL2, 0x54);

		save[2] = BWN_RF_READ(mac, B2055_C2_TX_RF_IQCAL1);
		BWN_RF_WRITE(mac, B2055_C2_TX_RF_IQCAL1, 0x29);

		save[3] = BWN_RF_READ(mac, B2055_C2_TX_RF_IQCAL2);
		BWN_RF_WRITE(mac, B2055_C2_TX_RF_IQCAL2, 0x54);

		save[3] = BWN_RF_READ(mac, B2055_C1_PWRDET_RXTX);
		save[4] = BWN_RF_READ(mac, B2055_C2_PWRDET_RXTX);

		if (!(BWN_PHY_READ(mac, BWN_NPHY_BANDCTL) &
		    BWN_NPHY_BANDCTL_5GHZ)) {
			BWN_RF_WRITE(mac, B2055_C1_PWRDET_RXTX, 0x04);
			BWN_RF_WRITE(mac, B2055_C2_PWRDET_RXTX, 0x04);
		} else {
			BWN_RF_WRITE(mac, B2055_C1_PWRDET_RXTX, 0x20);
			BWN_RF_WRITE(mac, B2055_C2_PWRDET_RXTX, 0x20);
		}

		if (mac->mac_phy.rev < 2) {
			BWN_RF_SET(mac, B2055_C1_TX_BB_MXGM, 0x20);
			BWN_RF_SET(mac, B2055_C2_TX_BB_MXGM, 0x20);
		} else {
			BWN_RF_MASK(mac, B2055_C1_TX_BB_MXGM, ~0x20);
			BWN_RF_MASK(mac, B2055_C2_TX_BB_MXGM, ~0x20);
		}
	}
}