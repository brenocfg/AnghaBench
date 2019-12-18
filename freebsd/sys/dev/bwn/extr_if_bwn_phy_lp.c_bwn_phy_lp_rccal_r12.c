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
struct bwn_txgain {int dummy; } ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_phy_lp_iq_est {int ie_ipwr; int ie_qpwr; } ;
struct bwn_phy_lp {int plp_txpctlmode; int plp_rccap; } ;
struct TYPE_2__ {struct bwn_phy_lp phy_lp; } ;
struct bwn_mac {struct bwn_softc* mac_sc; TYPE_1__ mac_phy; } ;
typedef  int /*<<< orphan*/  ie ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_B2062_N_RXBB_CALIB2 ; 
 int BWN_PHYLP_TXPCTL_OFF ; 
 int /*<<< orphan*/  BWN_PHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  BWN_PHY_AFE_CTL_OVRVAL ; 
 int /*<<< orphan*/  BWN_PHY_LP_PHY_CTL ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_PS_CTL_OVERRIDE_VAL0 ; 
 int /*<<< orphan*/  BWN_PHY_PS_CTL_OVERRIDE_VAL1 ; 
 int /*<<< orphan*/  BWN_PHY_PS_CTL_OVERRIDE_VAL2 ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  BWN_PHY_RF_OVERRIDE_2 ; 
 int /*<<< orphan*/  BWN_PHY_RF_OVERRIDE_2_VAL ; 
 int /*<<< orphan*/  BWN_PHY_RF_OVERRIDE_VAL_0 ; 
 int /*<<< orphan*/  BWN_PHY_RX_GAIN_CTL_OVERRIDE_VAL ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_TX_GAIN_CTL_OVERRIDE_VAL ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_clear_deaf (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_ddfs_turnoff (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_ddfs_turnon (struct bwn_mac*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int bwn_phy_lp_get_bbmult (struct bwn_mac*) ; 
 struct bwn_txgain bwn_phy_lp_get_txgain (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_get_txpctlmode (struct bwn_mac*) ; 
 int bwn_phy_lp_loopback (struct bwn_mac*) ; 
 int bwn_phy_lp_roundup (int,int,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_rx_iq_est (struct bwn_mac*,int,int,struct bwn_phy_lp_iq_est*) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_bbmult (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_deaf (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_rccap (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_rxgain_idx (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_trsw_over (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_txgain (struct bwn_mac*,struct bwn_txgain*) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_txpctlmode (struct bwn_mac*,int) ; 
 int bwn_phy_lp_switch_channel (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct bwn_phy_lp_iq_est*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bwn_phy_lp_rccal_r12(struct bwn_mac *mac)
{
	struct bwn_phy_lp *plp = &mac->mac_phy.phy_lp;
	struct bwn_softc *sc = mac->mac_sc;
	struct bwn_phy_lp_iq_est ie;
	struct bwn_txgain tx_gains;
	static const uint32_t pwrtbl[21] = {
		0x10000, 0x10557, 0x10e2d, 0x113e0, 0x10f22, 0x0ff64,
		0x0eda2, 0x0e5d4, 0x0efd1, 0x0fbe8, 0x0b7b8, 0x04b35,
		0x01a5e, 0x00a0b, 0x00444, 0x001fd, 0x000ff, 0x00088,
		0x0004c, 0x0002c, 0x0001a,
	};
	uint32_t npwr, ipwr, sqpwr, tmp;
	int loopback, i, j, sum, error;
	uint16_t save[7];
	uint8_t txo, bbmult, txpctlmode;

	error = bwn_phy_lp_switch_channel(mac, 7);
	if (error)
		device_printf(sc->sc_dev,
		    "failed to change channel to 7 (%d)\n", error);
	txo = (BWN_PHY_READ(mac, BWN_PHY_AFE_CTL_OVR) & 0x40) ? 1 : 0;
	bbmult = bwn_phy_lp_get_bbmult(mac);
	if (txo)
		tx_gains = bwn_phy_lp_get_txgain(mac);

	save[0] = BWN_PHY_READ(mac, BWN_PHY_RF_OVERRIDE_0);
	save[1] = BWN_PHY_READ(mac, BWN_PHY_RF_OVERRIDE_VAL_0);
	save[2] = BWN_PHY_READ(mac, BWN_PHY_AFE_CTL_OVR);
	save[3] = BWN_PHY_READ(mac, BWN_PHY_AFE_CTL_OVRVAL);
	save[4] = BWN_PHY_READ(mac, BWN_PHY_RF_OVERRIDE_2);
	save[5] = BWN_PHY_READ(mac, BWN_PHY_RF_OVERRIDE_2_VAL);
	save[6] = BWN_PHY_READ(mac, BWN_PHY_LP_PHY_CTL);

	bwn_phy_lp_get_txpctlmode(mac);
	txpctlmode = plp->plp_txpctlmode;
	bwn_phy_lp_set_txpctlmode(mac, BWN_PHYLP_TXPCTL_OFF);

	/* disable CRS */
	bwn_phy_lp_set_deaf(mac, 1);
	bwn_phy_lp_set_trsw_over(mac, 0, 1);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_VAL_0, 0xfffb);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_0, 0x4);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_VAL_0, 0xfff7);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_0, 0x8);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_VAL_0, 0x10);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_0, 0x10);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_VAL_0, 0xffdf);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_0, 0x20);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_VAL_0, 0xffbf);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_0, 0x40);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_2_VAL, 0x7);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_2_VAL, 0x38);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_2_VAL, 0xff3f);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_2_VAL, 0x100);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_2_VAL, 0xfdff);
	BWN_PHY_WRITE(mac, BWN_PHY_PS_CTL_OVERRIDE_VAL0, 0);
	BWN_PHY_WRITE(mac, BWN_PHY_PS_CTL_OVERRIDE_VAL1, 1);
	BWN_PHY_WRITE(mac, BWN_PHY_PS_CTL_OVERRIDE_VAL2, 0x20);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_2_VAL, 0xfbff);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_2_VAL, 0xf7ff);
	BWN_PHY_WRITE(mac, BWN_PHY_TX_GAIN_CTL_OVERRIDE_VAL, 0);
	BWN_PHY_WRITE(mac, BWN_PHY_RX_GAIN_CTL_OVERRIDE_VAL, 0x45af);
	BWN_PHY_WRITE(mac, BWN_PHY_RF_OVERRIDE_2, 0x3ff);

	loopback = bwn_phy_lp_loopback(mac);
	if (loopback == -1)
		goto done;
	bwn_phy_lp_set_rxgain_idx(mac, loopback);
	BWN_PHY_SETMASK(mac, BWN_PHY_LP_PHY_CTL, 0xffbf, 0x40);
	BWN_PHY_SETMASK(mac, BWN_PHY_RF_OVERRIDE_2_VAL, 0xfff8, 0x1);
	BWN_PHY_SETMASK(mac, BWN_PHY_RF_OVERRIDE_2_VAL, 0xffc7, 0x8);
	BWN_PHY_SETMASK(mac, BWN_PHY_RF_OVERRIDE_2_VAL, 0xff3f, 0xc0);

	tmp = 0;
	memset(&ie, 0, sizeof(ie));
	for (i = 128; i <= 159; i++) {
		BWN_RF_WRITE(mac, BWN_B2062_N_RXBB_CALIB2, i);
		sum = 0;
		for (j = 5; j <= 25; j++) {
			bwn_phy_lp_ddfs_turnon(mac, 1, 1, j, j, 0);
			if (!(bwn_phy_lp_rx_iq_est(mac, 1000, 32, &ie)))
				goto done;
			sqpwr = ie.ie_ipwr + ie.ie_qpwr;
			ipwr = ((pwrtbl[j - 5] >> 3) + 1) >> 1;
			npwr = bwn_phy_lp_roundup(sqpwr, (j == 5) ? sqpwr : 0,
			    12);
			sum += ((ipwr - npwr) * (ipwr - npwr));
			if ((i == 128) || (sum < tmp)) {
				plp->plp_rccap = i;
				tmp = sum;
			}
		}
	}
	bwn_phy_lp_ddfs_turnoff(mac);
done:
	/* restore CRS */
	bwn_phy_lp_clear_deaf(mac, 1);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_0, 0xff80);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_2, 0xfc00);

	BWN_PHY_WRITE(mac, BWN_PHY_RF_OVERRIDE_VAL_0, save[1]);
	BWN_PHY_WRITE(mac, BWN_PHY_RF_OVERRIDE_0, save[0]);
	BWN_PHY_WRITE(mac, BWN_PHY_AFE_CTL_OVRVAL, save[3]);
	BWN_PHY_WRITE(mac, BWN_PHY_AFE_CTL_OVR, save[2]);
	BWN_PHY_WRITE(mac, BWN_PHY_RF_OVERRIDE_2_VAL, save[5]);
	BWN_PHY_WRITE(mac, BWN_PHY_RF_OVERRIDE_2, save[4]);
	BWN_PHY_WRITE(mac, BWN_PHY_LP_PHY_CTL, save[6]);

	bwn_phy_lp_set_bbmult(mac, bbmult);
	if (txo)
		bwn_phy_lp_set_txgain(mac, &tx_gains);
	bwn_phy_lp_set_txpctlmode(mac, txpctlmode);
	if (plp->plp_rccap)
		bwn_phy_lp_set_rccap(mac);

	return (0);
}