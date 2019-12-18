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
typedef  int uint16_t ;
struct bwn_phy_n {int* tx_rx_cal_radio_saveregs; scalar_t__ use_int_tx_iq_lo_cal; } ;
struct bwn_phy {int rf_rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 scalar_t__ BWN_BAND_5G ; 
 int BWN_RF_READ (struct bwn_mac*,scalar_t__) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,scalar_t__,int) ; 
 scalar_t__ R2057_TX0_IQCAL_IDAC ; 
 scalar_t__ R2057_TX0_IQCAL_VCM_HG ; 
 scalar_t__ R2057_TX0_TSSIA ; 
 scalar_t__ R2057_TX0_TSSIG ; 
 scalar_t__ R2057_TX0_TSSI_MISC1 ; 
 scalar_t__ R2057_TX0_TSSI_VCM ; 
 scalar_t__ R2057_TX0_TX_SSI_MASTER ; 
 scalar_t__ R2057_TX0_TX_SSI_MUX ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 

__attribute__((used)) static void bwn_nphy_tx_cal_radio_setup_rev7(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;
	uint16_t *save = nphy->tx_rx_cal_radio_saveregs;
	int core, off;
	uint16_t r, tmp;

	for (core = 0; core < 2; core++) {
		r = core ? 0x20 : 0;
		off = core * 11;

		save[off + 0] = BWN_RF_READ(mac, r + R2057_TX0_TX_SSI_MASTER);
		save[off + 1] = BWN_RF_READ(mac, r + R2057_TX0_IQCAL_VCM_HG);
		save[off + 2] = BWN_RF_READ(mac, r + R2057_TX0_IQCAL_IDAC);
		save[off + 3] = BWN_RF_READ(mac, r + R2057_TX0_TSSI_VCM);
		save[off + 4] = 0;
		save[off + 5] = BWN_RF_READ(mac, r + R2057_TX0_TX_SSI_MUX);
		if (phy->rf_rev != 5)
			save[off + 6] = BWN_RF_READ(mac, r + R2057_TX0_TSSIA);
		save[off + 7] = BWN_RF_READ(mac, r + R2057_TX0_TSSIG);
		save[off + 8] = BWN_RF_READ(mac, r + R2057_TX0_TSSI_MISC1);

		if (bwn_current_band(mac) == BWN_BAND_5G) {
			BWN_RF_WRITE(mac, r + R2057_TX0_TX_SSI_MASTER, 0xA);
			BWN_RF_WRITE(mac, r + R2057_TX0_IQCAL_VCM_HG, 0x43);
			BWN_RF_WRITE(mac, r + R2057_TX0_IQCAL_IDAC, 0x55);
			BWN_RF_WRITE(mac, r + R2057_TX0_TSSI_VCM, 0);
			BWN_RF_WRITE(mac, r + R2057_TX0_TSSIG, 0);
			if (nphy->use_int_tx_iq_lo_cal) {
				BWN_RF_WRITE(mac, r + R2057_TX0_TX_SSI_MUX, 0x4);
				tmp = true ? 0x31 : 0x21; /* TODO */
				BWN_RF_WRITE(mac, r + R2057_TX0_TSSIA, tmp);
			}
			BWN_RF_WRITE(mac, r + R2057_TX0_TSSI_MISC1, 0x00);
		} else {
			BWN_RF_WRITE(mac, r + R2057_TX0_TX_SSI_MASTER, 0x6);
			BWN_RF_WRITE(mac, r + R2057_TX0_IQCAL_VCM_HG, 0x43);
			BWN_RF_WRITE(mac, r + R2057_TX0_IQCAL_IDAC, 0x55);
			BWN_RF_WRITE(mac, r + R2057_TX0_TSSI_VCM, 0);

			if (phy->rf_rev != 5)
				BWN_RF_WRITE(mac, r + R2057_TX0_TSSIA, 0);
			if (nphy->use_int_tx_iq_lo_cal) {
				BWN_RF_WRITE(mac, r + R2057_TX0_TX_SSI_MUX, 0x6);
				tmp = true ? 0x31 : 0x21; /* TODO */
				BWN_RF_WRITE(mac, r + R2057_TX0_TSSIG, tmp);
			}
			BWN_RF_WRITE(mac, r + R2057_TX0_TSSI_MISC1, 0);
		}
	}
}