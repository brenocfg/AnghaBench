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
struct bwn_phy_g {int pg_trsw_rx_gain; int pg_lna_lod_gain; int pg_pga_gain; int pg_lna_gain; } ;
struct bwn_phy {struct bwn_phy_g phy_g; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;
typedef  int int16_t ;

/* Variables and functions */
 scalar_t__ BWN_HAS_LOOPBACK (struct bwn_phy*) ; 
 int BWN_RF_READ (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  MAX (int,int /*<<< orphan*/ ) ; 
 int MIN (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bwn_lo_measure_gain_values(struct bwn_mac *mac, int16_t max_rx_gain,
    int use_trsw_rx)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_g *pg = &phy->phy_g;
	uint16_t tmp;

	if (max_rx_gain < 0)
		max_rx_gain = 0;

	if (BWN_HAS_LOOPBACK(phy)) {
		int trsw_rx = 0;
		int trsw_rx_gain;

		if (use_trsw_rx) {
			trsw_rx_gain = pg->pg_trsw_rx_gain / 2;
			if (max_rx_gain >= trsw_rx_gain) {
				trsw_rx_gain = max_rx_gain - trsw_rx_gain;
				trsw_rx = 0x20;
			}
		} else
			trsw_rx_gain = max_rx_gain;
		if (trsw_rx_gain < 9) {
			pg->pg_lna_lod_gain = 0;
		} else {
			pg->pg_lna_lod_gain = 1;
			trsw_rx_gain -= 8;
		}
		trsw_rx_gain = MIN(MAX(trsw_rx_gain, 0), 0x2d);
		pg->pg_pga_gain = trsw_rx_gain / 3;
		if (pg->pg_pga_gain >= 5) {
			pg->pg_pga_gain -= 5;
			pg->pg_lna_gain = 2;
		} else
			pg->pg_lna_gain = 0;
	} else {
		pg->pg_lna_gain = 0;
		pg->pg_trsw_rx_gain = 0x20;
		if (max_rx_gain >= 0x14) {
			pg->pg_lna_lod_gain = 1;
			pg->pg_pga_gain = 2;
		} else if (max_rx_gain >= 0x12) {
			pg->pg_lna_lod_gain = 1;
			pg->pg_pga_gain = 1;
		} else if (max_rx_gain >= 0xf) {
			pg->pg_lna_lod_gain = 1;
			pg->pg_pga_gain = 0;
		} else {
			pg->pg_lna_lod_gain = 0;
			pg->pg_pga_gain = 0;
		}
	}

	tmp = BWN_RF_READ(mac, 0x7a);
	if (pg->pg_lna_lod_gain == 0)
		tmp &= ~0x0008;
	else
		tmp |= 0x0008;
	BWN_RF_WRITE(mac, 0x7a, tmp);
}