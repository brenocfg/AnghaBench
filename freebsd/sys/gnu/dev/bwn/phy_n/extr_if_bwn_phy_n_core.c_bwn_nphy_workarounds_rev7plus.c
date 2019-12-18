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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int board_flags2; scalar_t__ board_srom_rev; } ;
struct bwn_softc {TYPE_1__ sc_board_info; } ;
struct bwn_phy {int rev; int rf_rev; } ;
struct bwn_mac {struct bwn_phy mac_phy; struct bwn_softc* mac_sc; } ;
typedef  int int16_t ;

/* Variables and functions */
 int BHND_BFL2_IPALVLSHIFT_3P3 ; 
 scalar_t__ BWN_BAND_2G ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_C1 ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_C2 ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_OVER ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_OVER1 ; 
 int BWN_NPHY_ENDROP_TLEN ; 
 int /*<<< orphan*/  BWN_NPHY_EPS_OVERRIDEI_0 ; 
 int /*<<< orphan*/  BWN_NPHY_EPS_OVERRIDEI_1 ; 
 int /*<<< orphan*/  BWN_NPHY_FINERX2_CGC ; 
 int BWN_NPHY_FORCEFRONT0 ; 
 int BWN_NPHY_FORCEFRONT1 ; 
 int /*<<< orphan*/  BWN_NPHY_FREQGAIN0 ; 
 int /*<<< orphan*/  BWN_NPHY_FREQGAIN1 ; 
 int /*<<< orphan*/  BWN_NPHY_FREQGAIN2 ; 
 int /*<<< orphan*/  BWN_NPHY_FREQGAIN3 ; 
 int /*<<< orphan*/  BWN_NPHY_FREQGAIN4 ; 
 int /*<<< orphan*/  BWN_NPHY_FREQGAIN5 ; 
 int /*<<< orphan*/  BWN_NPHY_FREQGAIN6 ; 
 int /*<<< orphan*/  BWN_NPHY_FREQGAIN7 ; 
 int BWN_NPHY_PHASETR_A0 ; 
 int BWN_NPHY_PHASETR_A1 ; 
 int BWN_NPHY_PHASETR_A2 ; 
 int BWN_NPHY_PHASETR_B0 ; 
 int BWN_NPHY_PHASETR_B1 ; 
 int BWN_NPHY_PHASETR_B2 ; 
 int /*<<< orphan*/  BWN_NPHY_TXTAILCNT ; 
 int /*<<< orphan*/  BWN_NTAB16 (int,int) ; 
 int /*<<< orphan*/  BWN_NTAB32 (int,int) ; 
 int /*<<< orphan*/  BWN_NTAB8 (int,int) ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int,int) ; 
 int BWN_RF_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_RF_SET (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  R2057_BACKUP1_CORE0 ; 
 int /*<<< orphan*/  R2057_IPA2G_BIAS_FILTER_CORE0 ; 
 int /*<<< orphan*/  R2057_IPA2G_CASCONV_CORE0 ; 
 int /*<<< orphan*/  R2057_IPA2G_IMAIN_CORE0 ; 
 int /*<<< orphan*/  R2057_PAD2G_IDACS_CORE0 ; 
 int /*<<< orphan*/  R2057_PAD2G_TUNE_PUS_CORE0 ; 
 int /*<<< orphan*/  R2057_PAD_BIAS_FILTER_BWS_CORE0 ; 
 int /*<<< orphan*/  R2057_RCCAL_BCAP_VAL ; 
 int /*<<< orphan*/  R2057_RCCAL_SCAP_VAL ; 
 int /*<<< orphan*/  R2057_TXMIX2G_TUNE_BOOST_PU_CORE0 ; 
 int bwn_clamp_val (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 
 int bwn_get_centre_freq (struct bwn_mac*) ; 
 scalar_t__ bwn_is_40mhz (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_gain_ctl_workarounds (struct bwn_mac*) ; 
 scalar_t__ bwn_nphy_ipa (struct bwn_mac*) ; 
 int bwn_nphy_read_lpf_ctl (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_nphy_rf_ctl_override_rev7 (struct bwn_mac*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_nphy_set_rf_sequence (struct bwn_mac*,int,int*,int*,int /*<<< orphan*/ ) ; 
 int bwn_ntab_read (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_ntab_read_bulk (struct bwn_mac*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  bwn_ntab_write (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_ntab_write_bulk (struct bwn_mac*,int /*<<< orphan*/ ,int,int const*) ; 
 int /*<<< orphan*/  nitems (int*) ; 

__attribute__((used)) static int bwn_nphy_workarounds_rev7plus(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct bwn_phy *phy = &mac->mac_phy;

	/* TX to RX */
	uint8_t tx2rx_events[7] = { 4, 3, 5, 2, 1, 8, 31, };
	uint8_t tx2rx_delays[7] = { 8, 4, 4, 4, 4, 6, 1, };
	/* RX to TX */
	uint8_t rx2tx_events_ipa[9] = { 0x0, 0x1, 0x2, 0x8, 0x5, 0x6, 0xF, 0x3,
					0x1F };
	uint8_t rx2tx_delays_ipa[9] = { 8, 6, 6, 4, 4, 16, 43, 1, 1 };

	static const uint16_t ntab7_15e_16e[] = { 0, 0x10f, 0x10f };
	uint8_t ntab7_138_146[] = { 0x11, 0x11 };
	uint8_t ntab7_133[] = { 0x77, 0x11, 0x11 };

	uint16_t lpf_ofdm_20mhz[2], lpf_ofdm_40mhz[2], lpf_11b[2];
	uint16_t bcap_val;
	int16_t bcap_val_11b[2], bcap_val_11n_20[2], bcap_val_11n_40[2];
	uint16_t scap_val;
	int16_t scap_val_11b[2], scap_val_11n_20[2], scap_val_11n_40[2];
	bool rccal_ovrd = false;

	uint16_t bias, conv, filt;

	uint32_t noise_tbl[2];

	uint32_t tmp32;
	uint8_t core;

	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_A0, 0x0125);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_A1, 0x01b3);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_A2, 0x0105);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_B0, 0x016e);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_B1, 0x00cd);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_B2, 0x0020);

	if (phy->rev == 7) {
		BWN_PHY_SET(mac, BWN_NPHY_FINERX2_CGC, 0x10);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN0, 0xFF80, 0x0020);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN0, 0x80FF, 0x2700);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN1, 0xFF80, 0x002E);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN1, 0x80FF, 0x3300);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN2, 0xFF80, 0x0037);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN2, 0x80FF, 0x3A00);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN3, 0xFF80, 0x003C);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN3, 0x80FF, 0x3E00);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN4, 0xFF80, 0x003E);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN4, 0x80FF, 0x3F00);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN5, 0xFF80, 0x0040);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN5, 0x80FF, 0x4000);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN6, 0xFF80, 0x0040);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN6, 0x80FF, 0x4000);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN7, 0xFF80, 0x0040);
		BWN_PHY_SETMASK(mac, BWN_NPHY_FREQGAIN7, 0x80FF, 0x4000);
	}

	if (phy->rev >= 16) {
		BWN_PHY_WRITE(mac, BWN_NPHY_FORCEFRONT0, 0x7ff);
		BWN_PHY_WRITE(mac, BWN_NPHY_FORCEFRONT1, 0x7ff);
	} else if (phy->rev <= 8) {
		BWN_PHY_WRITE(mac, BWN_NPHY_FORCEFRONT0, 0x1B0);
		BWN_PHY_WRITE(mac, BWN_NPHY_FORCEFRONT1, 0x1B0);
	}

	if (phy->rev >= 16)
		BWN_PHY_SETMASK(mac, BWN_NPHY_TXTAILCNT, ~0xFF, 0xa0);
	else if (phy->rev >= 8)
		BWN_PHY_SETMASK(mac, BWN_NPHY_TXTAILCNT, ~0xFF, 0x72);

	bwn_ntab_write(mac, BWN_NTAB16(8, 0x00), 2);
	bwn_ntab_write(mac, BWN_NTAB16(8, 0x10), 2);
	tmp32 = bwn_ntab_read(mac, BWN_NTAB32(30, 0));
	tmp32 &= 0xffffff;
	bwn_ntab_write(mac, BWN_NTAB32(30, 0), tmp32);
	bwn_ntab_write_bulk(mac, BWN_NTAB16(7, 0x15d), 3, ntab7_15e_16e);
	bwn_ntab_write_bulk(mac, BWN_NTAB16(7, 0x16d), 3, ntab7_15e_16e);

	bwn_nphy_set_rf_sequence(mac, 1, tx2rx_events, tx2rx_delays,
				 nitems(tx2rx_events));
	if (bwn_nphy_ipa(mac))
		bwn_nphy_set_rf_sequence(mac, 0, rx2tx_events_ipa,
				rx2tx_delays_ipa, nitems(rx2tx_events_ipa));

	BWN_PHY_SETMASK(mac, BWN_NPHY_EPS_OVERRIDEI_0, 0x3FFF, 0x4000);
	BWN_PHY_SETMASK(mac, BWN_NPHY_EPS_OVERRIDEI_1, 0x3FFF, 0x4000);

	for (core = 0; core < 2; core++) {
		lpf_ofdm_20mhz[core] = bwn_nphy_read_lpf_ctl(mac, 0x154 + core * 0x10);
		lpf_ofdm_40mhz[core] = bwn_nphy_read_lpf_ctl(mac, 0x159 + core * 0x10);
		lpf_11b[core] = bwn_nphy_read_lpf_ctl(mac, 0x152 + core * 0x10);
	}

	bcap_val = BWN_RF_READ(mac, R2057_RCCAL_BCAP_VAL);
	scap_val = BWN_RF_READ(mac, R2057_RCCAL_SCAP_VAL);

	if (bwn_nphy_ipa(mac)) {
		bool ghz2 = bwn_current_band(mac) == BWN_BAND_2G;

		switch (phy->rf_rev) {
		case 5:
			/* Check radio version (to be 0) by PHY rev for now */
			if (phy->rev == 8 && bwn_is_40mhz(mac)) {
				for (core = 0; core < 2; core++) {
					scap_val_11b[core] = scap_val;
					bcap_val_11b[core] = bcap_val;
					scap_val_11n_20[core] = scap_val;
					bcap_val_11n_20[core] = bcap_val;
					scap_val_11n_40[core] = 0xc;
					bcap_val_11n_40[core] = 0xc;
				}

				rccal_ovrd = true;
			}
			if (phy->rev == 9) {
				/* TODO: Radio version 1 (e.g. BCM5357B0) */
			}
			break;
		case 7:
		case 8:
			for (core = 0; core < 2; core++) {
				scap_val_11b[core] = scap_val;
				bcap_val_11b[core] = bcap_val;
				lpf_ofdm_20mhz[core] = 4;
				lpf_11b[core] = 1;
				if (bwn_current_band(mac) == BWN_BAND_2G) {
					scap_val_11n_20[core] = 0xc;
					bcap_val_11n_20[core] = 0xc;
					scap_val_11n_40[core] = 0xa;
					bcap_val_11n_40[core] = 0xa;
				} else {
					scap_val_11n_20[core] = 0x14;
					bcap_val_11n_20[core] = 0x14;
					scap_val_11n_40[core] = 0xf;
					bcap_val_11n_40[core] = 0xf;
				}
			}

			rccal_ovrd = true;
			break;
		case 9:
			for (core = 0; core < 2; core++) {
				bcap_val_11b[core] = bcap_val;
				scap_val_11b[core] = scap_val;
				lpf_11b[core] = 1;

				if (ghz2) {
					bcap_val_11n_20[core] = bcap_val + 13;
					scap_val_11n_20[core] = scap_val + 15;
				} else {
					bcap_val_11n_20[core] = bcap_val + 14;
					scap_val_11n_20[core] = scap_val + 15;
				}
				lpf_ofdm_20mhz[core] = 4;

				if (ghz2) {
					bcap_val_11n_40[core] = bcap_val - 7;
					scap_val_11n_40[core] = scap_val - 5;
				} else {
					bcap_val_11n_40[core] = bcap_val + 2;
					scap_val_11n_40[core] = scap_val + 4;
				}
				lpf_ofdm_40mhz[core] = 4;
			}

			rccal_ovrd = true;
			break;
		case 14:
			for (core = 0; core < 2; core++) {
				bcap_val_11b[core] = bcap_val;
				scap_val_11b[core] = scap_val;
				lpf_11b[core] = 1;
			}

			bcap_val_11n_20[0] = bcap_val + 20;
			scap_val_11n_20[0] = scap_val + 20;
			lpf_ofdm_20mhz[0] = 3;

			bcap_val_11n_20[1] = bcap_val + 16;
			scap_val_11n_20[1] = scap_val + 16;
			lpf_ofdm_20mhz[1] = 3;

			bcap_val_11n_40[0] = bcap_val + 20;
			scap_val_11n_40[0] = scap_val + 20;
			lpf_ofdm_40mhz[0] = 4;

			bcap_val_11n_40[1] = bcap_val + 10;
			scap_val_11n_40[1] = scap_val + 10;
			lpf_ofdm_40mhz[1] = 4;

			rccal_ovrd = true;
			break;
		}
	} else {
		if (phy->rf_rev == 5) {
			for (core = 0; core < 2; core++) {
				lpf_ofdm_20mhz[core] = 1;
				lpf_ofdm_40mhz[core] = 3;
				scap_val_11b[core] = scap_val;
				bcap_val_11b[core] = bcap_val;
				scap_val_11n_20[core] = 0x11;
				scap_val_11n_40[core] = 0x11;
				bcap_val_11n_20[core] = 0x13;
				bcap_val_11n_40[core] = 0x13;
			}

			rccal_ovrd = true;
		}
	}
	if (rccal_ovrd) {
		uint16_t rx2tx_lut_20_11b[2], rx2tx_lut_20_11n[2], rx2tx_lut_40_11n[2];
		uint8_t rx2tx_lut_extra = 1;

		for (core = 0; core < 2; core++) {
			bcap_val_11b[core] = bwn_clamp_val(bcap_val_11b[core], 0, 0x1f);
			scap_val_11b[core] = bwn_clamp_val(scap_val_11b[core], 0, 0x1f);
			bcap_val_11n_20[core] = bwn_clamp_val(bcap_val_11n_20[core], 0, 0x1f);
			scap_val_11n_20[core] = bwn_clamp_val(scap_val_11n_20[core], 0, 0x1f);
			bcap_val_11n_40[core] = bwn_clamp_val(bcap_val_11n_40[core], 0, 0x1f);
			scap_val_11n_40[core] = bwn_clamp_val(scap_val_11n_40[core], 0, 0x1f);

			rx2tx_lut_20_11b[core] = (rx2tx_lut_extra << 13) |
						 (bcap_val_11b[core] << 8) |
						 (scap_val_11b[core] << 3) |
						 lpf_11b[core];
			rx2tx_lut_20_11n[core] = (rx2tx_lut_extra << 13) |
						 (bcap_val_11n_20[core] << 8) |
						 (scap_val_11n_20[core] << 3) |
						 lpf_ofdm_20mhz[core];
			rx2tx_lut_40_11n[core] = (rx2tx_lut_extra << 13) |
						 (bcap_val_11n_40[core] << 8) |
						 (scap_val_11n_40[core] << 3) |
						 lpf_ofdm_40mhz[core];
		}

		for (core = 0; core < 2; core++) {
			bwn_ntab_write(mac, BWN_NTAB16(7, 0x152 + core * 16),
				       rx2tx_lut_20_11b[core]);
			bwn_ntab_write(mac, BWN_NTAB16(7, 0x153 + core * 16),
				       rx2tx_lut_20_11n[core]);
			bwn_ntab_write(mac, BWN_NTAB16(7, 0x154 + core * 16),
				       rx2tx_lut_20_11n[core]);
			bwn_ntab_write(mac, BWN_NTAB16(7, 0x155 + core * 16),
				       rx2tx_lut_40_11n[core]);
			bwn_ntab_write(mac, BWN_NTAB16(7, 0x156 + core * 16),
				       rx2tx_lut_40_11n[core]);
			bwn_ntab_write(mac, BWN_NTAB16(7, 0x157 + core * 16),
				       rx2tx_lut_40_11n[core]);
			bwn_ntab_write(mac, BWN_NTAB16(7, 0x158 + core * 16),
				       rx2tx_lut_40_11n[core]);
			bwn_ntab_write(mac, BWN_NTAB16(7, 0x159 + core * 16),
				       rx2tx_lut_40_11n[core]);
		}
	}

	BWN_PHY_WRITE(mac, 0x32F, 0x3);

	if (phy->rf_rev == 4 || phy->rf_rev == 6)
		bwn_nphy_rf_ctl_override_rev7(mac, 4, 1, 3, false, 0);

	if (phy->rf_rev == 3 || phy->rf_rev == 4 || phy->rf_rev == 6) {
		if (sc->sc_board_info.board_srom_rev &&
		    sc->sc_board_info.board_flags2 & BHND_BFL2_IPALVLSHIFT_3P3) {
			BWN_RF_WRITE(mac, 0x5, 0x05);
			BWN_RF_WRITE(mac, 0x6, 0x30);
			BWN_RF_WRITE(mac, 0x7, 0x00);
			BWN_RF_SET(mac, 0x4f, 0x1);
			BWN_RF_SET(mac, 0xd4, 0x1);
			bias = 0x1f;
			conv = 0x6f;
			filt = 0xaa;
		} else {
			bias = 0x2b;
			conv = 0x7f;
			filt = 0xee;
		}
		if (bwn_current_band(mac) == BWN_BAND_2G) {
			for (core = 0; core < 2; core++) {
				if (core == 0) {
					BWN_RF_WRITE(mac, 0x5F, bias);
					BWN_RF_WRITE(mac, 0x64, conv);
					BWN_RF_WRITE(mac, 0x66, filt);
				} else {
					BWN_RF_WRITE(mac, 0xE8, bias);
					BWN_RF_WRITE(mac, 0xE9, conv);
					BWN_RF_WRITE(mac, 0xEB, filt);
				}
			}
		}
	}

	if (bwn_nphy_ipa(mac)) {
		if (bwn_current_band(mac) == BWN_BAND_2G) {
			if (phy->rf_rev == 3 || phy->rf_rev == 4 ||
			    phy->rf_rev == 6) {
				for (core = 0; core < 2; core++) {
					if (core == 0)
						BWN_RF_WRITE(mac, 0x51,
								0x7f);
					else
						BWN_RF_WRITE(mac, 0xd6,
								0x7f);
				}
			}
			switch (phy->rf_rev) {
			case 3:
				for (core = 0; core < 2; core++) {
					if (core == 0) {
						BWN_RF_WRITE(mac, 0x64,
								0x13);
						BWN_RF_WRITE(mac, 0x5F,
								0x1F);
						BWN_RF_WRITE(mac, 0x66,
								0xEE);
						BWN_RF_WRITE(mac, 0x59,
								0x8A);
						BWN_RF_WRITE(mac, 0x80,
								0x3E);
					} else {
						BWN_RF_WRITE(mac, 0x69,
								0x13);
						BWN_RF_WRITE(mac, 0xE8,
								0x1F);
						BWN_RF_WRITE(mac, 0xEB,
								0xEE);
						BWN_RF_WRITE(mac, 0xDE,
								0x8A);
						BWN_RF_WRITE(mac, 0x105,
								0x3E);
					}
				}
				break;
			case 7:
			case 8:
				if (!bwn_is_40mhz(mac)) {
					BWN_RF_WRITE(mac, 0x5F, 0x14);
					BWN_RF_WRITE(mac, 0xE8, 0x12);
				} else {
					BWN_RF_WRITE(mac, 0x5F, 0x16);
					BWN_RF_WRITE(mac, 0xE8, 0x16);
				}
				break;
			case 14:
				for (core = 0; core < 2; core++) {
					int o = core ? 0x85 : 0;

					BWN_RF_WRITE(mac, o + R2057_IPA2G_CASCONV_CORE0, 0x13);
					BWN_RF_WRITE(mac, o + R2057_TXMIX2G_TUNE_BOOST_PU_CORE0, 0x21);
					BWN_RF_WRITE(mac, o + R2057_IPA2G_BIAS_FILTER_CORE0, 0xff);
					BWN_RF_WRITE(mac, o + R2057_PAD2G_IDACS_CORE0, 0x88);
					BWN_RF_WRITE(mac, o + R2057_PAD2G_TUNE_PUS_CORE0, 0x23);
					BWN_RF_WRITE(mac, o + R2057_IPA2G_IMAIN_CORE0, 0x16);
					BWN_RF_WRITE(mac, o + R2057_PAD_BIAS_FILTER_BWS_CORE0, 0x3e);
					BWN_RF_WRITE(mac, o + R2057_BACKUP1_CORE0, 0x10);
				}
				break;
			}
		} else {
			uint16_t freq = bwn_get_centre_freq(mac);
			if ((freq >= 5180 && freq <= 5230) ||
			    (freq >= 5745 && freq <= 5805)) {
				BWN_RF_WRITE(mac, 0x7D, 0xFF);
				BWN_RF_WRITE(mac, 0xFE, 0xFF);
			}
		}
	} else {
		if (phy->rf_rev != 5) {
			for (core = 0; core < 2; core++) {
				if (core == 0) {
					BWN_RF_WRITE(mac, 0x5c, 0x61);
					BWN_RF_WRITE(mac, 0x51, 0x70);
				} else {
					BWN_RF_WRITE(mac, 0xe1, 0x61);
					BWN_RF_WRITE(mac, 0xd6, 0x70);
				}
			}
		}
	}

	if (phy->rf_rev == 4) {
		bwn_ntab_write(mac, BWN_NTAB16(8, 0x05), 0x20);
		bwn_ntab_write(mac, BWN_NTAB16(8, 0x15), 0x20);
		for (core = 0; core < 2; core++) {
			if (core == 0) {
				BWN_RF_WRITE(mac, 0x1a1, 0x00);
				BWN_RF_WRITE(mac, 0x1a2, 0x3f);
				BWN_RF_WRITE(mac, 0x1a6, 0x3f);
			} else {
				BWN_RF_WRITE(mac, 0x1a7, 0x00);
				BWN_RF_WRITE(mac, 0x1ab, 0x3f);
				BWN_RF_WRITE(mac, 0x1ac, 0x3f);
			}
		}
	} else {
		BWN_PHY_SET(mac, BWN_NPHY_AFECTL_C1, 0x4);
		BWN_PHY_SET(mac, BWN_NPHY_AFECTL_OVER1, 0x4);
		BWN_PHY_SET(mac, BWN_NPHY_AFECTL_C2, 0x4);
		BWN_PHY_SET(mac, BWN_NPHY_AFECTL_OVER, 0x4);

		BWN_PHY_MASK(mac, BWN_NPHY_AFECTL_C1, ~0x1);
		BWN_PHY_SET(mac, BWN_NPHY_AFECTL_OVER1, 0x1);
		BWN_PHY_MASK(mac, BWN_NPHY_AFECTL_C2, ~0x1);
		BWN_PHY_SET(mac, BWN_NPHY_AFECTL_OVER, 0x1);
		bwn_ntab_write(mac, BWN_NTAB16(8, 0x05), 0);
		bwn_ntab_write(mac, BWN_NTAB16(8, 0x15), 0);

		BWN_PHY_MASK(mac, BWN_NPHY_AFECTL_C1, ~0x4);
		BWN_PHY_MASK(mac, BWN_NPHY_AFECTL_OVER1, ~0x4);
		BWN_PHY_MASK(mac, BWN_NPHY_AFECTL_C2, ~0x4);
		BWN_PHY_MASK(mac, BWN_NPHY_AFECTL_OVER, ~0x4);
	}

	BWN_PHY_WRITE(mac, BWN_NPHY_ENDROP_TLEN, 0x2);

	bwn_ntab_write(mac, BWN_NTAB32(16, 0x100), 20);
	bwn_ntab_write_bulk(mac, BWN_NTAB8(7, 0x138), 2, ntab7_138_146);
	bwn_ntab_write(mac, BWN_NTAB16(7, 0x141), 0x77);
	bwn_ntab_write_bulk(mac, BWN_NTAB8(7, 0x133), 3, ntab7_133);
	bwn_ntab_write_bulk(mac, BWN_NTAB8(7, 0x146), 2, ntab7_138_146);
	bwn_ntab_write(mac, BWN_NTAB16(7, 0x123), 0x77);
	bwn_ntab_write(mac, BWN_NTAB16(7, 0x12A), 0x77);

	bwn_ntab_read_bulk(mac, BWN_NTAB32(16, 0x02), 1, noise_tbl);
	noise_tbl[1] = bwn_is_40mhz(mac) ? 0x14D : 0x18D;
	bwn_ntab_write_bulk(mac, BWN_NTAB32(16, 0x02), 2, noise_tbl);

	bwn_ntab_read_bulk(mac, BWN_NTAB32(16, 0x7E), 1, noise_tbl);
	noise_tbl[1] = bwn_is_40mhz(mac) ? 0x14D : 0x18D;
	bwn_ntab_write_bulk(mac, BWN_NTAB32(16, 0x7E), 2, noise_tbl);

	bwn_nphy_gain_ctl_workarounds(mac);

	/* TODO
	bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x08), 4,
			    aux_adc_vmid_rev7_core0);
	bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x18), 4,
			    aux_adc_vmid_rev7_core1);
	bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x0C), 4,
			    aux_adc_gain_rev7);
	bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x1C), 4,
			    aux_adc_gain_rev7);
	*/

	return (0);
}