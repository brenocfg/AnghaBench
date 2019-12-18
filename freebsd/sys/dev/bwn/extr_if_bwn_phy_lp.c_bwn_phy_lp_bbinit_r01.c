#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct ieee80211com {int /*<<< orphan*/  ic_curchan; } ;
struct TYPE_5__ {scalar_t__ chip_id; scalar_t__ chip_pkg; } ;
struct TYPE_4__ {int board_flags; int board_type; } ;
struct bwn_softc {TYPE_2__ sc_cid; TYPE_1__ sc_board_info; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_pmu; struct ieee80211com sc_ic; } ;
struct bwn_smpair {int member_1; int member_2; int mask; int set; int /*<<< orphan*/  const offset; int /*<<< orphan*/  const member_0; } ;
struct bwn_phy_lp {int plp_rxpwroffset; int plp_rssivf; int plp_rssivc; int plp_bxarch; } ;
struct TYPE_6__ {scalar_t__ rev; struct bwn_phy_lp phy_lp; } ;
struct bwn_mac {TYPE_3__ mac_phy; struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int BHND_BFL_FEM ; 
 int BHND_BFL_FEM_BT ; 
 int BHND_BFL_PAREF ; 
 int BHND_BFL_RSSIINV ; 
 scalar_t__ BHND_CHIPID_BCM5354 ; 
 scalar_t__ BHND_PKGID_BCM4712SMALL ; 
 int /*<<< orphan*/  BHND_REGULATOR_PAREF_LDO ; 
 int BWN_HF_PR45960W ; 
 int /*<<< orphan*/  BWN_PHY_4C3 ; 
 int /*<<< orphan*/  BWN_PHY_4C4 ; 
 int /*<<< orphan*/  BWN_PHY_4C5 ; 
 int /*<<< orphan*/  BWN_PHY_ADC_COMPENSATION_CTL ; 
 int /*<<< orphan*/  const BWN_PHY_AFE_ADC_CTL_0 ; 
 int /*<<< orphan*/  BWN_PHY_AFE_CTL ; 
 int /*<<< orphan*/  BWN_PHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  const BWN_PHY_AFE_DAC_CTL ; 
 int /*<<< orphan*/  BWN_PHY_AFE_RSSI_CTL_0 ; 
 int /*<<< orphan*/  const BWN_PHY_AFE_RSSI_CTL_1 ; 
#define  BWN_PHY_CLIPCTRTHRESH 139 
 int /*<<< orphan*/  BWN_PHY_COPY (struct bwn_mac*,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const BWN_PHY_CRSGAIN_CTL ; 
#define  BWN_PHY_CRS_ED_THRESH 138 
 int /*<<< orphan*/  const BWN_PHY_DSSS_CONFIRM_CNT ; 
#define  BWN_PHY_GAINDIRECTMISMATCH 137 
#define  BWN_PHY_GAIN_MISMATCH_LIMIT 136 
 int /*<<< orphan*/  BWN_PHY_GPIO_OUTEN ; 
 int /*<<< orphan*/  BWN_PHY_GPIO_SELECT ; 
 int /*<<< orphan*/  const BWN_PHY_HIGAINDB ; 
 int /*<<< orphan*/  const BWN_PHY_IDLEAFTERPKTRXTO ; 
 int /*<<< orphan*/  const BWN_PHY_INPUT_PWRDB ; 
 int /*<<< orphan*/  const BWN_PHY_LOWGAINDB ; 
 int /*<<< orphan*/  const BWN_PHY_LP_PHY_CTL ; 
 int /*<<< orphan*/  const BWN_PHY_LP_RF_SIGNAL_LUT ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  const BWN_PHY_MINPWR_LEVEL ; 
 int /*<<< orphan*/  const BWN_PHY_OFDMSYNCTHRESH0 ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  BWN_PHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  BWN_PHY_RF_OVERRIDE_2 ; 
 int /*<<< orphan*/  const BWN_PHY_RX_RADIO_CTL ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/  const,int,int) ; 
 int /*<<< orphan*/  const BWN_PHY_SYNCPEAKCNT ; 
#define  BWN_PHY_TR_LOOKUP_1 135 
#define  BWN_PHY_TR_LOOKUP_2 134 
#define  BWN_PHY_TR_LOOKUP_3 133 
#define  BWN_PHY_TR_LOOKUP_4 132 
#define  BWN_PHY_TR_LOOKUP_5 131 
#define  BWN_PHY_TR_LOOKUP_6 130 
#define  BWN_PHY_TR_LOOKUP_7 129 
#define  BWN_PHY_TR_LOOKUP_8 128 
 int /*<<< orphan*/  const BWN_PHY_VERYLOWGAINDB ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_TAB_2 (int,int) ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (int /*<<< orphan*/ ) ; 
 int N (struct bwn_smpair const*) ; 
 int bhnd_pmu_disable_regulator (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bhnd_pmu_enable_regulator (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bhnd_pmu_set_voltage_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bwn_hf_read (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_hf_write (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_tab_write (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
bwn_phy_lp_bbinit_r01(struct bwn_mac *mac)
{
	struct bwn_phy_lp *plp = &mac->mac_phy.phy_lp;
	struct bwn_softc *sc = mac->mac_sc;
	struct ieee80211com *ic = &sc->sc_ic;
	static const struct bwn_smpair v1[] = {
		{ BWN_PHY_CLIPCTRTHRESH, 0xffe0, 0x0005 },
		{ BWN_PHY_CLIPCTRTHRESH, 0xfc1f, 0x0180 },
		{ BWN_PHY_CLIPCTRTHRESH, 0x83ff, 0x3c00 },
		{ BWN_PHY_GAINDIRECTMISMATCH, 0xfff0, 0x0005 },
		{ BWN_PHY_GAIN_MISMATCH_LIMIT, 0xffc0, 0x001a },
		{ BWN_PHY_CRS_ED_THRESH, 0xff00, 0x00b3 },
		{ BWN_PHY_CRS_ED_THRESH, 0x00ff, 0xad00 }
	};
	static const struct bwn_smpair v2[] = {
		{ BWN_PHY_TR_LOOKUP_1, 0xffc0, 0x000a },
		{ BWN_PHY_TR_LOOKUP_1, 0x3f00, 0x0900 },
		{ BWN_PHY_TR_LOOKUP_2, 0xffc0, 0x000a },
		{ BWN_PHY_TR_LOOKUP_2, 0xc0ff, 0x0b00 },
		{ BWN_PHY_TR_LOOKUP_3, 0xffc0, 0x000a },
		{ BWN_PHY_TR_LOOKUP_3, 0xc0ff, 0x0400 },
		{ BWN_PHY_TR_LOOKUP_4, 0xffc0, 0x000a },
		{ BWN_PHY_TR_LOOKUP_4, 0xc0ff, 0x0b00 },
		{ BWN_PHY_TR_LOOKUP_5, 0xffc0, 0x000a },
		{ BWN_PHY_TR_LOOKUP_5, 0xc0ff, 0x0900 },
		{ BWN_PHY_TR_LOOKUP_6, 0xffc0, 0x000a },
		{ BWN_PHY_TR_LOOKUP_6, 0xc0ff, 0x0b00 },
		{ BWN_PHY_TR_LOOKUP_7, 0xffc0, 0x000a },
		{ BWN_PHY_TR_LOOKUP_7, 0xc0ff, 0x0900 },
		{ BWN_PHY_TR_LOOKUP_8, 0xffc0, 0x000a },
		{ BWN_PHY_TR_LOOKUP_8, 0xc0ff, 0x0b00 }
	};
	static const struct bwn_smpair v3[] = {
		{ BWN_PHY_TR_LOOKUP_1, 0xffc0, 0x0001 },
		{ BWN_PHY_TR_LOOKUP_1, 0xc0ff, 0x0400 },
		{ BWN_PHY_TR_LOOKUP_2, 0xffc0, 0x0001 },
		{ BWN_PHY_TR_LOOKUP_2, 0xc0ff, 0x0500 },
		{ BWN_PHY_TR_LOOKUP_3, 0xffc0, 0x0002 },
		{ BWN_PHY_TR_LOOKUP_3, 0xc0ff, 0x0800 },
		{ BWN_PHY_TR_LOOKUP_4, 0xffc0, 0x0002 },
		{ BWN_PHY_TR_LOOKUP_4, 0xc0ff, 0x0a00 }
	};
	static const struct bwn_smpair v4[] = {
		{ BWN_PHY_TR_LOOKUP_1, 0xffc0, 0x0004 },
		{ BWN_PHY_TR_LOOKUP_1, 0xc0ff, 0x0800 },
		{ BWN_PHY_TR_LOOKUP_2, 0xffc0, 0x0004 },
		{ BWN_PHY_TR_LOOKUP_2, 0xc0ff, 0x0c00 },
		{ BWN_PHY_TR_LOOKUP_3, 0xffc0, 0x0002 },
		{ BWN_PHY_TR_LOOKUP_3, 0xc0ff, 0x0100 },
		{ BWN_PHY_TR_LOOKUP_4, 0xffc0, 0x0002 },
		{ BWN_PHY_TR_LOOKUP_4, 0xc0ff, 0x0300 }
	};
	static const struct bwn_smpair v5[] = {
		{ BWN_PHY_TR_LOOKUP_1, 0xffc0, 0x000a },
		{ BWN_PHY_TR_LOOKUP_1, 0xc0ff, 0x0900 },
		{ BWN_PHY_TR_LOOKUP_2, 0xffc0, 0x000a },
		{ BWN_PHY_TR_LOOKUP_2, 0xc0ff, 0x0b00 },
		{ BWN_PHY_TR_LOOKUP_3, 0xffc0, 0x0006 },
		{ BWN_PHY_TR_LOOKUP_3, 0xc0ff, 0x0500 },
		{ BWN_PHY_TR_LOOKUP_4, 0xffc0, 0x0006 },
		{ BWN_PHY_TR_LOOKUP_4, 0xc0ff, 0x0700 }
	};
	int error, i;
	uint16_t tmp, tmp2;

	BWN_PHY_MASK(mac, BWN_PHY_AFE_DAC_CTL, 0xf7ff);
	BWN_PHY_WRITE(mac, BWN_PHY_AFE_CTL, 0);
	BWN_PHY_WRITE(mac, BWN_PHY_AFE_CTL_OVR, 0);
	BWN_PHY_WRITE(mac, BWN_PHY_RF_OVERRIDE_0, 0);
	BWN_PHY_WRITE(mac, BWN_PHY_RF_OVERRIDE_2, 0);
	BWN_PHY_SET(mac, BWN_PHY_AFE_DAC_CTL, 0x0004);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDMSYNCTHRESH0, 0xff00, 0x0078);
	BWN_PHY_SETMASK(mac, BWN_PHY_CLIPCTRTHRESH, 0x83ff, 0x5800);
	BWN_PHY_WRITE(mac, BWN_PHY_ADC_COMPENSATION_CTL, 0x0016);
	BWN_PHY_SETMASK(mac, BWN_PHY_AFE_ADC_CTL_0, 0xfff8, 0x0004);
	BWN_PHY_SETMASK(mac, BWN_PHY_VERYLOWGAINDB, 0x00ff, 0x5400);
	BWN_PHY_SETMASK(mac, BWN_PHY_HIGAINDB, 0x00ff, 0x2400);
	BWN_PHY_SETMASK(mac, BWN_PHY_LOWGAINDB, 0x00ff, 0x2100);
	BWN_PHY_SETMASK(mac, BWN_PHY_VERYLOWGAINDB, 0xff00, 0x0006);
	BWN_PHY_MASK(mac, BWN_PHY_RX_RADIO_CTL, 0xfffe);
	for (i = 0; i < N(v1); i++)
		BWN_PHY_SETMASK(mac, v1[i].offset, v1[i].mask, v1[i].set);
	BWN_PHY_SETMASK(mac, BWN_PHY_INPUT_PWRDB,
	    0xff00, plp->plp_rxpwroffset);
	if ((sc->sc_board_info.board_flags & BHND_BFL_FEM) &&
	    ((IEEE80211_IS_CHAN_5GHZ(ic->ic_curchan)) ||
	   (sc->sc_board_info.board_flags & BHND_BFL_PAREF))) {
		error = bhnd_pmu_set_voltage_raw(sc->sc_pmu,
		    BHND_REGULATOR_PAREF_LDO, 0x28);
		if (error)
			device_printf(sc->sc_dev, "failed to set PAREF LDO "
			    "voltage: %d\n", error);

		error = bhnd_pmu_enable_regulator(sc->sc_pmu,
		    BHND_REGULATOR_PAREF_LDO);
		if (error)
			device_printf(sc->sc_dev, "failed to enable PAREF LDO "
			    "regulator: %d\n", error);

		if (mac->mac_phy.rev == 0)
			BWN_PHY_SETMASK(mac, BWN_PHY_LP_RF_SIGNAL_LUT,
			    0xffcf, 0x0010);
		bwn_tab_write(mac, BWN_TAB_2(11, 7), 60);
	} else {
		error = bhnd_pmu_disable_regulator(sc->sc_pmu,
		    BHND_REGULATOR_PAREF_LDO);
		if (error)
			device_printf(sc->sc_dev, "failed to disable PAREF LDO "
			    "regulator: %d\n", error);

		BWN_PHY_SETMASK(mac, BWN_PHY_LP_RF_SIGNAL_LUT, 0xffcf, 0x0020);
		bwn_tab_write(mac, BWN_TAB_2(11, 7), 100);
	}
	tmp = plp->plp_rssivf | plp->plp_rssivc << 4 | 0xa000;
	BWN_PHY_WRITE(mac, BWN_PHY_AFE_RSSI_CTL_0, tmp);
	if (sc->sc_board_info.board_flags & BHND_BFL_RSSIINV)
		BWN_PHY_SETMASK(mac, BWN_PHY_AFE_RSSI_CTL_1, 0xf000, 0x0aaa);
	else
		BWN_PHY_SETMASK(mac, BWN_PHY_AFE_RSSI_CTL_1, 0xf000, 0x02aa);
	bwn_tab_write(mac, BWN_TAB_2(11, 1), 24);
	BWN_PHY_SETMASK(mac, BWN_PHY_RX_RADIO_CTL,
	    0xfff9, (plp->plp_bxarch << 1));
	if (mac->mac_phy.rev == 1 &&
	    (sc->sc_board_info.board_flags & BHND_BFL_FEM_BT)) {
		for (i = 0; i < N(v2); i++)
			BWN_PHY_SETMASK(mac, v2[i].offset, v2[i].mask,
			    v2[i].set);
	} else if (IEEE80211_IS_CHAN_5GHZ(ic->ic_curchan) ||
	    (sc->sc_board_info.board_type == 0x048a) ||
	    ((mac->mac_phy.rev == 0) &&
	     (sc->sc_board_info.board_flags & BHND_BFL_FEM))) {
		for (i = 0; i < N(v3); i++)
			BWN_PHY_SETMASK(mac, v3[i].offset, v3[i].mask,
			    v3[i].set);
	} else if (mac->mac_phy.rev == 1 ||
		  (sc->sc_board_info.board_flags & BHND_BFL_FEM)) {
		for (i = 0; i < N(v4); i++)
			BWN_PHY_SETMASK(mac, v4[i].offset, v4[i].mask,
			    v4[i].set);
	} else {
		for (i = 0; i < N(v5); i++)
			BWN_PHY_SETMASK(mac, v5[i].offset, v5[i].mask,
			    v5[i].set);
	}
	if (mac->mac_phy.rev == 1 &&
	    (sc->sc_board_info.board_flags & BHND_BFL_PAREF)) {
		BWN_PHY_COPY(mac, BWN_PHY_TR_LOOKUP_5, BWN_PHY_TR_LOOKUP_1);
		BWN_PHY_COPY(mac, BWN_PHY_TR_LOOKUP_6, BWN_PHY_TR_LOOKUP_2);
		BWN_PHY_COPY(mac, BWN_PHY_TR_LOOKUP_7, BWN_PHY_TR_LOOKUP_3);
		BWN_PHY_COPY(mac, BWN_PHY_TR_LOOKUP_8, BWN_PHY_TR_LOOKUP_4);
	}
	if ((sc->sc_board_info.board_flags & BHND_BFL_FEM_BT) &&
	    (sc->sc_cid.chip_id == BHND_CHIPID_BCM5354) &&
	    (sc->sc_cid.chip_pkg == BHND_PKGID_BCM4712SMALL)) {
		BWN_PHY_SET(mac, BWN_PHY_CRSGAIN_CTL, 0x0006);
		BWN_PHY_WRITE(mac, BWN_PHY_GPIO_SELECT, 0x0005);
		BWN_PHY_WRITE(mac, BWN_PHY_GPIO_OUTEN, 0xffff);
		bwn_hf_write(mac, bwn_hf_read(mac) | BWN_HF_PR45960W);
	}
	if (IEEE80211_IS_CHAN_2GHZ(ic->ic_curchan)) {
		BWN_PHY_SET(mac, BWN_PHY_LP_PHY_CTL, 0x8000);
		BWN_PHY_SET(mac, BWN_PHY_CRSGAIN_CTL, 0x0040);
		BWN_PHY_SETMASK(mac, BWN_PHY_MINPWR_LEVEL, 0x00ff, 0xa400);
		BWN_PHY_SETMASK(mac, BWN_PHY_CRSGAIN_CTL, 0xf0ff, 0x0b00);
		BWN_PHY_SETMASK(mac, BWN_PHY_SYNCPEAKCNT, 0xfff8, 0x0007);
		BWN_PHY_SETMASK(mac, BWN_PHY_DSSS_CONFIRM_CNT, 0xfff8, 0x0003);
		BWN_PHY_SETMASK(mac, BWN_PHY_DSSS_CONFIRM_CNT, 0xffc7, 0x0020);
		BWN_PHY_MASK(mac, BWN_PHY_IDLEAFTERPKTRXTO, 0x00ff);
	} else {
		BWN_PHY_MASK(mac, BWN_PHY_LP_PHY_CTL, 0x7fff);
		BWN_PHY_MASK(mac, BWN_PHY_CRSGAIN_CTL, 0xffbf);
	}
	if (mac->mac_phy.rev == 1) {
		tmp = BWN_PHY_READ(mac, BWN_PHY_CLIPCTRTHRESH);
		tmp2 = (tmp & 0x03e0) >> 5;
		tmp2 |= tmp2 << 5;
		BWN_PHY_WRITE(mac, BWN_PHY_4C3, tmp2);
		tmp = BWN_PHY_READ(mac, BWN_PHY_GAINDIRECTMISMATCH);
		tmp2 = (tmp & 0x1f00) >> 8;
		tmp2 |= tmp2 << 5;
		BWN_PHY_WRITE(mac, BWN_PHY_4C4, tmp2);
		tmp = BWN_PHY_READ(mac, BWN_PHY_VERYLOWGAINDB);
		tmp2 = tmp & 0x00ff;
		tmp2 |= tmp << 8;
		BWN_PHY_WRITE(mac, BWN_PHY_4C5, tmp2);
	}
}