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
struct bwn_phy_lp_iq_est {int ie_ipwr; int ie_qpwr; int ie_iqprod; } ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_RX_COMP_COEFF_S ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CALC_COEFF (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CALC_COEFF2 (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bwn_nbits (int) ; 
 int bwn_phy_lp_rx_iq_est (struct bwn_mac*,int,int,struct bwn_phy_lp_iq_est*) ; 
 int bwn_sqrt (struct bwn_mac*,int) ; 

__attribute__((used)) static int
bwn_phy_lp_calc_rx_iq_comp(struct bwn_mac *mac, uint16_t sample)
{
#define	CALC_COEFF(_v, _x, _y, _z)	do {				\
	int _t;								\
	_t = _x - 20;							\
	if (_t >= 0) {							\
		_v = ((_y << (30 - _x)) + (_z >> (1 + _t))) / (_z >> _t); \
	} else {							\
		_v = ((_y << (30 - _x)) + (_z << (-1 - _t))) / (_z << -_t); \
	}								\
} while (0)
#define	CALC_COEFF2(_v, _x, _y, _z)	do {				\
	int _t;								\
	_t = _x - 11;							\
	if (_t >= 0)							\
		_v = (_y << (31 - _x)) / (_z >> _t);			\
	else								\
		_v = (_y << (31 - _x)) / (_z << -_t);			\
} while (0)
	struct bwn_phy_lp_iq_est ie;
	uint16_t v0, v1;
	int tmp[2], ret;

	v1 = BWN_PHY_READ(mac, BWN_PHY_RX_COMP_COEFF_S);
	v0 = v1 >> 8;
	v1 |= 0xff;

	BWN_PHY_SETMASK(mac, BWN_PHY_RX_COMP_COEFF_S, 0xff00, 0x00c0);
	BWN_PHY_MASK(mac, BWN_PHY_RX_COMP_COEFF_S, 0x00ff);

	ret = bwn_phy_lp_rx_iq_est(mac, sample, 32, &ie);
	if (ret == 0)
		goto done;

	if (ie.ie_ipwr + ie.ie_qpwr < 2) {
		ret = 0;
		goto done;
	}

	CALC_COEFF(tmp[0], bwn_nbits(ie.ie_iqprod), ie.ie_iqprod, ie.ie_ipwr);
	CALC_COEFF2(tmp[1], bwn_nbits(ie.ie_qpwr), ie.ie_qpwr, ie.ie_ipwr);

	tmp[1] = -bwn_sqrt(mac, tmp[1] - (tmp[0] * tmp[0]));
	v0 = tmp[0] >> 3;
	v1 = tmp[1] >> 4;
done:
	BWN_PHY_SETMASK(mac, BWN_PHY_RX_COMP_COEFF_S, 0xff00, v1);
	BWN_PHY_SETMASK(mac, BWN_PHY_RX_COMP_COEFF_S, 0x00ff, v0 << 8);
	return ret;
#undef CALC_COEFF
#undef CALC_COEFF2
}