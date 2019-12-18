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
struct TYPE_2__ {int board_flags2; scalar_t__ board_type; } ;
struct bwn_softc {TYPE_1__ sc_board_info; } ;
struct bwn_phy_n {scalar_t__ band5g_pwrgain; } ;
struct bwn_phy {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {struct bwn_phy mac_phy; struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2055_C1_TX_RF_SPARE ; 
 int /*<<< orphan*/  B2055_C2_TX_RF_SPARE ; 
 int BHND_BFL2_SKWRKFEM_BRD ; 
 scalar_t__ BHND_BOARD_BCM943224M93 ; 
 scalar_t__ BWN_BAND_5G ; 
 int BWN_HF_MLADVW ; 
 int /*<<< orphan*/  BWN_NPHY_CRSCHECK2 ; 
 int /*<<< orphan*/  BWN_NPHY_CRSCHECK3 ; 
 int /*<<< orphan*/  BWN_NPHY_FINERX2_CGC ; 
 int /*<<< orphan*/  BWN_NPHY_FINERX2_CGC_DECGC ; 
 int /*<<< orphan*/  BWN_NPHY_PHASETR_A0 ; 
 int /*<<< orphan*/  BWN_NPHY_PHASETR_A1 ; 
 int /*<<< orphan*/  BWN_NPHY_PHASETR_A2 ; 
 int /*<<< orphan*/  BWN_NPHY_PHASETR_B0 ; 
 int /*<<< orphan*/  BWN_NPHY_PHASETR_B1 ; 
 int /*<<< orphan*/  BWN_NPHY_PHASETR_B2 ; 
 int /*<<< orphan*/  BWN_NPHY_PIL_DW1 ; 
 int BWN_NPHY_PIL_DW_64QAM ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_LUT_TRSW_LO1 ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_LUT_TRSW_LO2 ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_LUT_TRSW_UP1 ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_LUT_TRSW_UP2 ; 
 int /*<<< orphan*/  BWN_NPHY_RXCTL ; 
 int /*<<< orphan*/  BWN_NPHY_SCRAM_SIGCTL ; 
 int BWN_NPHY_SCRAM_SIGCTL_SCM ; 
 int /*<<< orphan*/  BWN_NPHY_TXF_20CO_S2B1 ; 
 int /*<<< orphan*/  BWN_NPHY_TXF_20CO_S2B2 ; 
 int /*<<< orphan*/  BWN_NPHY_TXF_20CO_S2B3 ; 
 int /*<<< orphan*/  BWN_NTAB16 (int,int) ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 
 int bwn_hf_read (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_hf_write (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_nphy_gain_ctl_workarounds (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_set_rf_sequence (struct bwn_mac*,int,int*,int*,int) ; 
 int /*<<< orphan*/  bwn_ntab_write (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bwn_nphy_workarounds_rev1_2(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_n *nphy = phy->phy_n;

	uint8_t events1[7] = { 0x0, 0x1, 0x2, 0x8, 0x4, 0x5, 0x3 };
	uint8_t delays1[7] = { 0x8, 0x6, 0x6, 0x2, 0x4, 0x3C, 0x1 };

	uint8_t events2[7] = { 0x0, 0x3, 0x5, 0x4, 0x2, 0x1, 0x8 };
	uint8_t delays2[7] = { 0x8, 0x6, 0x2, 0x4, 0x4, 0x6, 0x1 };

	if (sc->sc_board_info.board_flags2 & BHND_BFL2_SKWRKFEM_BRD ||
	    sc->sc_board_info.board_type == BHND_BOARD_BCM943224M93) {
		delays1[0] = 0x1;
		delays1[5] = 0x14;
	}

	if (bwn_current_band(mac) == BWN_BAND_5G &&
	    nphy->band5g_pwrgain) {
		BWN_RF_MASK(mac, B2055_C1_TX_RF_SPARE, ~0x8);
		BWN_RF_MASK(mac, B2055_C2_TX_RF_SPARE, ~0x8);
	} else {
		BWN_RF_SET(mac, B2055_C1_TX_RF_SPARE, 0x8);
		BWN_RF_SET(mac, B2055_C2_TX_RF_SPARE, 0x8);
	}

	bwn_ntab_write(mac, BWN_NTAB16(8, 0x00), 0x000A);
	bwn_ntab_write(mac, BWN_NTAB16(8, 0x10), 0x000A);
	if (mac->mac_phy.rev < 3) {
		bwn_ntab_write(mac, BWN_NTAB16(8, 0x02), 0xCDAA);
		bwn_ntab_write(mac, BWN_NTAB16(8, 0x12), 0xCDAA);
	}

	if (mac->mac_phy.rev < 2) {
		bwn_ntab_write(mac, BWN_NTAB16(8, 0x08), 0x0000);
		bwn_ntab_write(mac, BWN_NTAB16(8, 0x18), 0x0000);
		bwn_ntab_write(mac, BWN_NTAB16(8, 0x07), 0x7AAB);
		bwn_ntab_write(mac, BWN_NTAB16(8, 0x17), 0x7AAB);
		bwn_ntab_write(mac, BWN_NTAB16(8, 0x06), 0x0800);
		bwn_ntab_write(mac, BWN_NTAB16(8, 0x16), 0x0800);
	}

	BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_LUT_TRSW_LO1, 0x2D8);
	BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_LUT_TRSW_UP1, 0x301);
	BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_LUT_TRSW_LO2, 0x2D8);
	BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_LUT_TRSW_UP2, 0x301);

	bwn_nphy_set_rf_sequence(mac, 0, events1, delays1, 7);
	bwn_nphy_set_rf_sequence(mac, 1, events2, delays2, 7);

	bwn_nphy_gain_ctl_workarounds(mac);

	if (mac->mac_phy.rev < 2) {
		if (BWN_PHY_READ(mac, BWN_NPHY_RXCTL) & 0x2)
			bwn_hf_write(mac, bwn_hf_read(mac) |
					BWN_HF_MLADVW);
	} else if (mac->mac_phy.rev == 2) {
		BWN_PHY_WRITE(mac, BWN_NPHY_CRSCHECK2, 0);
		BWN_PHY_WRITE(mac, BWN_NPHY_CRSCHECK3, 0);
	}

	if (mac->mac_phy.rev < 2)
		BWN_PHY_MASK(mac, BWN_NPHY_SCRAM_SIGCTL,
				~BWN_NPHY_SCRAM_SIGCTL_SCM);

	/* Set phase track alpha and beta */
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_A0, 0x125);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_A1, 0x1B3);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_A2, 0x105);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_B0, 0x16E);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_B1, 0xCD);
	BWN_PHY_WRITE(mac, BWN_NPHY_PHASETR_B2, 0x20);

	if (mac->mac_phy.rev < 3) {
		BWN_PHY_MASK(mac, BWN_NPHY_PIL_DW1,
			     ~BWN_NPHY_PIL_DW_64QAM & 0xFFFF);
		BWN_PHY_WRITE(mac, BWN_NPHY_TXF_20CO_S2B1, 0xB5);
		BWN_PHY_WRITE(mac, BWN_NPHY_TXF_20CO_S2B2, 0xA4);
		BWN_PHY_WRITE(mac, BWN_NPHY_TXF_20CO_S2B3, 0x00);
	}

	if (mac->mac_phy.rev == 2)
		BWN_PHY_SET(mac, BWN_NPHY_FINERX2_CGC,
				BWN_NPHY_FINERX2_CGC_DECGC);

	return (0);
}