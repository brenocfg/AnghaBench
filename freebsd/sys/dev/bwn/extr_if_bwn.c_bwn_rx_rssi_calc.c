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
struct bwn_phy_g {int* pg_nrssi_lt; } ;
struct bwn_phy {int rf_ver; int /*<<< orphan*/  type; struct bwn_phy_g phy_g; } ;
struct bwn_mac {TYPE_2__* mac_sc; struct bwn_phy mac_phy; } ;
typedef  int int8_t ;
struct TYPE_3__ {int board_flags; } ;
struct TYPE_4__ {TYPE_1__ sc_board_info; } ;

/* Variables and functions */
 int BHND_BFL_ADCDIV ; 
 int /*<<< orphan*/  BWN_PHYTYPE_G ; 

__attribute__((used)) static int8_t
bwn_rx_rssi_calc(struct bwn_mac *mac, uint8_t in_rssi,
    int ofdm, int adjust_2053, int adjust_2050)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_g *gphy = &phy->phy_g;
	int tmp;

	switch (phy->rf_ver) {
	case 0x2050:
		if (ofdm) {
			tmp = in_rssi;
			if (tmp > 127)
				tmp -= 256;
			tmp = tmp * 73 / 64;
			if (adjust_2050)
				tmp += 25;
			else
				tmp -= 3;
		} else {
			if (mac->mac_sc->sc_board_info.board_flags
			    & BHND_BFL_ADCDIV) {
				if (in_rssi > 63)
					in_rssi = 63;
				tmp = gphy->pg_nrssi_lt[in_rssi];
				tmp = (31 - tmp) * -131 / 128 - 57;
			} else {
				tmp = in_rssi;
				tmp = (31 - tmp) * -149 / 128 - 68;
			}
			if (phy->type == BWN_PHYTYPE_G && adjust_2050)
				tmp += 25;
		}
		break;
	case 0x2060:
		if (in_rssi > 127)
			tmp = in_rssi - 256;
		else
			tmp = in_rssi;
		break;
	default:
		tmp = in_rssi;
		tmp = (tmp - 11) * 103 / 64;
		if (adjust_2053)
			tmp -= 109;
		else
			tmp -= 83;
	}

	return (tmp);
}