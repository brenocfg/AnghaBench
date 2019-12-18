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
struct ieee80211com {int /*<<< orphan*/  ic_curchan; } ;
struct bwn_txgain {int dummy; } ;
struct TYPE_3__ {scalar_t__ chip_id; } ;
struct bwn_softc {TYPE_1__ sc_cid; struct ieee80211com sc_ic; } ;
struct bwn_rxcompco {scalar_t__ rc_chan; int rc_c1; int rc_c0; } ;
struct bwn_phy_lp {scalar_t__ plp_chanfullcal; scalar_t__ plp_chan; int plp_txpctlmode; } ;
struct TYPE_4__ {int rev; struct bwn_phy_lp phy_lp; } ;
struct bwn_mac {TYPE_2__ mac_phy; struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 scalar_t__ BHND_CHIPID_BCM5354 ; 
 int /*<<< orphan*/  BWN_BTCOEX_CTL ; 
 int /*<<< orphan*/  BWN_BTCOEX_TXCTL ; 
 int BWN_PHYLP_TXPCTL_OFF ; 
 int /*<<< orphan*/  BWN_PHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  BWN_PHY_AFE_CTL_OVRVAL ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_OFDM (int) ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  BWN_PHY_RF_OVERRIDE_2 ; 
 int /*<<< orphan*/  BWN_PHY_RF_OVERRIDE_VAL_0 ; 
 int /*<<< orphan*/  BWN_PHY_RF_PWR_OVERRIDE ; 
 int /*<<< orphan*/  BWN_PHY_RX_COMP_COEFF_S ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 int N (struct bwn_rxcompco*) ; 
 int /*<<< orphan*/  bwn_mac_enable (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_mac_suspend (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_bugfix (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_calc_rx_iq_comp (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_clear_deaf (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_phy_lp_digflt_restore (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_digflt_save (struct bwn_mac*) ; 
 int bwn_phy_lp_get_bbmult (struct bwn_mac*) ; 
 struct bwn_txgain bwn_phy_lp_get_txgain (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_get_txpctlmode (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_bbmult (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_deaf (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_rxgain (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_trsw_over (struct bwn_mac*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_txgain (struct bwn_mac*,struct bwn_txgain*) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_txpctlmode (struct bwn_mac*,int) ; 
 struct bwn_rxcompco* bwn_rxcompco_5354 ; 
 struct bwn_rxcompco* bwn_rxcompco_r12 ; 
 struct bwn_rxcompco bwn_rxcompco_r2 ; 

__attribute__((used)) static void
bwn_phy_lp_calib(struct bwn_mac *mac)
{
	struct bwn_phy_lp *plp = &mac->mac_phy.phy_lp;
	struct bwn_softc *sc = mac->mac_sc;
	struct ieee80211com *ic = &sc->sc_ic;
	const struct bwn_rxcompco *rc = NULL;
	struct bwn_txgain ogain;
	int i, omode, oafeovr, orf, obbmult;
	uint8_t mode, fc = 0;

	if (plp->plp_chanfullcal != plp->plp_chan) {
		plp->plp_chanfullcal = plp->plp_chan;
		fc = 1;
	}

	bwn_mac_suspend(mac);

	/* BlueTooth Coexistance Override */
	BWN_WRITE_2(mac, BWN_BTCOEX_CTL, 0x3);
	BWN_WRITE_2(mac, BWN_BTCOEX_TXCTL, 0xff);

	if (mac->mac_phy.rev >= 2)
		bwn_phy_lp_digflt_save(mac);
	bwn_phy_lp_get_txpctlmode(mac);
	mode = plp->plp_txpctlmode;
	bwn_phy_lp_set_txpctlmode(mac, BWN_PHYLP_TXPCTL_OFF);
	if (mac->mac_phy.rev == 0 && mode != BWN_PHYLP_TXPCTL_OFF)
		bwn_phy_lp_bugfix(mac);
	if (mac->mac_phy.rev >= 2 && fc == 1) {
		bwn_phy_lp_get_txpctlmode(mac);
		omode = plp->plp_txpctlmode;
		oafeovr = BWN_PHY_READ(mac, BWN_PHY_AFE_CTL_OVR) & 0x40;
		if (oafeovr)
			ogain = bwn_phy_lp_get_txgain(mac);
		orf = BWN_PHY_READ(mac, BWN_PHY_RF_PWR_OVERRIDE) & 0xff;
		obbmult = bwn_phy_lp_get_bbmult(mac);
		bwn_phy_lp_set_txpctlmode(mac, BWN_PHYLP_TXPCTL_OFF);
		if (oafeovr)
			bwn_phy_lp_set_txgain(mac, &ogain);
		bwn_phy_lp_set_bbmult(mac, obbmult);
		bwn_phy_lp_set_txpctlmode(mac, omode);
		BWN_PHY_SETMASK(mac, BWN_PHY_RF_PWR_OVERRIDE, 0xff00, orf);
	}
	bwn_phy_lp_set_txpctlmode(mac, mode);
	if (mac->mac_phy.rev >= 2)
		bwn_phy_lp_digflt_restore(mac);

	/* do RX IQ Calculation; assumes that noise is true. */
	if (sc->sc_cid.chip_id == BHND_CHIPID_BCM5354) {
		for (i = 0; i < N(bwn_rxcompco_5354); i++) {
			if (bwn_rxcompco_5354[i].rc_chan == plp->plp_chan)
				rc = &bwn_rxcompco_5354[i];
		}
	} else if (mac->mac_phy.rev >= 2)
		rc = &bwn_rxcompco_r2;
	else {
		for (i = 0; i < N(bwn_rxcompco_r12); i++) {
			if (bwn_rxcompco_r12[i].rc_chan == plp->plp_chan)
				rc = &bwn_rxcompco_r12[i];
		}
	}
	if (rc == NULL)
		goto fail;

	BWN_PHY_SETMASK(mac, BWN_PHY_RX_COMP_COEFF_S, 0xff00, rc->rc_c1);
	BWN_PHY_SETMASK(mac, BWN_PHY_RX_COMP_COEFF_S, 0x00ff, rc->rc_c0 << 8);

	bwn_phy_lp_set_trsw_over(mac, 1 /* TX */, 0 /* RX */);

	if (IEEE80211_IS_CHAN_2GHZ(ic->ic_curchan)) {
		BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_0, 0x8);
		BWN_PHY_SETMASK(mac, BWN_PHY_RF_OVERRIDE_VAL_0, 0xfff7, 0);
	} else {
		BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_0, 0x20);
		BWN_PHY_SETMASK(mac, BWN_PHY_RF_OVERRIDE_VAL_0, 0xffdf, 0);
	}

	bwn_phy_lp_set_rxgain(mac, 0x2d5d);
	BWN_PHY_MASK(mac, BWN_PHY_AFE_CTL_OVR, 0xfffe);
	BWN_PHY_MASK(mac, BWN_PHY_AFE_CTL_OVRVAL, 0xfffe);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_0, 0x800);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_VAL_0, 0x800);
	bwn_phy_lp_set_deaf(mac, 0);
	/* XXX no checking return value? */
	(void)bwn_phy_lp_calc_rx_iq_comp(mac, 0xfff0);
	bwn_phy_lp_clear_deaf(mac, 0);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_0, 0xfffc);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_0, 0xfff7);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_0, 0xffdf);

	/* disable RX GAIN override. */
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_0, 0xfffe);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_0, 0xffef);
	BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_0, 0xffbf);
	if (mac->mac_phy.rev >= 2) {
		BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_2, 0xfeff);
		if (IEEE80211_IS_CHAN_2GHZ(ic->ic_curchan)) {
			BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_2, 0xfbff);
			BWN_PHY_MASK(mac, BWN_PHY_OFDM(0xe5), 0xfff7);
		}
	} else {
		BWN_PHY_MASK(mac, BWN_PHY_RF_OVERRIDE_2, 0xfdff);
	}

	BWN_PHY_MASK(mac, BWN_PHY_AFE_CTL_OVR, 0xfffe);
	BWN_PHY_MASK(mac, BWN_PHY_AFE_CTL_OVRVAL, 0xf7ff);
fail:
	bwn_mac_enable(mac);
}