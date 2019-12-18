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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  wr_ihdr; } ;
struct TYPE_5__ {int /*<<< orphan*/  wt_ihdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  wme_update; } ;
struct ieee80211com {int ic_caps; int /*<<< orphan*/  ic_vap_delete; int /*<<< orphan*/  ic_vap_create; int /*<<< orphan*/  ic_parent; int /*<<< orphan*/  ic_transmit; int /*<<< orphan*/  ic_raw_xmit; int /*<<< orphan*/  ic_update_promisc; int /*<<< orphan*/  ic_updateslot; int /*<<< orphan*/  ic_set_channel; int /*<<< orphan*/  (* ic_getradiocaps ) (struct ieee80211com*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ic_scan_end; int /*<<< orphan*/  ic_scan_start; TYPE_1__ ic_wme; int /*<<< orphan*/  ic_channels; int /*<<< orphan*/  ic_nchans; int /*<<< orphan*/  ic_phytype; int /*<<< orphan*/  ic_opmode; int /*<<< orphan*/  ic_name; struct rt2661_softc* ic_softc; int /*<<< orphan*/  ic_macaddr; } ;
struct rt2661_softc {int sc_id; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * txq; int /*<<< orphan*/  mgtq; int /*<<< orphan*/  sc_debug; TYPE_3__ sc_rxtap; TYPE_2__ sc_txtap; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  rxq; int /*<<< orphan*/  rf_rev; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  watchdog_ch; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int /*<<< orphan*/  IEEE80211_CHAN_MAX ; 
 int IEEE80211_C_AHDEMO ; 
 int IEEE80211_C_BGSCAN ; 
 int IEEE80211_C_HOSTAP ; 
 int IEEE80211_C_IBSS ; 
 int IEEE80211_C_MBSS ; 
 int IEEE80211_C_MONITOR ; 
 int IEEE80211_C_SHPREAMBLE ; 
 int IEEE80211_C_SHSLOT ; 
 int IEEE80211_C_STA ; 
 int IEEE80211_C_TXFRAG ; 
 int IEEE80211_C_WDS ; 
 int IEEE80211_C_WME ; 
 int IEEE80211_C_WPA ; 
 int /*<<< orphan*/  IEEE80211_M_STA ; 
 int /*<<< orphan*/  IEEE80211_T_OFDM ; 
 int MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int MTX_RECURSE ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  RAL_READ (struct rt2661_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT2661_MAC_CSR0 ; 
 int /*<<< orphan*/  RT2661_MGT_RING_COUNT ; 
 int /*<<< orphan*/  RT2661_RX_RADIOTAP_PRESENT ; 
 int /*<<< orphan*/  RT2661_RX_RING_COUNT ; 
 int /*<<< orphan*/  RT2661_TX_RADIOTAP_PRESENT ; 
 int /*<<< orphan*/  RT2661_TX_RING_COUNT ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct rt2661_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ieee80211_announce (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_ifattach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_radiotap_attach (struct ieee80211com*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rt2661_alloc_rx_ring (struct rt2661_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rt2661_alloc_tx_ring (struct rt2661_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2661_free_tx_ring (struct rt2661_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2661_get_rf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2661_getradiocaps (struct ieee80211com*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2661_parent ; 
 int /*<<< orphan*/  rt2661_raw_xmit ; 
 int /*<<< orphan*/  rt2661_read_eeprom (struct rt2661_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2661_scan_end ; 
 int /*<<< orphan*/  rt2661_scan_start ; 
 int /*<<< orphan*/  rt2661_set_channel ; 
 int /*<<< orphan*/  rt2661_transmit ; 
 int /*<<< orphan*/  rt2661_update_promisc ; 
 int /*<<< orphan*/  rt2661_update_slot ; 
 int /*<<< orphan*/  rt2661_vap_create ; 
 int /*<<< orphan*/  rt2661_vap_delete ; 
 int /*<<< orphan*/  rt2661_wme_update ; 

int
rt2661_attach(device_t dev, int id)
{
	struct rt2661_softc *sc = device_get_softc(dev);
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t val;
	int error, ac, ntries;

	sc->sc_id = id;
	sc->sc_dev = dev;

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF | MTX_RECURSE);

	callout_init_mtx(&sc->watchdog_ch, &sc->sc_mtx, 0);
	mbufq_init(&sc->sc_snd, ifqmaxlen);

	/* wait for NIC to initialize */
	for (ntries = 0; ntries < 1000; ntries++) {
		if ((val = RAL_READ(sc, RT2661_MAC_CSR0)) != 0)
			break;
		DELAY(1000);
	}
	if (ntries == 1000) {
		device_printf(sc->sc_dev,
		    "timeout waiting for NIC to initialize\n");
		error = EIO;
		goto fail1;
	}

	/* retrieve RF rev. no and various other things from EEPROM */
	rt2661_read_eeprom(sc, ic->ic_macaddr);

	device_printf(dev, "MAC/BBP RT%X, RF %s\n", val,
	    rt2661_get_rf(sc->rf_rev));

	/*
	 * Allocate Tx and Rx rings.
	 */
	for (ac = 0; ac < 4; ac++) {
		error = rt2661_alloc_tx_ring(sc, &sc->txq[ac],
		    RT2661_TX_RING_COUNT);
		if (error != 0) {
			device_printf(sc->sc_dev,
			    "could not allocate Tx ring %d\n", ac);
			goto fail2;
		}
	}

	error = rt2661_alloc_tx_ring(sc, &sc->mgtq, RT2661_MGT_RING_COUNT);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not allocate Mgt ring\n");
		goto fail2;
	}

	error = rt2661_alloc_rx_ring(sc, &sc->rxq, RT2661_RX_RING_COUNT);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not allocate Rx ring\n");
		goto fail3;
	}

	ic->ic_softc = sc;
	ic->ic_name = device_get_nameunit(dev);
	ic->ic_opmode = IEEE80211_M_STA;
	ic->ic_phytype = IEEE80211_T_OFDM; /* not only, but not used */

	/* set device capabilities */
	ic->ic_caps =
		  IEEE80211_C_STA		/* station mode */
		| IEEE80211_C_IBSS		/* ibss, nee adhoc, mode */
		| IEEE80211_C_HOSTAP		/* hostap mode */
		| IEEE80211_C_MONITOR		/* monitor mode */
		| IEEE80211_C_AHDEMO		/* adhoc demo mode */
		| IEEE80211_C_WDS		/* 4-address traffic works */
		| IEEE80211_C_MBSS		/* mesh point link mode */
		| IEEE80211_C_SHPREAMBLE	/* short preamble supported */
		| IEEE80211_C_SHSLOT		/* short slot time supported */
		| IEEE80211_C_WPA		/* capable of WPA1+WPA2 */
		| IEEE80211_C_BGSCAN		/* capable of bg scanning */
#ifdef notyet
		| IEEE80211_C_TXFRAG		/* handle tx frags */
		| IEEE80211_C_WME		/* 802.11e */
#endif
		;

	rt2661_getradiocaps(ic, IEEE80211_CHAN_MAX, &ic->ic_nchans,
	    ic->ic_channels);

	ieee80211_ifattach(ic);
#if 0
	ic->ic_wme.wme_update = rt2661_wme_update;
#endif
	ic->ic_scan_start = rt2661_scan_start;
	ic->ic_scan_end = rt2661_scan_end;
	ic->ic_getradiocaps = rt2661_getradiocaps;
	ic->ic_set_channel = rt2661_set_channel;
	ic->ic_updateslot = rt2661_update_slot;
	ic->ic_update_promisc = rt2661_update_promisc;
	ic->ic_raw_xmit = rt2661_raw_xmit;
	ic->ic_transmit = rt2661_transmit;
	ic->ic_parent = rt2661_parent;
	ic->ic_vap_create = rt2661_vap_create;
	ic->ic_vap_delete = rt2661_vap_delete;

	ieee80211_radiotap_attach(ic,
	    &sc->sc_txtap.wt_ihdr, sizeof(sc->sc_txtap),
		RT2661_TX_RADIOTAP_PRESENT,
	    &sc->sc_rxtap.wr_ihdr, sizeof(sc->sc_rxtap),
		RT2661_RX_RADIOTAP_PRESENT);

#ifdef RAL_DEBUG
	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "debug", CTLFLAG_RW, &sc->sc_debug, 0, "debug msgs");
#endif
	if (bootverbose)
		ieee80211_announce(ic);

	return 0;

fail3:	rt2661_free_tx_ring(sc, &sc->mgtq);
fail2:	while (--ac >= 0)
		rt2661_free_tx_ring(sc, &sc->txq[ac]);
fail1:	mtx_destroy(&sc->sc_mtx);
	return error;
}