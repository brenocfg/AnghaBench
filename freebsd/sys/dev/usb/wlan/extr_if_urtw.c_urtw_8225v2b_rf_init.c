#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usb_error_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
struct ieee80211com {int* ic_macaddr; int /*<<< orphan*/  ic_vaps; } ;
struct urtw_softc {int sc_acmctl; int /*<<< orphan*/  sc_mtx; struct ieee80211com sc_ic; } ;
struct ieee80211vap {int* iv_myaddr; } ;
struct TYPE_5__ {int reg; int val; } ;

/* Variables and functions */
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int URTW_8187B_AC_BE ; 
 int URTW_8187B_AC_BK ; 
 int URTW_8187B_AC_VI ; 
 int URTW_8187B_AC_VO ; 
 int URTW_8225_ADDR_0_MAGIC ; 
 int URTW_8225_ADDR_1_MAGIC ; 
 int URTW_8225_ADDR_2_MAGIC ; 
 int URTW_8225_ADDR_3_MAGIC ; 
 int URTW_8225_ADDR_5_MAGIC ; 
 int URTW_ACM_CONTROL ; 
 int /*<<< orphan*/  URTW_ARFR ; 
 int /*<<< orphan*/  URTW_ATIM_WND ; 
 int /*<<< orphan*/  URTW_BEACON_INTERVAL ; 
 int /*<<< orphan*/  URTW_BRSR_8187B ; 
 int URTW_CONFIG1 ; 
 int URTW_CONFIG3 ; 
 int URTW_CONFIG3_ANAPARAM_WRITE ; 
 int URTW_CW_CONF ; 
 int URTW_CW_CONF_PERPACKET_RETRY ; 
 int /*<<< orphan*/  URTW_EPROM_CMD_CONFIG ; 
 int /*<<< orphan*/  URTW_EPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  URTW_FEMR_FOR_8187B ; 
 int /*<<< orphan*/  URTW_INT_MIG ; 
 int URTW_MSR ; 
 int URTW_MSR_LINK_ENEDCA ; 
 int URTW_RATE_FALLBACK ; 
 int URTW_RATE_FALLBACK_ENABLE ; 
 int /*<<< orphan*/  URTW_RFSW_CTRL ; 
 int /*<<< orphan*/  URTW_RF_PINS_ENABLE ; 
 int /*<<< orphan*/  URTW_RF_PINS_OUTPUT ; 
 int /*<<< orphan*/  URTW_RF_PINS_SELECT ; 
 int URTW_RF_TIMING ; 
 int /*<<< orphan*/  URTW_TID_AC_MAP ; 
 int URTW_TX_AGC_CTL ; 
 int URTW_TX_AGC_CTL_PERPACKET_GAIN ; 
 int URTW_TX_ANTENNA ; 
 int URTW_TX_GAIN_CCK ; 
 int URTW_TX_GAIN_OFDM ; 
 int URTW_WPA_CONFIG ; 
 unsigned int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  urtw_8187_write_phy_cck (struct urtw_softc*,int,int) ; 
 int /*<<< orphan*/  urtw_8187_write_phy_ofdm (struct urtw_softc*,int,int) ; 
 int /*<<< orphan*/  urtw_8225_write (struct urtw_softc*,int,int) ; 
 TYPE_1__* urtw_8225v2b_rf_part0 ; 
 TYPE_1__* urtw_8225v2b_rf_part1 ; 
 TYPE_1__* urtw_8225v2b_rf_part2 ; 
 int* urtw_8225v2b_rxgain ; 
 int* urtw_8225z2_agc ; 
 int /*<<< orphan*/  urtw_read8_m (struct urtw_softc*,int,int*) ; 
 scalar_t__ urtw_set_macaddr (struct urtw_softc*,int const*) ; 
 scalar_t__ urtw_set_mode (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urtw_write16_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  urtw_write32_m (struct urtw_softc*,int,int) ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int,int) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
urtw_8225v2b_rf_init(struct urtw_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	const uint8_t *macaddr;
	unsigned int i;
	uint8_t data8;
	usb_error_t error;

	error = urtw_set_mode(sc, URTW_EPROM_CMD_CONFIG);
	if (error)
		goto fail;

	/*
	 * initialize extra registers on 8187
	 */
	urtw_write16_m(sc, URTW_BRSR_8187B, 0xfff);

	/* retry limit */
	urtw_read8_m(sc, URTW_CW_CONF, &data8);
	data8 |= URTW_CW_CONF_PERPACKET_RETRY;
	urtw_write8_m(sc, URTW_CW_CONF, data8);

	/* TX AGC */
	urtw_read8_m(sc, URTW_TX_AGC_CTL, &data8);
	data8 |= URTW_TX_AGC_CTL_PERPACKET_GAIN;
	urtw_write8_m(sc, URTW_TX_AGC_CTL, data8);

	/* Auto Rate Fallback Control */
#define	URTW_ARFR	0x1e0
	urtw_write16_m(sc, URTW_ARFR, 0xfff);
	urtw_read8_m(sc, URTW_RATE_FALLBACK, &data8);
	urtw_write8_m(sc, URTW_RATE_FALLBACK,
	    data8 | URTW_RATE_FALLBACK_ENABLE);

	urtw_read8_m(sc, URTW_MSR, &data8);
	urtw_write8_m(sc, URTW_MSR, data8 & 0xf3);
	urtw_read8_m(sc, URTW_MSR, &data8);
	urtw_write8_m(sc, URTW_MSR, data8 | URTW_MSR_LINK_ENEDCA);
	urtw_write8_m(sc, URTW_ACM_CONTROL, sc->sc_acmctl);

	urtw_write16_m(sc, URTW_ATIM_WND, 2);
	urtw_write16_m(sc, URTW_BEACON_INTERVAL, 100);
#define	URTW_FEMR_FOR_8187B	0x1d4
	urtw_write16_m(sc, URTW_FEMR_FOR_8187B, 0xffff);

	/* led type */
	urtw_read8_m(sc, URTW_CONFIG1, &data8);
	data8 = (data8 & 0x3f) | 0x80;
	urtw_write8_m(sc, URTW_CONFIG1, data8);

	/* applying MAC address again.  */
	macaddr = vap ? vap->iv_myaddr : ic->ic_macaddr;
	error = urtw_set_macaddr(sc, macaddr);
	if (error)
		goto fail;

	error = urtw_set_mode(sc, URTW_EPROM_CMD_NORMAL);
	if (error)
		goto fail;

	urtw_write8_m(sc, URTW_WPA_CONFIG, 0);

	/*
	 * MAC configuration
	 */
	for (i = 0; i < nitems(urtw_8225v2b_rf_part1); i++)
		urtw_write8_m(sc, urtw_8225v2b_rf_part1[i].reg,
		    urtw_8225v2b_rf_part1[i].val);
	urtw_write16_m(sc, URTW_TID_AC_MAP, 0xfa50);
	urtw_write16_m(sc, URTW_INT_MIG, 0x0000);
	urtw_write32_m(sc, 0x1f0, 0);
	urtw_write32_m(sc, 0x1f4, 0);
	urtw_write8_m(sc, 0x1f8, 0);
	urtw_write32_m(sc, URTW_RF_TIMING, 0x4001);

#define	URTW_RFSW_CTRL	0x272
	urtw_write16_m(sc, URTW_RFSW_CTRL, 0x569a);

	/*
	 * initialize PHY
	 */
	error = urtw_set_mode(sc, URTW_EPROM_CMD_CONFIG);
	if (error)
		goto fail;
	urtw_read8_m(sc, URTW_CONFIG3, &data8);
	urtw_write8_m(sc, URTW_CONFIG3,
	    data8 | URTW_CONFIG3_ANAPARAM_WRITE);

	error = urtw_set_mode(sc, URTW_EPROM_CMD_NORMAL);
	if (error)
		goto fail;

	/* setup RFE initial timing */
	urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, 0x0480);
	urtw_write16_m(sc, URTW_RF_PINS_SELECT, 0x2488);
	urtw_write16_m(sc, URTW_RF_PINS_ENABLE, 0x1fff);
	usb_pause_mtx(&sc->sc_mtx, 1100);

	for (i = 0; i < nitems(urtw_8225v2b_rf_part0); i++) {
		urtw_8225_write(sc, urtw_8225v2b_rf_part0[i].reg,
		    urtw_8225v2b_rf_part0[i].val);
		usb_pause_mtx(&sc->sc_mtx, 1);
	}
	urtw_8225_write(sc, 0x00, 0x01b7);

	for (i = 0; i < 95; i++) {
		urtw_8225_write(sc, URTW_8225_ADDR_1_MAGIC, (uint8_t)(i + 1));
		usb_pause_mtx(&sc->sc_mtx, 1);
		urtw_8225_write(sc, URTW_8225_ADDR_2_MAGIC,
		    urtw_8225v2b_rxgain[i]);
		usb_pause_mtx(&sc->sc_mtx, 1);
	}

	urtw_8225_write(sc, URTW_8225_ADDR_3_MAGIC, 0x080);
	usb_pause_mtx(&sc->sc_mtx, 1);
	urtw_8225_write(sc, URTW_8225_ADDR_5_MAGIC, 0x004);
	usb_pause_mtx(&sc->sc_mtx, 1);
	urtw_8225_write(sc, URTW_8225_ADDR_0_MAGIC, 0x0b7);
	usb_pause_mtx(&sc->sc_mtx, 1);
	usb_pause_mtx(&sc->sc_mtx, 3000);
	urtw_8225_write(sc, URTW_8225_ADDR_2_MAGIC, 0xc4d);
	usb_pause_mtx(&sc->sc_mtx, 2000);
	urtw_8225_write(sc, URTW_8225_ADDR_2_MAGIC, 0x44d);
	usb_pause_mtx(&sc->sc_mtx, 1);
	urtw_8225_write(sc, URTW_8225_ADDR_0_MAGIC, 0x2bf);
	usb_pause_mtx(&sc->sc_mtx, 1);

	urtw_write8_m(sc, URTW_TX_GAIN_CCK, 0x03);
	urtw_write8_m(sc, URTW_TX_GAIN_OFDM, 0x07);
	urtw_write8_m(sc, URTW_TX_ANTENNA, 0x03);

	urtw_8187_write_phy_ofdm(sc, 0x80, 0x12);
	for (i = 0; i < 128; i++) {
		uint32_t addr, data;

		data = (urtw_8225z2_agc[i] << 8) | 0x0000008f;
		addr = ((i + 0x80) << 8) | 0x0000008e;

		urtw_8187_write_phy_ofdm(sc, data & 0x7f, (data >> 8) & 0xff);
		urtw_8187_write_phy_ofdm(sc, addr & 0x7f, (addr >> 8) & 0xff);
		urtw_8187_write_phy_ofdm(sc, 0x0e, 0x00);
	}
	urtw_8187_write_phy_ofdm(sc, 0x80, 0x10);

	for (i = 0; i < nitems(urtw_8225v2b_rf_part2); i++)
		urtw_8187_write_phy_ofdm(sc, i, urtw_8225v2b_rf_part2[i].val);

	urtw_write32_m(sc, URTW_8187B_AC_VO, (7 << 12) | (3 << 8) | 0x1c);
	urtw_write32_m(sc, URTW_8187B_AC_VI, (7 << 12) | (3 << 8) | 0x1c);
	urtw_write32_m(sc, URTW_8187B_AC_BE, (7 << 12) | (3 << 8) | 0x1c);
	urtw_write32_m(sc, URTW_8187B_AC_BK, (7 << 12) | (3 << 8) | 0x1c);

	urtw_8187_write_phy_ofdm(sc, 0x97, 0x46);
	urtw_8187_write_phy_ofdm(sc, 0xa4, 0xb6);
	urtw_8187_write_phy_ofdm(sc, 0x85, 0xfc);
	urtw_8187_write_phy_cck(sc, 0xc1, 0x88);

fail:
	return (error);
}