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
struct bwn_phy_n {int* tx_rx_cal_phy_saveregs; scalar_t__ use_int_tx_iq_lo_cal; } ;
struct bwn_phy {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 scalar_t__ BWN_BAND_2G ; 
 scalar_t__ BWN_BAND_5G ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_C1 ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_C2 ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_OVER ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_OVER1 ; 
 int /*<<< orphan*/  BWN_NPHY_BBCFG ; 
 int BWN_NPHY_BBCFG_RSTRX ; 
 int /*<<< orphan*/  BWN_NPHY_PAPD_EN0 ; 
 int /*<<< orphan*/  BWN_NPHY_PAPD_EN1 ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_INTC1 ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_INTC2 ; 
 int /*<<< orphan*/  BWN_NTAB16 (int,int) ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  N_INTC_OVERRIDE_PA ; 
 int /*<<< orphan*/  N_INTC_OVERRIDE_TRSW ; 
 int /*<<< orphan*/  R2057_IPA5G_CASCOFFV_PU_CORE0 ; 
 int /*<<< orphan*/  R2057_IPA5G_CASCOFFV_PU_CORE1 ; 
 int /*<<< orphan*/  R2057_OVR_REG0 ; 
 int /*<<< orphan*/  R2057_PAD2G_TUNE_PUS_CORE0 ; 
 int /*<<< orphan*/  R2057_PAD2G_TUNE_PUS_CORE1 ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 
 int bwn_nphy_read_lpf_ctl (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_nphy_rf_ctl_intc_override (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bwn_nphy_rf_ctl_override_rev19 (struct bwn_mac*,int,int,int,int,int) ; 
 int /*<<< orphan*/  bwn_nphy_rf_ctl_override_rev7 (struct bwn_mac*,int,int,int,int,int) ; 
 int bwn_ntab_read (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_ntab_write (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bwn_nphy_tx_cal_phy_setup(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;
	uint16_t *regs = mac->mac_phy.phy_n->tx_rx_cal_phy_saveregs;
	uint16_t tmp;

	regs[0] = BWN_PHY_READ(mac, BWN_NPHY_AFECTL_C1);
	regs[1] = BWN_PHY_READ(mac, BWN_NPHY_AFECTL_C2);
	if (mac->mac_phy.rev >= 3) {
		BWN_PHY_SETMASK(mac, BWN_NPHY_AFECTL_C1, 0xF0FF, 0x0A00);
		BWN_PHY_SETMASK(mac, BWN_NPHY_AFECTL_C2, 0xF0FF, 0x0A00);

		tmp = BWN_PHY_READ(mac, BWN_NPHY_AFECTL_OVER1);
		regs[2] = tmp;
		BWN_PHY_WRITE(mac, BWN_NPHY_AFECTL_OVER1, tmp | 0x0600);

		tmp = BWN_PHY_READ(mac, BWN_NPHY_AFECTL_OVER);
		regs[3] = tmp;
		BWN_PHY_WRITE(mac, BWN_NPHY_AFECTL_OVER, tmp | 0x0600);

		regs[4] = BWN_PHY_READ(mac, BWN_NPHY_BBCFG);
		BWN_PHY_MASK(mac, BWN_NPHY_BBCFG,
			     ~BWN_NPHY_BBCFG_RSTRX & 0xFFFF);

		tmp = bwn_ntab_read(mac, BWN_NTAB16(8, 3));
		regs[5] = tmp;
		bwn_ntab_write(mac, BWN_NTAB16(8, 3), 0);

		tmp = bwn_ntab_read(mac, BWN_NTAB16(8, 19));
		regs[6] = tmp;
		bwn_ntab_write(mac, BWN_NTAB16(8, 19), 0);
		regs[7] = BWN_PHY_READ(mac, BWN_NPHY_RFCTL_INTC1);
		regs[8] = BWN_PHY_READ(mac, BWN_NPHY_RFCTL_INTC2);

		if (!nphy->use_int_tx_iq_lo_cal)
			bwn_nphy_rf_ctl_intc_override(mac, N_INTC_OVERRIDE_PA,
						      1, 3);
		else
			bwn_nphy_rf_ctl_intc_override(mac, N_INTC_OVERRIDE_PA,
						      0, 3);
		bwn_nphy_rf_ctl_intc_override(mac, N_INTC_OVERRIDE_TRSW, 2, 1);
		bwn_nphy_rf_ctl_intc_override(mac, N_INTC_OVERRIDE_TRSW, 8, 2);

		regs[9] = BWN_PHY_READ(mac, BWN_NPHY_PAPD_EN0);
		regs[10] = BWN_PHY_READ(mac, BWN_NPHY_PAPD_EN1);
		BWN_PHY_MASK(mac, BWN_NPHY_PAPD_EN0, ~0x0001);
		BWN_PHY_MASK(mac, BWN_NPHY_PAPD_EN1, ~0x0001);

		tmp = bwn_nphy_read_lpf_ctl(mac, 0);
		if (phy->rev >= 19)
			bwn_nphy_rf_ctl_override_rev19(mac, 0x80, tmp, 0, false,
						       1);
		else if (phy->rev >= 7)
			bwn_nphy_rf_ctl_override_rev7(mac, 0x80, tmp, 0, false,
						      1);

		if (nphy->use_int_tx_iq_lo_cal && true /* FIXME */) {
			if (phy->rev >= 19) {
				bwn_nphy_rf_ctl_override_rev19(mac, 0x8, 0, 0x3,
							       false, 0);
			} else if (phy->rev >= 8) {
				bwn_nphy_rf_ctl_override_rev7(mac, 0x8, 0, 0x3,
							      false, 0);
			} else if (phy->rev == 7) {
				BWN_RF_SETMASK(mac, R2057_OVR_REG0, 1 << 4, 1 << 4);
				if (bwn_current_band(mac) == BWN_BAND_2G) {
					BWN_RF_SETMASK(mac, R2057_PAD2G_TUNE_PUS_CORE0, ~1, 0);
					BWN_RF_SETMASK(mac, R2057_PAD2G_TUNE_PUS_CORE1, ~1, 0);
				} else {
					BWN_RF_SETMASK(mac, R2057_IPA5G_CASCOFFV_PU_CORE0, ~1, 0);
					BWN_RF_SETMASK(mac, R2057_IPA5G_CASCOFFV_PU_CORE1, ~1, 0);
				}
			}
		}
	} else {
		BWN_PHY_SETMASK(mac, BWN_NPHY_AFECTL_C1, 0x0FFF, 0xA000);
		BWN_PHY_SETMASK(mac, BWN_NPHY_AFECTL_C2, 0x0FFF, 0xA000);
		tmp = BWN_PHY_READ(mac, BWN_NPHY_AFECTL_OVER);
		regs[2] = tmp;
		BWN_PHY_WRITE(mac, BWN_NPHY_AFECTL_OVER, tmp | 0x3000);
		tmp = bwn_ntab_read(mac, BWN_NTAB16(8, 2));
		regs[3] = tmp;
		tmp |= 0x2000;
		bwn_ntab_write(mac, BWN_NTAB16(8, 2), tmp);
		tmp = bwn_ntab_read(mac, BWN_NTAB16(8, 18));
		regs[4] = tmp;
		tmp |= 0x2000;
		bwn_ntab_write(mac, BWN_NTAB16(8, 18), tmp);
		regs[5] = BWN_PHY_READ(mac, BWN_NPHY_RFCTL_INTC1);
		regs[6] = BWN_PHY_READ(mac, BWN_NPHY_RFCTL_INTC2);
		if (bwn_current_band(mac) == BWN_BAND_5G)
			tmp = 0x0180;
		else
			tmp = 0x0120;
		BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_INTC1, tmp);
		BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_INTC2, tmp);
	}
}