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
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  wr_ihdr; } ;
struct TYPE_3__ {int /*<<< orphan*/  wt_ihdr; } ;
struct ieee80211com {int ic_caps; int* ic_macaddr; int /*<<< orphan*/  ic_parent; int /*<<< orphan*/  ic_transmit; int /*<<< orphan*/  ic_vap_delete; int /*<<< orphan*/  ic_vap_create; int /*<<< orphan*/  ic_raw_xmit; int /*<<< orphan*/  ic_scan_mindwell; int /*<<< orphan*/  ic_scan_curchan; int /*<<< orphan*/  ic_set_channel; int /*<<< orphan*/  (* ic_getradiocaps ) (struct ieee80211com*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ic_scan_end; int /*<<< orphan*/  ic_scan_start; int /*<<< orphan*/  ic_channels; int /*<<< orphan*/  ic_nchans; int /*<<< orphan*/  ic_phytype; int /*<<< orphan*/  ic_opmode; int /*<<< orphan*/  ic_name; struct ipw_softc* ic_softc; } ;
struct ipw_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * mem; int /*<<< orphan*/ * irq; int /*<<< orphan*/  sc_ih; TYPE_2__ sc_rxtap; TYPE_1__ sc_txtap; int /*<<< orphan*/  flags; int /*<<< orphan*/  chanmask; int /*<<< orphan*/  sc_sh; int /*<<< orphan*/  sc_st; int /*<<< orphan*/  sc_wdtimer; int /*<<< orphan*/  sc_init_task; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int CTLTYPE_OPAQUE ; 
 int ENXIO ; 
 int /*<<< orphan*/  IEEE80211_CHAN_MAX ; 
 int IEEE80211_C_IBSS ; 
 int IEEE80211_C_MONITOR ; 
 int IEEE80211_C_PMGT ; 
 int IEEE80211_C_SHPREAMBLE ; 
 int IEEE80211_C_STA ; 
 int IEEE80211_C_WPA ; 
 int /*<<< orphan*/  IEEE80211_M_STA ; 
 int /*<<< orphan*/  IEEE80211_T_DS ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 scalar_t__ IPW_EEPROM_MAC ; 
 scalar_t__ IPW_EEPROM_RADIO ; 
 int /*<<< orphan*/  IPW_FLAG_HAS_RADIO_SWITCH ; 
 int /*<<< orphan*/  IPW_RX_RADIOTAP_PRESENT ; 
 int /*<<< orphan*/  IPW_TX_RADIOTAP_PRESENT ; 
 int MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int MTX_RECURSE ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct ipw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ipw_softc*) ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ipw_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ipw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_announce (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_ifattach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_radiotap_attach (struct ieee80211com*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 scalar_t__ ipw_dma_alloc (struct ipw_softc*) ; 
 int /*<<< orphan*/  ipw_getradiocaps (struct ieee80211com*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_init_task ; 
 int /*<<< orphan*/  ipw_intr ; 
 int /*<<< orphan*/  ipw_parent ; 
 int /*<<< orphan*/  ipw_raw_xmit ; 
 int /*<<< orphan*/  ipw_read_chanmask (struct ipw_softc*) ; 
 int ipw_read_prom_word (struct ipw_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ipw_release (struct ipw_softc*) ; 
 scalar_t__ ipw_reset (struct ipw_softc*) ; 
 int /*<<< orphan*/  ipw_scan_curchan ; 
 int /*<<< orphan*/  ipw_scan_end ; 
 int /*<<< orphan*/  ipw_scan_mindwell ; 
 int /*<<< orphan*/  ipw_scan_start ; 
 int /*<<< orphan*/  ipw_set_channel ; 
 int /*<<< orphan*/  ipw_sysctl_radio ; 
 int /*<<< orphan*/  ipw_sysctl_stats ; 
 int /*<<< orphan*/  ipw_transmit ; 
 int /*<<< orphan*/  ipw_vap_create ; 
 int /*<<< orphan*/  ipw_vap_delete ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipw_attach(device_t dev)
{
	struct ipw_softc *sc = device_get_softc(dev);
	struct ieee80211com *ic = &sc->sc_ic;
	uint16_t val;
	int error, i;

	sc->sc_dev = dev;

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF | MTX_RECURSE);
	mbufq_init(&sc->sc_snd, ifqmaxlen);
	TASK_INIT(&sc->sc_init_task, 0, ipw_init_task, sc);
	callout_init_mtx(&sc->sc_wdtimer, &sc->sc_mtx, 0);

	pci_write_config(dev, 0x41, 0, 1);

	/* enable bus-mastering */
	pci_enable_busmaster(dev);

	i = PCIR_BAR(0);
	sc->mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &i, RF_ACTIVE);
	if (sc->mem == NULL) {
		device_printf(dev, "could not allocate memory resource\n");
		goto fail;
	}

	sc->sc_st = rman_get_bustag(sc->mem);
	sc->sc_sh = rman_get_bushandle(sc->mem);

	i = 0;
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &i,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->irq == NULL) {
		device_printf(dev, "could not allocate interrupt resource\n");
		goto fail1;
	}

	if (ipw_reset(sc) != 0) {
		device_printf(dev, "could not reset adapter\n");
		goto fail2;
	}

	if (ipw_dma_alloc(sc) != 0) {
		device_printf(dev, "could not allocate DMA resources\n");
		goto fail2;
	}

	ic->ic_softc = sc;
	ic->ic_name = device_get_nameunit(dev);
	ic->ic_opmode = IEEE80211_M_STA;
	ic->ic_phytype = IEEE80211_T_DS;

	/* set device capabilities */
	ic->ic_caps =
		  IEEE80211_C_STA		/* station mode supported */
		| IEEE80211_C_IBSS		/* IBSS mode supported */
		| IEEE80211_C_MONITOR		/* monitor mode supported */
		| IEEE80211_C_PMGT		/* power save supported */
		| IEEE80211_C_SHPREAMBLE	/* short preamble supported */
		| IEEE80211_C_WPA		/* 802.11i supported */
		;

	/* read MAC address from EEPROM */
	val = ipw_read_prom_word(sc, IPW_EEPROM_MAC + 0);
	ic->ic_macaddr[0] = val >> 8;
	ic->ic_macaddr[1] = val & 0xff;
	val = ipw_read_prom_word(sc, IPW_EEPROM_MAC + 1);
	ic->ic_macaddr[2] = val >> 8;
	ic->ic_macaddr[3] = val & 0xff;
	val = ipw_read_prom_word(sc, IPW_EEPROM_MAC + 2);
	ic->ic_macaddr[4] = val >> 8;
	ic->ic_macaddr[5] = val & 0xff;

	sc->chanmask = ipw_read_chanmask(sc);
	ipw_getradiocaps(ic, IEEE80211_CHAN_MAX, &ic->ic_nchans,
	    ic->ic_channels);

	/* check support for radio transmitter switch in EEPROM */
	if (!(ipw_read_prom_word(sc, IPW_EEPROM_RADIO) & 8))
		sc->flags |= IPW_FLAG_HAS_RADIO_SWITCH;

	ieee80211_ifattach(ic);
	ic->ic_scan_start = ipw_scan_start;
	ic->ic_scan_end = ipw_scan_end;
	ic->ic_getradiocaps = ipw_getradiocaps;
	ic->ic_set_channel = ipw_set_channel;
	ic->ic_scan_curchan = ipw_scan_curchan;
	ic->ic_scan_mindwell = ipw_scan_mindwell;
	ic->ic_raw_xmit = ipw_raw_xmit;
	ic->ic_vap_create = ipw_vap_create;
	ic->ic_vap_delete = ipw_vap_delete;
	ic->ic_transmit = ipw_transmit;
	ic->ic_parent = ipw_parent;

	ieee80211_radiotap_attach(ic,
	    &sc->sc_txtap.wt_ihdr, sizeof(sc->sc_txtap),
		IPW_TX_RADIOTAP_PRESENT,
	    &sc->sc_rxtap.wr_ihdr, sizeof(sc->sc_rxtap),
		IPW_RX_RADIOTAP_PRESENT);

	/*
	 * Add a few sysctl knobs.
	 */
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO, "radio",
	    CTLTYPE_INT | CTLFLAG_RD, sc, 0, ipw_sysctl_radio, "I",
	    "radio transmitter switch state (0=off, 1=on)");

	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO, "stats",
	    CTLTYPE_OPAQUE | CTLFLAG_RD, sc, 0, ipw_sysctl_stats, "S",
	    "statistics");

	/*
	 * Hook our interrupt after all initialization is complete.
	 */
	error = bus_setup_intr(dev, sc->irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, ipw_intr, sc, &sc->sc_ih);
	if (error != 0) {
		device_printf(dev, "could not set up interrupt\n");
		goto fail3;
	}

	if (bootverbose)
		ieee80211_announce(ic);

	return 0;
fail3:
	ipw_release(sc);
fail2:
	bus_release_resource(dev, SYS_RES_IRQ, rman_get_rid(sc->irq), sc->irq);
fail1:
	bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(sc->mem),
	    sc->mem);
fail:
	mtx_destroy(&sc->sc_mtx);
	return ENXIO;
}