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
struct bwn_txpwr_loctl {int tx_bias; int tx_magn; int /*<<< orphan*/  txctl_measured_time; } ;
struct bwn_phy_g {int pg_max_lb_gain; struct bwn_txpwr_loctl pg_loctl; } ;
struct bwn_phy {int rev; int rf_ver; int rf_rev; struct bwn_phy_g phy_g; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_GETTIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_HAS_LOOPBACK (struct bwn_phy*) ; 
 scalar_t__ BWN_HAS_TXMAG (struct bwn_phy*) ; 
 int /*<<< orphan*/  BWN_RF_MASK (struct bwn_mac*,int,int) ; 
 int BWN_RF_READ (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  BWN_RF_SETMASK (struct bwn_mac*,int,int,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  MAX (int,int /*<<< orphan*/ ) ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
 int N (int const*) ; 
 int abs (int) ; 
 int bwn_lo_calcfeed (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int bwn_lo_txctl_regtable (struct bwn_mac*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bwn_phy_g_set_bbatt (struct bwn_mac*,int) ; 

__attribute__((used)) static void
bwn_lo_measure_txctl_values(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_g *pg = &phy->phy_g;
	struct bwn_txpwr_loctl *lo = &pg->pg_loctl;
	uint16_t reg, mask;
	uint16_t trsw_rx, pga;
	uint16_t rf_pctl_reg;

	static const uint8_t tx_bias_values[] = {
		0x09, 0x08, 0x0a, 0x01, 0x00,
		0x02, 0x05, 0x04, 0x06,
	};
	static const uint8_t tx_magn_values[] = {
		0x70, 0x40,
	};

	if (!BWN_HAS_LOOPBACK(phy)) {
		rf_pctl_reg = 6;
		trsw_rx = 2;
		pga = 0;
	} else {
		int lb_gain;

		trsw_rx = 0;
		lb_gain = pg->pg_max_lb_gain / 2;
		if (lb_gain > 10) {
			rf_pctl_reg = 0;
			pga = abs(10 - lb_gain) / 6;
			pga = MIN(MAX(pga, 0), 15);
		} else {
			int cmp_val;
			int tmp;

			pga = 0;
			cmp_val = 0x24;
			if ((phy->rev >= 2) &&
			    (phy->rf_ver == 0x2050) && (phy->rf_rev == 8))
				cmp_val = 0x3c;
			tmp = lb_gain;
			if ((10 - lb_gain) < cmp_val)
				tmp = (10 - lb_gain);
			if (tmp < 0)
				tmp += 6;
			else
				tmp += 3;
			cmp_val /= 4;
			tmp /= 4;
			if (tmp >= cmp_val)
				rf_pctl_reg = cmp_val;
			else
				rf_pctl_reg = tmp;
		}
	}
	BWN_RF_SETMASK(mac, 0x43, 0xfff0, rf_pctl_reg);
	bwn_phy_g_set_bbatt(mac, 2);

	reg = bwn_lo_txctl_regtable(mac, &mask, NULL);
	mask = ~mask;
	BWN_RF_MASK(mac, reg, mask);

	if (BWN_HAS_TXMAG(phy)) {
		int i, j;
		int feedthrough;
		int min_feedth = 0xffff;
		uint8_t tx_magn, tx_bias;

		for (i = 0; i < N(tx_magn_values); i++) {
			tx_magn = tx_magn_values[i];
			BWN_RF_SETMASK(mac, 0x52, 0xff0f, tx_magn);
			for (j = 0; j < N(tx_bias_values); j++) {
				tx_bias = tx_bias_values[j];
				BWN_RF_SETMASK(mac, 0x52, 0xfff0, tx_bias);
				feedthrough = bwn_lo_calcfeed(mac, 0, pga,
				    trsw_rx);
				if (feedthrough < min_feedth) {
					lo->tx_bias = tx_bias;
					lo->tx_magn = tx_magn;
					min_feedth = feedthrough;
				}
				if (lo->tx_bias == 0)
					break;
			}
			BWN_RF_WRITE(mac, 0x52,
					  (BWN_RF_READ(mac, 0x52)
					   & 0xff00) | lo->tx_bias | lo->
					  tx_magn);
		}
	} else {
		lo->tx_magn = 0;
		lo->tx_bias = 0;
		BWN_RF_MASK(mac, 0x52, 0xfff0);
	}

	BWN_GETTIME(lo->txctl_measured_time);
}