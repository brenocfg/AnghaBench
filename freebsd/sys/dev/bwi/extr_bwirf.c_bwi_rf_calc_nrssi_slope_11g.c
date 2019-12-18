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
struct bwi_softc {int dummy; } ;
struct bwi_rf {int rf_rev; int rf_nrssi_slope; int* rf_nrssi; int /*<<< orphan*/  rf_curchan; } ;
struct bwi_phy {int phy_rev; int phy_version; } ;
struct bwi_mac {struct bwi_rf mac_rf; struct bwi_phy mac_phy; struct bwi_softc* mac_sc; } ;
struct bwi_gains {int tbl_gain1; int tbl_gain2; int phy_gain; } ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  gains ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_BBP_ATTEN ; 
 int /*<<< orphan*/  BWI_RF_ANTDIV ; 
 int /*<<< orphan*/  BWI_RF_CHAN_EX ; 
 int CSR_READ_2 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_SETBITS_2 (struct bwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct bwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PHY_CLRBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  PHY_FILT_SETBITS (struct bwi_mac*,int,int,int) ; 
 int PHY_READ (struct bwi_mac*,int const) ; 
 int /*<<< orphan*/  PHY_SETBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct bwi_mac*,int const,int) ; 
 int /*<<< orphan*/  RF_CLRBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  RF_FILT_SETBITS (struct bwi_mac*,int,int,int) ; 
 int RF_READ (struct bwi_mac*,int const) ; 
 int /*<<< orphan*/  RF_SETBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  RF_WRITE (struct bwi_mac*,int const,int) ; 
 int SAVE_PHY3_MAX ; 
 int SAVE_PHY_COMM_MAX ; 
 int SAVE_RF_MAX ; 
 int bwi_nrssi_11g (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_init_sw_nrssi_table (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_set_nrssi_ofs_11g (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_set_nrssi_thr_11g (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_work_around (struct bwi_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_set_gains (struct bwi_mac*,struct bwi_gains*) ; 
 int /*<<< orphan*/  bzero (struct bwi_gains*,int) ; 

__attribute__((used)) static void
bwi_rf_calc_nrssi_slope_11g(struct bwi_mac *mac)
{
#define SAVE_RF_MAX		3
#define SAVE_PHY_COMM_MAX	4
#define SAVE_PHY3_MAX		8

	static const uint16_t save_rf_regs[SAVE_RF_MAX] =
	{ 0x7a, 0x52, 0x43 };
	static const uint16_t save_phy_comm_regs[SAVE_PHY_COMM_MAX] =
	{ 0x15, 0x5a, 0x59, 0x58 };
	static const uint16_t save_phy3_regs[SAVE_PHY3_MAX] = {
		0x002e, 0x002f, 0x080f, 0x0810,
		0x0801, 0x0060, 0x0014, 0x0478
	};

	struct bwi_softc *sc = mac->mac_sc;
	struct bwi_phy *phy = &mac->mac_phy;
	struct bwi_rf *rf = &mac->mac_rf;
	uint16_t save_rf[SAVE_RF_MAX];
	uint16_t save_phy_comm[SAVE_PHY_COMM_MAX];
	uint16_t save_phy3[SAVE_PHY3_MAX];
	uint16_t ant_div, bbp_atten, chan_ex;
	struct bwi_gains gains;
	int16_t nrssi[2];
	int i, phy3_idx = 0;

	if (rf->rf_rev >= 9)
		return;
	else if (rf->rf_rev == 8)
		bwi_rf_set_nrssi_ofs_11g(mac);

	PHY_CLRBITS(mac, 0x429, 0x8000);
	PHY_CLRBITS(mac, 0x802, 0x3);

	/*
	 * Save RF/PHY registers for later restoration
	 */
	ant_div = CSR_READ_2(sc, BWI_RF_ANTDIV);
	CSR_SETBITS_2(sc, BWI_RF_ANTDIV, 0x8000);

	for (i = 0; i < SAVE_RF_MAX; ++i)
		save_rf[i] = RF_READ(mac, save_rf_regs[i]);
	for (i = 0; i < SAVE_PHY_COMM_MAX; ++i)
		save_phy_comm[i] = PHY_READ(mac, save_phy_comm_regs[i]);

	bbp_atten = CSR_READ_2(sc, BWI_BBP_ATTEN);
	chan_ex = CSR_READ_2(sc, BWI_RF_CHAN_EX);

	if (phy->phy_rev >= 3) {
		for (i = 0; i < SAVE_PHY3_MAX; ++i)
			save_phy3[i] = PHY_READ(mac, save_phy3_regs[i]);

		PHY_WRITE(mac, 0x2e, 0);
		PHY_WRITE(mac, 0x810, 0);

		if (phy->phy_rev == 4 || phy->phy_rev == 6 ||
		    phy->phy_rev == 7) {
			PHY_SETBITS(mac, 0x478, 0x100);
			PHY_SETBITS(mac, 0x810, 0x40);
		} else if (phy->phy_rev == 3 || phy->phy_rev == 5) {
			PHY_CLRBITS(mac, 0x810, 0x40);
		}

		PHY_SETBITS(mac, 0x60, 0x40);
		PHY_SETBITS(mac, 0x14, 0x200);
	}

	/*
	 * Calculate nrssi0
	 */
	RF_SETBITS(mac, 0x7a, 0x70);

	bzero(&gains, sizeof(gains));
	gains.tbl_gain1 = 0;
	gains.tbl_gain2 = 8;
	gains.phy_gain = 0;
	bwi_set_gains(mac, &gains);

	RF_CLRBITS(mac, 0x7a, 0xff08);
	if (phy->phy_rev >= 2) {
		PHY_FILT_SETBITS(mac, 0x811, 0xffcf, 0x30);
		PHY_FILT_SETBITS(mac, 0x812, 0xffcf, 0x10);
	}

	RF_SETBITS(mac, 0x7a, 0x80);
	DELAY(20);
	nrssi[0] = bwi_nrssi_11g(mac);

	/*
	 * Calculate nrssi1
	 */
	RF_CLRBITS(mac, 0x7a, 0xff80);
	if (phy->phy_version >= 2)
		PHY_FILT_SETBITS(mac, 0x3, 0xff9f, 0x40);
	CSR_SETBITS_2(sc, BWI_RF_CHAN_EX, 0x2000);

	RF_SETBITS(mac, 0x7a, 0xf);
	PHY_WRITE(mac, 0x15, 0xf330);
	if (phy->phy_rev >= 2) {
		PHY_FILT_SETBITS(mac, 0x812, 0xffcf, 0x20);
		PHY_FILT_SETBITS(mac, 0x811, 0xffcf, 0x20);
	}

	bzero(&gains, sizeof(gains));
	gains.tbl_gain1 = 3;
	gains.tbl_gain2 = 0;
	gains.phy_gain = 1;
	bwi_set_gains(mac, &gains);

	if (rf->rf_rev == 8) {
		RF_WRITE(mac, 0x43, 0x1f);
	} else {
		RF_FILT_SETBITS(mac, 0x52, 0xff0f, 0x60);
		RF_FILT_SETBITS(mac, 0x43, 0xfff0, 0x9);
	}
	PHY_WRITE(mac, 0x5a, 0x480);
	PHY_WRITE(mac, 0x59, 0x810);
	PHY_WRITE(mac, 0x58, 0xd);
	DELAY(20);

	nrssi[1] = bwi_nrssi_11g(mac);

	/*
	 * Install calculated narrow RSSI values
	 */
	if (nrssi[1] == nrssi[0])
		rf->rf_nrssi_slope = 0x10000;
	else
		rf->rf_nrssi_slope = 0x400000 / (nrssi[0] - nrssi[1]);
	if (nrssi[0] >= -4) {
		rf->rf_nrssi[0] = nrssi[1];
		rf->rf_nrssi[1] = nrssi[0];
	}

	/*
	 * Restore saved RF/PHY registers
	 */
	if (phy->phy_rev >= 3) {
		for (phy3_idx = 0; phy3_idx < 4; ++phy3_idx) {
			PHY_WRITE(mac, save_phy3_regs[phy3_idx],
				  save_phy3[phy3_idx]);
		}
	}
	if (phy->phy_rev >= 2) {
		PHY_CLRBITS(mac, 0x812, 0x30);
		PHY_CLRBITS(mac, 0x811, 0x30);
	}

	for (i = 0; i < SAVE_RF_MAX; ++i)
		RF_WRITE(mac, save_rf_regs[i], save_rf[i]);

	CSR_WRITE_2(sc, BWI_RF_ANTDIV, ant_div);
	CSR_WRITE_2(sc, BWI_BBP_ATTEN, bbp_atten);
	CSR_WRITE_2(sc, BWI_RF_CHAN_EX, chan_ex);

	for (i = 0; i < SAVE_PHY_COMM_MAX; ++i)
		PHY_WRITE(mac, save_phy_comm_regs[i], save_phy_comm[i]);

	bwi_rf_work_around(mac, rf->rf_curchan);
	PHY_SETBITS(mac, 0x802, 0x3);
	bwi_set_gains(mac, NULL);
	PHY_SETBITS(mac, 0x429, 0x8000);

	if (phy->phy_rev >= 3) {
		for (; phy3_idx < SAVE_PHY3_MAX; ++phy3_idx) {
			PHY_WRITE(mac, save_phy3_regs[phy3_idx],
				  save_phy3[phy3_idx]);
		}
	}

	bwi_rf_init_sw_nrssi_table(mac);
	bwi_rf_set_nrssi_thr_11g(mac);

#undef SAVE_RF_MAX
#undef SAVE_PHY_COMM_MAX
#undef SAVE_PHY3_MAX
}