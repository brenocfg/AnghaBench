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
struct bwn_phy {int rev; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int B2056_SYN_GPIO_MASTER1 ; 
 int B2056_SYN_RESERVED_ADDR30 ; 
 int B2056_SYN_RESERVED_ADDR31 ; 
 int B2056_TX0 ; 
 int B2056_TX1 ; 
 int B2056_TX_IQCAL_IDAC ; 
 int B2056_TX_IQCAL_VCM_HG ; 
 int B2056_TX_TSSIA ; 
 int B2056_TX_TSSIG ; 
 int B2056_TX_TSSI_MISC1 ; 
 int B2056_TX_TSSI_MISC2 ; 
 int B2056_TX_TSSI_MISC3 ; 
 int B2056_TX_TSSI_VCM ; 
 int B2056_TX_TX_AMP_DET ; 
 int B2056_TX_TX_SSI_MASTER ; 
 int B2056_TX_TX_SSI_MUX ; 
 scalar_t__ BWN_BAND_2G ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int,int) ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 

__attribute__((used)) static void bwn_nphy_ipa_internal_tssi_setup(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;

	uint8_t core;
	uint16_t r; /* routing */

	if (phy->rev >= 19) {
		/* TODO */
	} else if (phy->rev >= 7) {
		for (core = 0; core < 2; core++) {
			r = core ? 0x190 : 0x170;
			if (bwn_current_band(mac) == BWN_BAND_2G) {
				BWN_RF_WRITE(mac, r + 0x5, 0x5);
				BWN_RF_WRITE(mac, r + 0x9, 0xE);
				if (phy->rev != 5)
					BWN_RF_WRITE(mac, r + 0xA, 0);
				if (phy->rev != 7)
					BWN_RF_WRITE(mac, r + 0xB, 1);
				else
					BWN_RF_WRITE(mac, r + 0xB, 0x31);
			} else {
				BWN_RF_WRITE(mac, r + 0x5, 0x9);
				BWN_RF_WRITE(mac, r + 0x9, 0xC);
				BWN_RF_WRITE(mac, r + 0xB, 0x0);
				if (phy->rev != 5)
					BWN_RF_WRITE(mac, r + 0xA, 1);
				else
					BWN_RF_WRITE(mac, r + 0xA, 0x31);
			}
			BWN_RF_WRITE(mac, r + 0x6, 0);
			BWN_RF_WRITE(mac, r + 0x7, 0);
			BWN_RF_WRITE(mac, r + 0x8, 3);
			BWN_RF_WRITE(mac, r + 0xC, 0);
		}
	} else {
		if (bwn_current_band(mac) == BWN_BAND_2G)
			BWN_RF_WRITE(mac, B2056_SYN_RESERVED_ADDR31, 0x128);
		else
			BWN_RF_WRITE(mac, B2056_SYN_RESERVED_ADDR31, 0x80);
		BWN_RF_WRITE(mac, B2056_SYN_RESERVED_ADDR30, 0);
		BWN_RF_WRITE(mac, B2056_SYN_GPIO_MASTER1, 0x29);

		for (core = 0; core < 2; core++) {
			r = core ? B2056_TX1 : B2056_TX0;

			BWN_RF_WRITE(mac, r | B2056_TX_IQCAL_VCM_HG, 0);
			BWN_RF_WRITE(mac, r | B2056_TX_IQCAL_IDAC, 0);
			BWN_RF_WRITE(mac, r | B2056_TX_TSSI_VCM, 3);
			BWN_RF_WRITE(mac, r | B2056_TX_TX_AMP_DET, 0);
			BWN_RF_WRITE(mac, r | B2056_TX_TSSI_MISC1, 8);
			BWN_RF_WRITE(mac, r | B2056_TX_TSSI_MISC2, 0);
			BWN_RF_WRITE(mac, r | B2056_TX_TSSI_MISC3, 0);
			if (bwn_current_band(mac) == BWN_BAND_2G) {
				BWN_RF_WRITE(mac, r | B2056_TX_TX_SSI_MASTER,
						0x5);
				if (phy->rev != 5)
					BWN_RF_WRITE(mac, r | B2056_TX_TSSIA,
							0x00);
				if (phy->rev >= 5)
					BWN_RF_WRITE(mac, r | B2056_TX_TSSIG,
							0x31);
				else
					BWN_RF_WRITE(mac, r | B2056_TX_TSSIG,
							0x11);
				BWN_RF_WRITE(mac, r | B2056_TX_TX_SSI_MUX,
						0xE);
			} else {
				BWN_RF_WRITE(mac, r | B2056_TX_TX_SSI_MASTER,
						0x9);
				BWN_RF_WRITE(mac, r | B2056_TX_TSSIA, 0x31);
				BWN_RF_WRITE(mac, r | B2056_TX_TSSIG, 0x0);
				BWN_RF_WRITE(mac, r | B2056_TX_TX_SSI_MUX,
						0xC);
			}
		}
	}
}