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
struct bwn_phy {scalar_t__ type; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
#define  BWN_CCK_RATE_11MB 139 
#define  BWN_CCK_RATE_1MB 138 
#define  BWN_CCK_RATE_2MB 137 
#define  BWN_CCK_RATE_5MB 136 
 scalar_t__ BWN_ISCCKRATE (int) ; 
#define  BWN_OFDM_RATE_12MB 135 
#define  BWN_OFDM_RATE_18MB 134 
#define  BWN_OFDM_RATE_24MB 133 
#define  BWN_OFDM_RATE_36MB 132 
#define  BWN_OFDM_RATE_48MB 131 
#define  BWN_OFDM_RATE_54MB 130 
#define  BWN_OFDM_RATE_6MB 129 
#define  BWN_OFDM_RATE_9MB 128 
 scalar_t__ BWN_PHYTYPE_LP ; 
 int BWN_TXH_PHY1_BW_20 ; 
 int BWN_TXH_PHY1_CRATE_1_2 ; 
 int BWN_TXH_PHY1_CRATE_3_4 ; 
 int BWN_TXH_PHY1_MODE_SISO ; 
 int BWN_TXH_PHY1_MODUL_BPSK ; 
 int BWN_TXH_PHY1_MODUL_QAM16 ; 
 int BWN_TXH_PHY1_MODUL_QAM64 ; 
 int BWN_TXH_PHY1_MODUL_QPSK ; 

__attribute__((used)) static uint16_t
bwn_set_txhdr_phyctl1(struct bwn_mac *mac, uint8_t bitrate)
{
	struct bwn_phy *phy = &mac->mac_phy;
	uint16_t control = 0;
	uint16_t bw;

	/* XXX TODO: this is for LP phy, what about N-PHY, etc? */
	bw = BWN_TXH_PHY1_BW_20;

	if (BWN_ISCCKRATE(bitrate) && phy->type != BWN_PHYTYPE_LP) {
		control = bw;
	} else {
		control = bw;
		/* Figure out coding rate and modulation */
		/* XXX TODO: table-ize, for MCS transmit */
		/* Note: this is BWN_*_RATE values */
		switch (bitrate) {
		case BWN_CCK_RATE_1MB:
			control |= 0;
			break;
		case BWN_CCK_RATE_2MB:
			control |= 1;
			break;
		case BWN_CCK_RATE_5MB:
			control |= 2;
			break;
		case BWN_CCK_RATE_11MB:
			control |= 3;
			break;
		case BWN_OFDM_RATE_6MB:
			control |= BWN_TXH_PHY1_CRATE_1_2;
			control |= BWN_TXH_PHY1_MODUL_BPSK;
			break;
		case BWN_OFDM_RATE_9MB:
			control |= BWN_TXH_PHY1_CRATE_3_4;
			control |= BWN_TXH_PHY1_MODUL_BPSK;
			break;
		case BWN_OFDM_RATE_12MB:
			control |= BWN_TXH_PHY1_CRATE_1_2;
			control |= BWN_TXH_PHY1_MODUL_QPSK;
			break;
		case BWN_OFDM_RATE_18MB:
			control |= BWN_TXH_PHY1_CRATE_3_4;
			control |= BWN_TXH_PHY1_MODUL_QPSK;
			break;
		case BWN_OFDM_RATE_24MB:
			control |= BWN_TXH_PHY1_CRATE_1_2;
			control |= BWN_TXH_PHY1_MODUL_QAM16;
			break;
		case BWN_OFDM_RATE_36MB:
			control |= BWN_TXH_PHY1_CRATE_3_4;
			control |= BWN_TXH_PHY1_MODUL_QAM16;
			break;
		case BWN_OFDM_RATE_48MB:
			control |= BWN_TXH_PHY1_CRATE_1_2;
			control |= BWN_TXH_PHY1_MODUL_QAM64;
			break;
		case BWN_OFDM_RATE_54MB:
			control |= BWN_TXH_PHY1_CRATE_3_4;
			control |= BWN_TXH_PHY1_MODUL_QAM64;
			break;
		default:
			break;
		}
		control |= BWN_TXH_PHY1_MODE_SISO;
	}

	return control;
}