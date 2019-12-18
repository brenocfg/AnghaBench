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
typedef  int uint16_t ;
struct bwn_phy_n {int lpf_bw_overrode_for_sample_play; int bb_mult_save; } ;
struct bwn_phy {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {int /*<<< orphan*/  mac_sc; struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_ERRPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BWN_NPHY_IQLOCAL_CMDGCTL ; 
 int /*<<< orphan*/  BWN_NPHY_REV7_RF_CTL_OVER3 ; 
 int /*<<< orphan*/  BWN_NPHY_REV7_RF_CTL_OVER4 ; 
 int /*<<< orphan*/  BWN_NPHY_RFSEQMODE ; 
 int BWN_NPHY_RFSEQMODE_CAOVER ; 
 int /*<<< orphan*/  BWN_NPHY_RFSEQST ; 
 int /*<<< orphan*/  BWN_NPHY_SAMP_CMD ; 
 int /*<<< orphan*/  BWN_NPHY_SAMP_DEPCNT ; 
 int /*<<< orphan*/  BWN_NPHY_SAMP_LOOPCNT ; 
 int /*<<< orphan*/  BWN_NPHY_SAMP_WAITCNT ; 
 int /*<<< orphan*/  BWN_NTAB16 (int,int) ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  bwn_is_40mhz (struct bwn_mac*) ; 
 int bwn_nphy_read_lpf_ctl (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_nphy_rf_ctl_override_rev19 (struct bwn_mac*,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bwn_nphy_rf_ctl_override_rev7 (struct bwn_mac*,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bwn_nphy_stay_in_carrier_search (struct bwn_mac*,int) ; 
 int bwn_ntab_read (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_ntab_write (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bwn_nphy_run_samples(struct bwn_mac *mac, uint16_t samps, uint16_t loops,
				 uint16_t wait, bool iqmode, bool dac_test,
				 bool modify_bbmult)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;
	int i;
	uint16_t seq_mode;
	uint32_t tmp;

	bwn_nphy_stay_in_carrier_search(mac, true);

	if (phy->rev >= 7) {
		bool lpf_bw3, lpf_bw4;

		lpf_bw3 = BWN_PHY_READ(mac, BWN_NPHY_REV7_RF_CTL_OVER3) & 0x80;
		lpf_bw4 = BWN_PHY_READ(mac, BWN_NPHY_REV7_RF_CTL_OVER4) & 0x80;

		if (lpf_bw3 || lpf_bw4) {
			/* TODO */
		} else {
			uint16_t value = bwn_nphy_read_lpf_ctl(mac, 0);
			if (phy->rev >= 19)
				bwn_nphy_rf_ctl_override_rev19(mac, 0x80, value,
							       0, false, 1);
			else
				bwn_nphy_rf_ctl_override_rev7(mac, 0x80, value,
							      0, false, 1);
			nphy->lpf_bw_overrode_for_sample_play = true;
		}
	}

	if ((nphy->bb_mult_save & 0x80000000) == 0) {
		tmp = bwn_ntab_read(mac, BWN_NTAB16(15, 87));
		nphy->bb_mult_save = (tmp & 0xFFFF) | 0x80000000;
	}

	if (modify_bbmult) {
		tmp = !bwn_is_40mhz(mac) ? 0x6464 : 0x4747;
		bwn_ntab_write(mac, BWN_NTAB16(15, 87), tmp);
	}

	BWN_PHY_WRITE(mac, BWN_NPHY_SAMP_DEPCNT, (samps - 1));

	if (loops != 0xFFFF)
		BWN_PHY_WRITE(mac, BWN_NPHY_SAMP_LOOPCNT, (loops - 1));
	else
		BWN_PHY_WRITE(mac, BWN_NPHY_SAMP_LOOPCNT, loops);

	BWN_PHY_WRITE(mac, BWN_NPHY_SAMP_WAITCNT, wait);

	seq_mode = BWN_PHY_READ(mac, BWN_NPHY_RFSEQMODE);

	BWN_PHY_SET(mac, BWN_NPHY_RFSEQMODE, BWN_NPHY_RFSEQMODE_CAOVER);
	if (iqmode) {
		BWN_PHY_MASK(mac, BWN_NPHY_IQLOCAL_CMDGCTL, 0x7FFF);
		BWN_PHY_SET(mac, BWN_NPHY_IQLOCAL_CMDGCTL, 0x8000);
	} else {
		tmp = dac_test ? 5 : 1;
		BWN_PHY_WRITE(mac, BWN_NPHY_SAMP_CMD, tmp);
	}
	for (i = 0; i < 100; i++) {
		if (!(BWN_PHY_READ(mac, BWN_NPHY_RFSEQST) & 1)) {
			i = 0;
			break;
		}
		DELAY(10);
	}
	if (i)
		BWN_ERRPRINTF(mac->mac_sc, "run samples timeout\n");

	BWN_PHY_WRITE(mac, BWN_NPHY_RFSEQMODE, seq_mode);

	bwn_nphy_stay_in_carrier_search(mac, false);
}