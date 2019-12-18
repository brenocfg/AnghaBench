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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct bwn_txgain {int tg_pad; int tg_gm; int tg_pga; int tg_dac; } ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_phy_lp {scalar_t__ plp_txpctlmode; int plp_txpwridx; int plp_tssinpt; int plp_tssiidx; int /*<<< orphan*/  plp_antenna; scalar_t__ plp_rccap; int /*<<< orphan*/  plp_chan; } ;
struct TYPE_2__ {int rev; struct bwn_phy_lp phy_lp; } ;
struct bwn_mac {TYPE_1__ mac_phy; struct bwn_softc* mac_sc; } ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_CHANNEL ; 
 scalar_t__ BWN_PHYLP_TXPCTL_OFF ; 
 scalar_t__ BWN_PHYLP_TXPCTL_ON_SW ; 
 int /*<<< orphan*/  BWN_PHY_RF_PWR_OVERRIDE ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_TX_GAIN_CTL_OVERRIDE_VAL ; 
 int /*<<< orphan*/  BWN_TAB_2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_TAB_4 (int,int) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bwn_phy_lp_bbinit (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_get_txpctlmode (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_rf_onoff (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_anafilter (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_antenna (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_bbmult (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_rccap (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_txgain (struct bwn_mac*,struct bwn_txgain*) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_txgain_dac (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_txgain_override (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_txgain_pa (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_txpctlmode (struct bwn_mac*,scalar_t__) ; 
 int /*<<< orphan*/  bwn_phy_lp_tblinit (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_txpctl_init (struct bwn_mac*) ; 
 int bwn_tab_read (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_tab_read_multi (struct bwn_mac*,int /*<<< orphan*/ ,unsigned int const,int*) ; 
 int /*<<< orphan*/  bwn_tab_write (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_tab_write_multi (struct bwn_mac*,int /*<<< orphan*/ ,unsigned int const,int*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bwn_phy_lp_bugfix(struct bwn_mac *mac)
{
	struct bwn_phy_lp *plp = &mac->mac_phy.phy_lp;
	struct bwn_softc *sc = mac->mac_sc;
	const unsigned int size = 256;
	struct bwn_txgain tg;
	uint32_t rxcomp, txgain, coeff, rfpwr, *tabs;
	uint16_t tssinpt, tssiidx, value[2];
	uint8_t mode;
	int8_t txpwridx;

	tabs = (uint32_t *)malloc(sizeof(uint32_t) * size, M_DEVBUF,
	    M_NOWAIT | M_ZERO);
	if (tabs == NULL) {
		device_printf(sc->sc_dev, "failed to allocate buffer.\n");
		return;
	}

	bwn_phy_lp_get_txpctlmode(mac);
	mode = plp->plp_txpctlmode;
	txpwridx = plp->plp_txpwridx;
	tssinpt = plp->plp_tssinpt;
	tssiidx = plp->plp_tssiidx;

	bwn_tab_read_multi(mac,
	    (mac->mac_phy.rev < 2) ? BWN_TAB_4(10, 0x140) :
	    BWN_TAB_4(7, 0x140), size, tabs);

	bwn_phy_lp_tblinit(mac);
	bwn_phy_lp_bbinit(mac);
	bwn_phy_lp_txpctl_init(mac);
	bwn_phy_lp_rf_onoff(mac, 1);
	bwn_phy_lp_set_txpctlmode(mac, BWN_PHYLP_TXPCTL_OFF);

	bwn_tab_write_multi(mac,
	    (mac->mac_phy.rev < 2) ? BWN_TAB_4(10, 0x140) :
	    BWN_TAB_4(7, 0x140), size, tabs);

	BWN_WRITE_2(mac, BWN_CHANNEL, plp->plp_chan);
	plp->plp_tssinpt = tssinpt;
	plp->plp_tssiidx = tssiidx;
	bwn_phy_lp_set_anafilter(mac, plp->plp_chan);
	if (txpwridx != -1) {
		/* set TX power by index */
		plp->plp_txpwridx = txpwridx;
		bwn_phy_lp_get_txpctlmode(mac);
		if (plp->plp_txpctlmode != BWN_PHYLP_TXPCTL_OFF)
			bwn_phy_lp_set_txpctlmode(mac, BWN_PHYLP_TXPCTL_ON_SW);
		if (mac->mac_phy.rev >= 2) {
			rxcomp = bwn_tab_read(mac,
			    BWN_TAB_4(7, txpwridx + 320));
			txgain = bwn_tab_read(mac,
			    BWN_TAB_4(7, txpwridx + 192));
			tg.tg_pad = (txgain >> 16) & 0xff;
			tg.tg_gm = txgain & 0xff;
			tg.tg_pga = (txgain >> 8) & 0xff;
			tg.tg_dac = (rxcomp >> 28) & 0xff;
			bwn_phy_lp_set_txgain(mac, &tg);
		} else {
			rxcomp = bwn_tab_read(mac,
			    BWN_TAB_4(10, txpwridx + 320));
			txgain = bwn_tab_read(mac,
			    BWN_TAB_4(10, txpwridx + 192));
			BWN_PHY_SETMASK(mac, BWN_PHY_TX_GAIN_CTL_OVERRIDE_VAL,
			    0xf800, (txgain >> 4) & 0x7fff);
			bwn_phy_lp_set_txgain_dac(mac, txgain & 0x7);
			bwn_phy_lp_set_txgain_pa(mac, (txgain >> 24) & 0x7f);
		}
		bwn_phy_lp_set_bbmult(mac, (rxcomp >> 20) & 0xff);

		/* set TX IQCC */
		value[0] = (rxcomp >> 10) & 0x3ff;
		value[1] = rxcomp & 0x3ff;
		bwn_tab_write_multi(mac, BWN_TAB_2(0, 80), 2, value);

		coeff = bwn_tab_read(mac,
		    (mac->mac_phy.rev >= 2) ? BWN_TAB_4(7, txpwridx + 448) :
		    BWN_TAB_4(10, txpwridx + 448));
		bwn_tab_write(mac, BWN_TAB_2(0, 85), coeff & 0xffff);
		if (mac->mac_phy.rev >= 2) {
			rfpwr = bwn_tab_read(mac,
			    BWN_TAB_4(7, txpwridx + 576));
			BWN_PHY_SETMASK(mac, BWN_PHY_RF_PWR_OVERRIDE, 0xff00,
			    rfpwr & 0xffff);
		}
		bwn_phy_lp_set_txgain_override(mac);
	}
	if (plp->plp_rccap)
		bwn_phy_lp_set_rccap(mac);
	bwn_phy_lp_set_antenna(mac, plp->plp_antenna);
	bwn_phy_lp_set_txpctlmode(mac, mode);
	free(tabs, M_DEVBUF);
}