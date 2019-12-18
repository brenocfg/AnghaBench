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
struct bwn_mac {int dummy; } ;
typedef  int int8_t ;
typedef  enum n_rssi_type { ____Placeholder_n_rssi_type } n_rssi_type ;
typedef  enum n_rail_type { ____Placeholder_n_rail_type } n_rail_type ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0I_PWRDET ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0I_RSSI_X ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0I_RSSI_Y ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0I_RSSI_Z ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0I_TBD ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0I_TSSI ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0Q_PWRDET ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0Q_RSSI_X ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0Q_RSSI_Y ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0Q_RSSI_Z ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0Q_TBD ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0Q_TSSI ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1I_PWRDET ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1I_RSSI_X ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1I_RSSI_Y ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1I_RSSI_Z ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1I_TBD ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1I_TSSI ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1Q_PWRDET ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1Q_RSSI_X ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1Q_RSSI_Y ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1Q_RSSI_Z ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1Q_TBD ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1Q_TSSI ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int N_RAIL_I ; 
 int N_RAIL_Q ; 
#define  N_RSSI_IQ 134 
#define  N_RSSI_NB 133 
#define  N_RSSI_TBD 132 
#define  N_RSSI_TSSI_2G 131 
#define  N_RSSI_TSSI_5G 130 
#define  N_RSSI_W1 129 
#define  N_RSSI_W2 128 
 int bwn_clamp_val (int,int,int) ; 

__attribute__((used)) static void bwn_nphy_scale_offset_rssi(struct bwn_mac *mac, uint16_t scale,
					int8_t offset, uint8_t core,
					enum n_rail_type rail,
					enum n_rssi_type rssi_type)
{
	uint16_t tmp;
	bool core1or5 = (core == 1) || (core == 5);
	bool core2or5 = (core == 2) || (core == 5);

	offset = bwn_clamp_val(offset, -32, 31);
	tmp = ((scale & 0x3F) << 8) | (offset & 0x3F);

	switch (rssi_type) {
	case N_RSSI_NB:
		if (core1or5 && rail == N_RAIL_I)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0I_RSSI_Z, tmp);
		if (core1or5 && rail == N_RAIL_Q)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0Q_RSSI_Z, tmp);
		if (core2or5 && rail == N_RAIL_I)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1I_RSSI_Z, tmp);
		if (core2or5 && rail == N_RAIL_Q)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1Q_RSSI_Z, tmp);
		break;
	case N_RSSI_W1:
		if (core1or5 && rail == N_RAIL_I)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0I_RSSI_X, tmp);
		if (core1or5 && rail == N_RAIL_Q)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0Q_RSSI_X, tmp);
		if (core2or5 && rail == N_RAIL_I)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1I_RSSI_X, tmp);
		if (core2or5 && rail == N_RAIL_Q)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1Q_RSSI_X, tmp);
		break;
	case N_RSSI_W2:
		if (core1or5 && rail == N_RAIL_I)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0I_RSSI_Y, tmp);
		if (core1or5 && rail == N_RAIL_Q)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0Q_RSSI_Y, tmp);
		if (core2or5 && rail == N_RAIL_I)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1I_RSSI_Y, tmp);
		if (core2or5 && rail == N_RAIL_Q)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1Q_RSSI_Y, tmp);
		break;
	case N_RSSI_TBD:
		if (core1or5 && rail == N_RAIL_I)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0I_TBD, tmp);
		if (core1or5 && rail == N_RAIL_Q)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0Q_TBD, tmp);
		if (core2or5 && rail == N_RAIL_I)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1I_TBD, tmp);
		if (core2or5 && rail == N_RAIL_Q)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1Q_TBD, tmp);
		break;
	case N_RSSI_IQ:
		if (core1or5 && rail == N_RAIL_I)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0I_PWRDET, tmp);
		if (core1or5 && rail == N_RAIL_Q)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0Q_PWRDET, tmp);
		if (core2or5 && rail == N_RAIL_I)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1I_PWRDET, tmp);
		if (core2or5 && rail == N_RAIL_Q)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1Q_PWRDET, tmp);
		break;
	case N_RSSI_TSSI_2G:
		if (core1or5)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0I_TSSI, tmp);
		if (core2or5)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1I_TSSI, tmp);
		break;
	case N_RSSI_TSSI_5G:
		if (core1or5)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0Q_TSSI, tmp);
		if (core2or5)
			BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1Q_TSSI, tmp);
		break;
	}
}