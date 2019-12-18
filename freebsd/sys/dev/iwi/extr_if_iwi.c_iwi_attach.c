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
struct TYPE_6__ {int /*<<< orphan*/  wr_ihdr; } ;
struct TYPE_5__ {int /*<<< orphan*/  wt_ihdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  wme_update; } ;
struct ieee80211com {int ic_caps; int* ic_macaddr; int /*<<< orphan*/  (* ic_getradiocaps ) (struct ieee80211com*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ic_parent; int /*<<< orphan*/  ic_transmit; int /*<<< orphan*/  ic_ioctl; int /*<<< orphan*/  ic_vap_delete; int /*<<< orphan*/  ic_vap_create; TYPE_1__ ic_wme; int /*<<< orphan*/  ic_scan_mindwell; int /*<<< orphan*/  ic_scan_curchan; int /*<<< orphan*/  ic_set_channel; int /*<<< orphan*/  ic_scan_end; int /*<<< orphan*/  ic_scan_start; int /*<<< orphan*/  ic_raw_xmit; int /*<<< orphan*/  ic_node_free; int /*<<< orphan*/  ic_node_alloc; int /*<<< orphan*/  ic_channels; int /*<<< orphan*/  ic_nchans; int /*<<< orphan*/  ic_phytype; int /*<<< orphan*/  ic_opmode; int /*<<< orphan*/  ic_name; struct iwi_softc* ic_softc; } ;
struct iwi_softc {int /*<<< orphan*/  sc_ih; int /*<<< orphan*/ * irq; TYPE_3__ sc_rxtap; TYPE_2__ sc_txtap; int /*<<< orphan*/  sc_node_free; int /*<<< orphan*/  rxq; int /*<<< orphan*/ * txq; int /*<<< orphan*/  cmdq; int /*<<< orphan*/ * mem; int /*<<< orphan*/  sc_sh; int /*<<< orphan*/  sc_st; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_rftimer; int /*<<< orphan*/  sc_wdtimer; int /*<<< orphan*/  sc_monitortask; int /*<<< orphan*/  sc_disassoctask; int /*<<< orphan*/  sc_restarttask; int /*<<< orphan*/  sc_radiofftask; int /*<<< orphan*/  sc_radiontask; int /*<<< orphan*/  sc_unr; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_ledevent; int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IEEE80211_CHAN_MAX ; 
 int IEEE80211_C_BGSCAN ; 
 int IEEE80211_C_IBSS ; 
 int IEEE80211_C_MONITOR ; 
 int IEEE80211_C_PMGT ; 
 int IEEE80211_C_SHPREAMBLE ; 
 int IEEE80211_C_STA ; 
 int IEEE80211_C_WME ; 
 int IEEE80211_C_WPA ; 
 int /*<<< orphan*/  IEEE80211_M_STA ; 
 int /*<<< orphan*/  IEEE80211_T_OFDM ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  IWI_CMD_RING_COUNT ; 
 scalar_t__ IWI_CSR_TX1_RIDX ; 
 scalar_t__ IWI_CSR_TX1_WIDX ; 
 scalar_t__ IWI_EEPROM_MAC ; 
 int /*<<< orphan*/  IWI_LOCK_INIT (struct iwi_softc*) ; 
 scalar_t__ IWI_MAX_IBSSNODE ; 
 int /*<<< orphan*/  IWI_RX_RADIOTAP_PRESENT ; 
 int /*<<< orphan*/  IWI_RX_RING_COUNT ; 
 int /*<<< orphan*/  IWI_TX_RADIOTAP_PRESENT ; 
 int /*<<< orphan*/  IWI_TX_RING_COUNT ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwi_softc*) ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct iwi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct iwi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ieee80211_announce (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_ifattach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_radiotap_attach (struct ieee80211com*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 scalar_t__ iwi_alloc_cmd_ring (struct iwi_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iwi_alloc_rx_ring (struct iwi_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwi_alloc_tx_ring (struct iwi_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iwi_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwi_disassoc ; 
 int /*<<< orphan*/  iwi_getradiocaps (struct ieee80211com*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwi_intr ; 
 int /*<<< orphan*/  iwi_ioctl ; 
 int /*<<< orphan*/  iwi_ledattach (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_monitor_scan ; 
 int /*<<< orphan*/  iwi_node_alloc ; 
 int /*<<< orphan*/  iwi_node_free ; 
 int /*<<< orphan*/  iwi_parent ; 
 int /*<<< orphan*/  iwi_radio_off ; 
 int /*<<< orphan*/  iwi_radio_on ; 
 int /*<<< orphan*/  iwi_raw_xmit ; 
 int iwi_read_prom_word (struct iwi_softc*,scalar_t__) ; 
 scalar_t__ iwi_reset (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_restart ; 
 int /*<<< orphan*/  iwi_scan_curchan ; 
 int /*<<< orphan*/  iwi_scan_end ; 
 int /*<<< orphan*/  iwi_scan_mindwell ; 
 int /*<<< orphan*/  iwi_scan_start ; 
 int /*<<< orphan*/  iwi_set_channel ; 
 int /*<<< orphan*/  iwi_sysctlattach (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_transmit ; 
 int /*<<< orphan*/  iwi_vap_create ; 
 int /*<<< orphan*/  iwi_vap_delete ; 
 int /*<<< orphan*/  iwi_wme_init (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_wme_update ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_unrhdr (int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static int
iwi_attach(device_t dev)
{
	struct iwi_softc *sc = device_get_softc(dev);
	struct ieee80211com *ic = &sc->sc_ic;
	uint16_t val;
	int i, error;

	sc->sc_dev = dev;
	sc->sc_ledevent = ticks;

	IWI_LOCK_INIT(sc);
	mbufq_init(&sc->sc_snd, ifqmaxlen);

	sc->sc_unr = new_unrhdr(1, IWI_MAX_IBSSNODE-1, &sc->sc_mtx);

	TASK_INIT(&sc->sc_radiontask, 0, iwi_radio_on, sc);
	TASK_INIT(&sc->sc_radiofftask, 0, iwi_radio_off, sc);
	TASK_INIT(&sc->sc_restarttask, 0, iwi_restart, sc);
	TASK_INIT(&sc->sc_disassoctask, 0, iwi_disassoc, sc);
	TASK_INIT(&sc->sc_monitortask, 0, iwi_monitor_scan, sc);

	callout_init_mtx(&sc->sc_wdtimer, &sc->sc_mtx, 0);
	callout_init_mtx(&sc->sc_rftimer, &sc->sc_mtx, 0);

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
		goto fail;
	}

	if (iwi_reset(sc) != 0) {
		device_printf(dev, "could not reset adapter\n");
		goto fail;
	}

	/*
	 * Allocate rings.
	 */
	if (iwi_alloc_cmd_ring(sc, &sc->cmdq, IWI_CMD_RING_COUNT) != 0) {
		device_printf(dev, "could not allocate Cmd ring\n");
		goto fail;
	}

	for (i = 0; i < 4; i++) {
		error = iwi_alloc_tx_ring(sc, &sc->txq[i], IWI_TX_RING_COUNT,
		    IWI_CSR_TX1_RIDX + i * 4,
		    IWI_CSR_TX1_WIDX + i * 4);
		if (error != 0) {
			device_printf(dev, "could not allocate Tx ring %d\n",
				i+i);
			goto fail;
		}
	}

	if (iwi_alloc_rx_ring(sc, &sc->rxq, IWI_RX_RING_COUNT) != 0) {
		device_printf(dev, "could not allocate Rx ring\n");
		goto fail;
	}

	iwi_wme_init(sc);

	ic->ic_softc = sc;
	ic->ic_name = device_get_nameunit(dev);
	ic->ic_opmode = IEEE80211_M_STA;
	ic->ic_phytype = IEEE80211_T_OFDM; /* not only, but not used */

	/* set device capabilities */
	ic->ic_caps =
	      IEEE80211_C_STA		/* station mode supported */
	    | IEEE80211_C_IBSS		/* IBSS mode supported */
	    | IEEE80211_C_MONITOR	/* monitor mode supported */
	    | IEEE80211_C_PMGT		/* power save supported */
	    | IEEE80211_C_SHPREAMBLE	/* short preamble supported */
	    | IEEE80211_C_WPA		/* 802.11i */
	    | IEEE80211_C_WME		/* 802.11e */
#if 0
	    | IEEE80211_C_BGSCAN	/* capable of bg scanning */
#endif
	    ;

	/* read MAC address from EEPROM */
	val = iwi_read_prom_word(sc, IWI_EEPROM_MAC + 0);
	ic->ic_macaddr[0] = val & 0xff;
	ic->ic_macaddr[1] = val >> 8;
	val = iwi_read_prom_word(sc, IWI_EEPROM_MAC + 1);
	ic->ic_macaddr[2] = val & 0xff;
	ic->ic_macaddr[3] = val >> 8;
	val = iwi_read_prom_word(sc, IWI_EEPROM_MAC + 2);
	ic->ic_macaddr[4] = val & 0xff;
	ic->ic_macaddr[5] = val >> 8;

	iwi_getradiocaps(ic, IEEE80211_CHAN_MAX, &ic->ic_nchans,
	    ic->ic_channels);

	ieee80211_ifattach(ic);
	/* override default methods */
	ic->ic_node_alloc = iwi_node_alloc;
	sc->sc_node_free = ic->ic_node_free;
	ic->ic_node_free = iwi_node_free;
	ic->ic_raw_xmit = iwi_raw_xmit;
	ic->ic_scan_start = iwi_scan_start;
	ic->ic_scan_end = iwi_scan_end;
	ic->ic_set_channel = iwi_set_channel;
	ic->ic_scan_curchan = iwi_scan_curchan;
	ic->ic_scan_mindwell = iwi_scan_mindwell;
	ic->ic_wme.wme_update = iwi_wme_update;

	ic->ic_vap_create = iwi_vap_create;
	ic->ic_vap_delete = iwi_vap_delete;
	ic->ic_ioctl = iwi_ioctl;
	ic->ic_transmit = iwi_transmit;
	ic->ic_parent = iwi_parent;
	ic->ic_getradiocaps = iwi_getradiocaps;

	ieee80211_radiotap_attach(ic,
	    &sc->sc_txtap.wt_ihdr, sizeof(sc->sc_txtap),
		IWI_TX_RADIOTAP_PRESENT,
	    &sc->sc_rxtap.wr_ihdr, sizeof(sc->sc_rxtap),
		IWI_RX_RADIOTAP_PRESENT);

	iwi_sysctlattach(sc);
	iwi_ledattach(sc);

	/*
	 * Hook our interrupt after all initialization is complete.
	 */
	error = bus_setup_intr(dev, sc->irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, iwi_intr, sc, &sc->sc_ih);
	if (error != 0) {
		device_printf(dev, "could not set up interrupt\n");
		goto fail;
	}

	if (bootverbose)
		ieee80211_announce(ic);

	return 0;
fail:
	/* XXX fix */
	iwi_detach(dev);
	return ENXIO;
}