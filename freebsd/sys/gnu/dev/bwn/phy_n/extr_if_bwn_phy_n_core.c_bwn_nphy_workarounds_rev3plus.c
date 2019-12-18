#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int board_flags2; } ;
struct bwn_softc {TYPE_1__ sc_board_info; int /*<<< orphan*/  sc_dev; } ;
struct bwn_phy_n {int hw_phyrxchain; int hw_phytxchain; } ;
struct TYPE_4__ {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {TYPE_2__ mac_phy; struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int B2056_RX0 ; 
 int B2056_RX1 ; 
 int B2056_RX_MIXA_BIAS_AUX ; 
 int B2056_RX_MIXA_BIAS_MAIN ; 
 int B2056_RX_MIXA_CMFB_IDAC ; 
 int B2056_RX_MIXA_LOB_BIAS ; 
 int B2056_RX_MIXA_MAST_BIAS ; 
 int B2056_RX_MIXG_CMFB_IDAC ; 
 int B2056_TX0 ; 
 int B2056_TX1 ; 
 int B2056_TX_GMBB_IDAC ; 
 int BHND_BFL2_APLL_WAR ; 
 int BHND_BFL2_GPLL_WAR2 ; 
 int BHND_BFL2_SINGLEANT_CCK ; 
 char* BHND_NVAR_PDETRANGE2G ; 
 char* BHND_NVAR_PDETRANGE5G ; 
 scalar_t__ BWN_BAND_2G ; 
 scalar_t__ BWN_BAND_5G ; 
 int /*<<< orphan*/  BWN_ERRPRINTF (struct bwn_softc*,char*,char const*,int) ; 
 int /*<<< orphan*/  BWN_NPHY_ED_CRS20LASSERTTHRESH0 ; 
 int /*<<< orphan*/  BWN_NPHY_ED_CRS20LASSERTTHRESH1 ; 
 int /*<<< orphan*/  BWN_NPHY_ED_CRS20LDEASSERTTHRESH0 ; 
 int /*<<< orphan*/  BWN_NPHY_ED_CRS20LDEASSERTTHRESH1 ; 
 int /*<<< orphan*/  BWN_NPHY_ED_CRS20UASSERTTHRESH0 ; 
 int /*<<< orphan*/  BWN_NPHY_ED_CRS20UASSERTTHRESH1 ; 
 int /*<<< orphan*/  BWN_NPHY_ED_CRS20UDEASSERTTHRESH0 ; 
 int /*<<< orphan*/  BWN_NPHY_ED_CRS20UDEASSERTTHRESH1 ; 
 int /*<<< orphan*/  BWN_NPHY_ED_CRS40ASSERTTHRESH0 ; 
 int /*<<< orphan*/  BWN_NPHY_ED_CRS40ASSERTTHRESH1 ; 
 int /*<<< orphan*/  BWN_NPHY_ED_CRS40DEASSERTTHRESH0 ; 
 int /*<<< orphan*/  BWN_NPHY_ED_CRS40DEASSERTTHRESH1 ; 
 int /*<<< orphan*/  BWN_NPHY_ENDROP_TLEN ; 
 int /*<<< orphan*/  BWN_NPHY_FORCEFRONT0 ; 
 int /*<<< orphan*/  BWN_NPHY_FORCEFRONT1 ; 
 int /*<<< orphan*/  BWN_NPHY_PHASETR_A0 ; 
 int /*<<< orphan*/  BWN_NPHY_PHASETR_A1 ; 
 int /*<<< orphan*/  BWN_NPHY_PHASETR_A2 ; 
 int /*<<< orphan*/  BWN_NPHY_PHASETR_B0 ; 
 int /*<<< orphan*/  BWN_NPHY_PHASETR_B1 ; 
 int /*<<< orphan*/  BWN_NPHY_PHASETR_B2 ; 
 int /*<<< orphan*/  BWN_NPHY_REV3_C1_CLIP_LOGAIN_B ; 
 int /*<<< orphan*/  BWN_NPHY_REV3_C2_CLIP_LOGAIN_B ; 
 int /*<<< orphan*/  BWN_NPHY_SGILTRNOFFSET ; 
 int /*<<< orphan*/  BWN_NTAB16 (int,int) ; 
 int /*<<< orphan*/  BWN_NTAB32 (int,int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int,int) ; 
 int bhnd_nvram_getvar_uint8 (int /*<<< orphan*/ ,char const*,int*) ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_is_40mhz (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_gain_ctl_workarounds (struct bwn_mac*) ; 
 scalar_t__ bwn_nphy_ipa (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_set_rf_sequence (struct bwn_mac*,int,int*,int*,int /*<<< orphan*/ ) ; 
 int bwn_ntab_read (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_ntab_write (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_ntab_write_bulk (struct bwn_mac*,int /*<<< orphan*/ ,int,int*) ; 
 size_t min (int,int) ; 
 int /*<<< orphan*/  nitems (int*) ; 

__attribute__((used)) static int bwn_nphy_workarounds_rev3plus(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;

	/* TX to RX */
	uint8_t tx2rx_events[7] = { 0x4, 0x3, 0x5, 0x2, 0x1, 0x8, 0x1F };
	uint8_t tx2rx_delays[7] = { 8, 4, 4, 4, 4, 6, 1 };
	/* RX to TX */
	uint8_t rx2tx_events_ipa[9] = { 0x0, 0x1, 0x2, 0x8, 0x5, 0x6, 0xF, 0x3,
					0x1F };
	uint8_t rx2tx_delays_ipa[9] = { 8, 6, 6, 4, 4, 16, 43, 1, 1 };
	uint8_t rx2tx_events[9] = { 0x0, 0x1, 0x2, 0x8, 0x5, 0x6, 0x3, 0x4, 0x1F };
	uint8_t rx2tx_delays[9] = { 8, 6, 6, 4, 4, 18, 42, 1, 1 };

	uint16_t vmids[5][4] = {
		{ 0xa2, 0xb4, 0xb4, 0x89, }, /* 0 */
		{ 0xb4, 0xb4, 0xb4, 0x24, }, /* 1 */
		{ 0xa2, 0xb4, 0xb4, 0x74, }, /* 2 */
		{ 0xa2, 0xb4, 0xb4, 0x270, }, /* 3 */
		{ 0xa2, 0xb4, 0xb4, 0x00, }, /* 4 and 5 */
	};
	uint16_t gains[5][4] = {
		{ 0x02, 0x02, 0x02, 0x00, }, /* 0 */
		{ 0x02, 0x02, 0x02, 0x02, }, /* 1 */
		{ 0x02, 0x02, 0x02, 0x04, }, /* 2 */
		{ 0x02, 0x02, 0x02, 0x00, }, /* 3 */
		{ 0x02, 0x02, 0x02, 0x00, }, /* 4 and 5 */
	};
	uint16_t *vmid, *gain;

	const char *pdet_range_var;
	uint8_t pdet_range;
	uint16_t tmp16;
	uint32_t tmp32;
	int error;

	BWN_PHY_WRITE(mac, BWN_NPHY_FORCEFRONT0, 0x1f8);
	BWN_PHY_WRITE(mac, BWN_NPHY_FORCEFRONT1, 0x1f8);

	tmp32 = bwn_ntab_read(mac, BWN_NTAB32(30, 0));
	tmp32 &= 0xffffff;
	bwn_ntab_write(mac, BWN_NTAB32(30, 0), tmp32);

	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_A0, 0x0125);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_A1, 0x01B3);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_A2, 0x0105);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_B0, 0x016E);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_B1, 0x00CD);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_B2, 0x0020);

	BWN_PHY_WRITE(mac, BWN_NPHY_REV3_C1_CLIP_LOGAIN_B, 0x000C);
	BWN_PHY_WRITE(mac, BWN_NPHY_REV3_C2_CLIP_LOGAIN_B, 0x000C);

	/* TX to RX */
	bwn_nphy_set_rf_sequence(mac, 1, tx2rx_events, tx2rx_delays,
				 nitems(tx2rx_events));

	/* RX to TX */
	if (bwn_nphy_ipa(mac))
		bwn_nphy_set_rf_sequence(mac, 0, rx2tx_events_ipa,
				rx2tx_delays_ipa, nitems(rx2tx_events_ipa));
	if (nphy->hw_phyrxchain != 3 &&
	    nphy->hw_phyrxchain != nphy->hw_phytxchain) {
		if (bwn_nphy_ipa(mac)) {
			rx2tx_delays[5] = 59;
			rx2tx_delays[6] = 1;
			rx2tx_events[7] = 0x1F;
		}
		bwn_nphy_set_rf_sequence(mac, 0, rx2tx_events, rx2tx_delays,
					 nitems(rx2tx_events));
	}

	tmp16 = (bwn_current_band(mac) == BWN_BAND_2G) ?
		0x2 : 0x9C40;
	BWN_PHY_WRITE(mac, BWN_NPHY_ENDROP_TLEN, tmp16);

	BWN_PHY_SETMASK(mac, BWN_NPHY_SGILTRNOFFSET, 0xF0FF, 0x0700);

	if (!bwn_is_40mhz(mac)) {
		bwn_ntab_write(mac, BWN_NTAB32(16, 3), 0x18D);
		bwn_ntab_write(mac, BWN_NTAB32(16, 127), 0x18D);
	} else {
		bwn_ntab_write(mac, BWN_NTAB32(16, 3), 0x14D);
		bwn_ntab_write(mac, BWN_NTAB32(16, 127), 0x14D);
	}

	bwn_nphy_gain_ctl_workarounds(mac);

	bwn_ntab_write(mac, BWN_NTAB16(8, 0), 2);
	bwn_ntab_write(mac, BWN_NTAB16(8, 16), 2);

	if (bwn_current_band(mac) == BWN_BAND_2G)
		pdet_range_var = BHND_NVAR_PDETRANGE2G;
	else
		pdet_range_var = BHND_NVAR_PDETRANGE5G;

	error = bhnd_nvram_getvar_uint8(sc->sc_dev, pdet_range_var,
	    &pdet_range);
	if (error) {
		BWN_ERRPRINTF(mac->mac_sc, "Error reading PDet range %s from "
		    "NVRAM: %d\n", pdet_range_var, error);
		return (error);
	}

	/* uint16_t min() */
	vmid = vmids[min(pdet_range, 4)];
	gain = gains[min(pdet_range, 4)];
	switch (pdet_range) {
	case 3:
		if (!(mac->mac_phy.rev >= 4 &&
		      bwn_current_band(mac) == BWN_BAND_2G))
			break;
		/* FALL THROUGH */
	case 0:
	case 1:
		bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x08), 4, vmid);
		bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x18), 4, vmid);
		bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x0c), 4, gain);
		bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x1c), 4, gain);
		break;
	case 2:
		if (mac->mac_phy.rev >= 6) {
			if (bwn_current_band(mac) == BWN_BAND_2G)
				vmid[3] = 0x94;
			else
				vmid[3] = 0x8e;
			gain[3] = 3;
		} else if (mac->mac_phy.rev == 5) {
			vmid[3] = 0x84;
			gain[3] = 2;
		}
		bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x08), 4, vmid);
		bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x18), 4, vmid);
		bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x0c), 4, gain);
		bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x1c), 4, gain);
		break;
	case 4:
	case 5:
		if (bwn_current_band(mac) != BWN_BAND_2G) {
			if (pdet_range == 4) {
				vmid[3] = 0x8e;
				tmp16 = 0x96;
				gain[3] = 0x2;
			} else {
				vmid[3] = 0x89;
				tmp16 = 0x89;
				gain[3] = 0;
			}
		} else {
			if (pdet_range == 4) {
				vmid[3] = 0x89;
				tmp16 = 0x8b;
				gain[3] = 0x2;
			} else {
				vmid[3] = 0x74;
				tmp16 = 0x70;
				gain[3] = 0;
			}
		}
		bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x08), 4, vmid);
		bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x0c), 4, gain);
		vmid[3] = tmp16;
		bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x18), 4, vmid);
		bwn_ntab_write_bulk(mac, BWN_NTAB16(8, 0x1c), 4, gain);
		break;
	}

	BWN_RF_WRITE(mac, B2056_RX0 | B2056_RX_MIXA_MAST_BIAS, 0x00);
	BWN_RF_WRITE(mac, B2056_RX1 | B2056_RX_MIXA_MAST_BIAS, 0x00);
	BWN_RF_WRITE(mac, B2056_RX0 | B2056_RX_MIXA_BIAS_MAIN, 0x06);
	BWN_RF_WRITE(mac, B2056_RX1 | B2056_RX_MIXA_BIAS_MAIN, 0x06);
	BWN_RF_WRITE(mac, B2056_RX0 | B2056_RX_MIXA_BIAS_AUX, 0x07);
	BWN_RF_WRITE(mac, B2056_RX1 | B2056_RX_MIXA_BIAS_AUX, 0x07);
	BWN_RF_WRITE(mac, B2056_RX0 | B2056_RX_MIXA_LOB_BIAS, 0x88);
	BWN_RF_WRITE(mac, B2056_RX1 | B2056_RX_MIXA_LOB_BIAS, 0x88);
	BWN_RF_WRITE(mac, B2056_RX0 | B2056_RX_MIXA_CMFB_IDAC, 0x00);
	BWN_RF_WRITE(mac, B2056_RX1 | B2056_RX_MIXA_CMFB_IDAC, 0x00);
	BWN_RF_WRITE(mac, B2056_RX0 | B2056_RX_MIXG_CMFB_IDAC, 0x00);
	BWN_RF_WRITE(mac, B2056_RX1 | B2056_RX_MIXG_CMFB_IDAC, 0x00);

	/* N PHY WAR TX Chain Update with hw_phytxchain as argument */

	if ((sc->sc_board_info.board_flags2 & BHND_BFL2_APLL_WAR &&
	     bwn_current_band(mac) == BWN_BAND_5G) ||
	    (sc->sc_board_info.board_flags2 & BHND_BFL2_GPLL_WAR2 &&
	     bwn_current_band(mac) == BWN_BAND_2G))
		tmp32 = 0x00088888;
	else
		tmp32 = 0x88888888;
	bwn_ntab_write(mac, BWN_NTAB32(30, 1), tmp32);
	bwn_ntab_write(mac, BWN_NTAB32(30, 2), tmp32);
	bwn_ntab_write(mac, BWN_NTAB32(30, 3), tmp32);

	if (mac->mac_phy.rev == 4 &&
	    bwn_current_band(mac) == BWN_BAND_5G) {
		BWN_RF_WRITE(mac, B2056_TX0 | B2056_TX_GMBB_IDAC,
				0x70);
		BWN_RF_WRITE(mac, B2056_TX1 | B2056_TX_GMBB_IDAC,
				0x70);
	}

	/* Dropped probably-always-true condition */
	BWN_PHY_WRITE(mac, BWN_NPHY_ED_CRS40ASSERTTHRESH0, 0x03eb);
	BWN_PHY_WRITE(mac, BWN_NPHY_ED_CRS40ASSERTTHRESH1, 0x03eb);
	BWN_PHY_WRITE(mac, BWN_NPHY_ED_CRS40DEASSERTTHRESH0, 0x0341);
	BWN_PHY_WRITE(mac, BWN_NPHY_ED_CRS40DEASSERTTHRESH1, 0x0341);
	BWN_PHY_WRITE(mac, BWN_NPHY_ED_CRS20LASSERTTHRESH0, 0x042b);
	BWN_PHY_WRITE(mac, BWN_NPHY_ED_CRS20LASSERTTHRESH1, 0x042b);
	BWN_PHY_WRITE(mac, BWN_NPHY_ED_CRS20LDEASSERTTHRESH0, 0x0381);
	BWN_PHY_WRITE(mac, BWN_NPHY_ED_CRS20LDEASSERTTHRESH1, 0x0381);
	BWN_PHY_WRITE(mac, BWN_NPHY_ED_CRS20UASSERTTHRESH0, 0x042b);
	BWN_PHY_WRITE(mac, BWN_NPHY_ED_CRS20UASSERTTHRESH1, 0x042b);
	BWN_PHY_WRITE(mac, BWN_NPHY_ED_CRS20UDEASSERTTHRESH0, 0x0381);
	BWN_PHY_WRITE(mac, BWN_NPHY_ED_CRS20UDEASSERTTHRESH1, 0x0381);

	if (mac->mac_phy.rev >= 6 && sc->sc_board_info.board_flags2 & BHND_BFL2_SINGLEANT_CCK)
		; /* TODO: 0x0080000000000000 HF */

	return (0);
}