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
struct bwn_phy_n_iq_comp {int a0; int b0; int a1; int b1; } ;
struct bwn_nphy_iq_est {int iq0_prod; int i0_pwr; int q0_pwr; int iq1_prod; int i1_pwr; int q1_pwr; } ;
struct TYPE_2__ {int rev; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int abs (int) ; 
 int /*<<< orphan*/  bwn_nphy_rx_iq_coeffs (struct bwn_mac*,int,struct bwn_phy_n_iq_comp*) ; 
 int /*<<< orphan*/  bwn_nphy_rx_iq_est (struct bwn_mac*,struct bwn_nphy_iq_est*,int,int,int) ; 
 int bwn_sqrt (struct bwn_mac*,int) ; 
 int fls (int) ; 

__attribute__((used)) static void bwn_nphy_calc_rx_iq_comp(struct bwn_mac *mac, uint8_t mask)
{
	int i;
	int32_t iq;
	uint32_t ii;
	uint32_t qq;
	int iq_nbits, qq_nbits;
	int arsh, brsh;
	uint16_t tmp, a, b;

	struct bwn_nphy_iq_est est;
	struct bwn_phy_n_iq_comp old;
	struct bwn_phy_n_iq_comp new = { };
	bool error = false;

	if (mask == 0)
		return;

	bwn_nphy_rx_iq_coeffs(mac, false, &old);
	bwn_nphy_rx_iq_coeffs(mac, true, &new);
	bwn_nphy_rx_iq_est(mac, &est, 0x4000, 32, false);
	new = old;

	for (i = 0; i < 2; i++) {
		if (i == 0 && (mask & 1)) {
			iq = est.iq0_prod;
			ii = est.i0_pwr;
			qq = est.q0_pwr;
		} else if (i == 1 && (mask & 2)) {
			iq = est.iq1_prod;
			ii = est.i1_pwr;
			qq = est.q1_pwr;
		} else {
			continue;
		}

		if (ii + qq < 2) {
			error = true;
			break;
		}

		iq_nbits = fls(abs(iq));
		qq_nbits = fls(qq);

		arsh = iq_nbits - 20;
		if (arsh >= 0) {
			a = -((iq << (30 - iq_nbits)) + (ii >> (1 + arsh)));
			tmp = ii >> arsh;
		} else {
			a = -((iq << (30 - iq_nbits)) + (ii << (-1 - arsh)));
			tmp = ii << -arsh;
		}
		if (tmp == 0) {
			error = true;
			break;
		}
		a /= tmp;

		brsh = qq_nbits - 11;
		if (brsh >= 0) {
			b = (qq << (31 - qq_nbits));
			tmp = ii >> brsh;
		} else {
			b = (qq << (31 - qq_nbits));
			tmp = ii << -brsh;
		}
		if (tmp == 0) {
			error = true;
			break;
		}
		b = bwn_sqrt(mac, b / tmp - a * a) - (1 << 10);

		if (i == 0 && (mask & 0x1)) {
			if (mac->mac_phy.rev >= 3) {
				new.a0 = a & 0x3FF;
				new.b0 = b & 0x3FF;
			} else {
				new.a0 = b & 0x3FF;
				new.b0 = a & 0x3FF;
			}
		} else if (i == 1 && (mask & 0x2)) {
			if (mac->mac_phy.rev >= 3) {
				new.a1 = a & 0x3FF;
				new.b1 = b & 0x3FF;
			} else {
				new.a1 = b & 0x3FF;
				new.b1 = a & 0x3FF;
			}
		}
	}

	if (error)
		new = old;

	bwn_nphy_rx_iq_coeffs(mac, true, &new);
}