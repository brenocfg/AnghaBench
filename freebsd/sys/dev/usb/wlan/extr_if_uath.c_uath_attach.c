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
typedef  scalar_t__ usb_error_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_attach_arg {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {int /*<<< orphan*/  wr_ihdr; } ;
struct TYPE_5__ {int /*<<< orphan*/  wt_ihdr; } ;
struct TYPE_4__ {int analog5GhzRevision; int /*<<< orphan*/  regDomain; } ;
struct ieee80211com {int ic_caps; int /*<<< orphan*/  ic_parent; int /*<<< orphan*/  ic_transmit; int /*<<< orphan*/  ic_update_promisc; int /*<<< orphan*/  ic_update_mcast; int /*<<< orphan*/  ic_vap_delete; int /*<<< orphan*/  ic_vap_create; int /*<<< orphan*/  ic_set_channel; int /*<<< orphan*/  ic_scan_end; int /*<<< orphan*/  ic_scan_start; int /*<<< orphan*/  ic_raw_xmit; int /*<<< orphan*/  ic_opmode; int /*<<< orphan*/  ic_phytype; int /*<<< orphan*/  ic_name; struct uath_softc* ic_softc; int /*<<< orphan*/  ic_macaddr; } ;
struct uath_softc {int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_cmd; TYPE_3__ sc_rxtap; TYPE_2__ sc_txtap; TYPE_1__ sc_devcap; int /*<<< orphan*/  sc_dev; void* sc_tx_dma_buf; void* sc_cmd_dma_buf; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  watchdog_ch; int /*<<< orphan*/  stat_ch; int /*<<< orphan*/  sc_debug; int /*<<< orphan*/  sc_udev; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bands ;

/* Variables and functions */
 int IEEE80211_C_BGSCAN ; 
 int IEEE80211_C_MONITOR ; 
 int IEEE80211_C_SHPREAMBLE ; 
 int IEEE80211_C_SHSLOT ; 
 int IEEE80211_C_STA ; 
 int IEEE80211_C_TXFRAG ; 
 int IEEE80211_C_TXPMGT ; 
 int IEEE80211_C_WPA ; 
 int /*<<< orphan*/  IEEE80211_MODE_11A ; 
 int /*<<< orphan*/  IEEE80211_MODE_11B ; 
 int /*<<< orphan*/  IEEE80211_MODE_11G ; 
 int IEEE80211_MODE_BYTES ; 
 int /*<<< orphan*/  IEEE80211_M_STA ; 
 int /*<<< orphan*/  IEEE80211_T_OFDM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 size_t UATH_BULK_TX ; 
 int /*<<< orphan*/  UATH_IFACE_INDEX ; 
 size_t UATH_INTR_TX ; 
 int /*<<< orphan*/  UATH_LOCK (struct uath_softc*) ; 
 int /*<<< orphan*/  UATH_N_XFERS ; 
 int /*<<< orphan*/  UATH_RX_RADIOTAP_PRESENT ; 
 int /*<<< orphan*/  UATH_TX_RADIOTAP_PRESENT ; 
 int /*<<< orphan*/  UATH_UNLOCK (struct uath_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct uath_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_announce (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_ifattach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_init_channels (struct ieee80211com*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_radiotap_attach (struct ieee80211com*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uath_alloc_cmd_list (struct uath_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ uath_alloc_rx_data_list (struct uath_softc*) ; 
 scalar_t__ uath_alloc_tx_data_list (struct uath_softc*) ; 
 int /*<<< orphan*/  uath_debug ; 
 int /*<<< orphan*/  uath_free_cmd_list (struct uath_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ uath_get_devcap (struct uath_softc*) ; 
 scalar_t__ uath_get_devstatus (struct uath_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ uath_host_available (struct uath_softc*) ; 
 int /*<<< orphan*/  uath_parent ; 
 int /*<<< orphan*/  uath_raw_xmit ; 
 int /*<<< orphan*/  uath_regdomain ; 
 int /*<<< orphan*/  uath_scan_end ; 
 int /*<<< orphan*/  uath_scan_start ; 
 int /*<<< orphan*/  uath_set_channel ; 
 int /*<<< orphan*/  uath_sysctl_node (struct uath_softc*) ; 
 int /*<<< orphan*/  uath_transmit ; 
 int /*<<< orphan*/  uath_update_mcast ; 
 int /*<<< orphan*/  uath_update_promisc ; 
 int /*<<< orphan*/  uath_usbconfig ; 
 int /*<<< orphan*/  uath_vap_create ; 
 int /*<<< orphan*/  uath_vap_delete ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 
 scalar_t__ usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* usbd_xfer_get_frame_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uath_attach(device_t dev)
{
	struct uath_softc *sc = device_get_softc(dev);
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct ieee80211com *ic = &sc->sc_ic;
	uint8_t bands[IEEE80211_MODE_BYTES];
	uint8_t iface_index = UATH_IFACE_INDEX;		/* XXX */
	usb_error_t error;

	sc->sc_dev = dev;
	sc->sc_udev = uaa->device;
#ifdef UATH_DEBUG
	sc->sc_debug = uath_debug;
#endif
	device_set_usb_desc(dev);

	/*
	 * Only post-firmware devices here.
	 */
	mtx_init(&sc->sc_mtx, device_get_nameunit(sc->sc_dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init(&sc->stat_ch, 0);
	callout_init_mtx(&sc->watchdog_ch, &sc->sc_mtx, 0);
	mbufq_init(&sc->sc_snd, ifqmaxlen);

	error = usbd_transfer_setup(uaa->device, &iface_index, sc->sc_xfer,
	    uath_usbconfig, UATH_N_XFERS, sc, &sc->sc_mtx);
	if (error) {
		device_printf(dev, "could not allocate USB transfers, "
		    "err=%s\n", usbd_errstr(error));
		goto fail;
	}

	sc->sc_cmd_dma_buf = 
	    usbd_xfer_get_frame_buffer(sc->sc_xfer[UATH_INTR_TX], 0);
	sc->sc_tx_dma_buf = 
	    usbd_xfer_get_frame_buffer(sc->sc_xfer[UATH_BULK_TX], 0);

	/*
	 * Setup buffers for firmware commands.
	 */
	error = uath_alloc_cmd_list(sc, sc->sc_cmd);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "could not allocate Tx command list\n");
		goto fail1;
	}

	/*
	 * We're now ready to send+receive firmware commands.
	 */
	UATH_LOCK(sc);
	error = uath_host_available(sc);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not initialize adapter\n");
		goto fail2;
	}
	error = uath_get_devcap(sc);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "could not get device capabilities\n");
		goto fail2;
	}
	UATH_UNLOCK(sc);

	/* Create device sysctl node. */
	uath_sysctl_node(sc);

	UATH_LOCK(sc);
	error = uath_get_devstatus(sc, ic->ic_macaddr);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not get device status\n");
		goto fail2;
	}

	/*
	 * Allocate xfers for Rx/Tx data pipes.
	 */
	error = uath_alloc_rx_data_list(sc);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not allocate Rx data list\n");
		goto fail2;
	}
	error = uath_alloc_tx_data_list(sc);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not allocate Tx data list\n");
		goto fail2;
	}
	UATH_UNLOCK(sc);

	ic->ic_softc = sc;
	ic->ic_name = device_get_nameunit(dev);
	ic->ic_phytype = IEEE80211_T_OFDM;	/* not only, but not used */
	ic->ic_opmode = IEEE80211_M_STA;	/* default to BSS mode */

	/* set device capabilities */
	ic->ic_caps =
	    IEEE80211_C_STA |		/* station mode */
	    IEEE80211_C_MONITOR |	/* monitor mode supported */
	    IEEE80211_C_TXPMGT |	/* tx power management */
	    IEEE80211_C_SHPREAMBLE |	/* short preamble supported */
	    IEEE80211_C_SHSLOT |	/* short slot time supported */
	    IEEE80211_C_WPA |		/* 802.11i */
	    IEEE80211_C_BGSCAN |	/* capable of bg scanning */
	    IEEE80211_C_TXFRAG;		/* handle tx frags */

	/* put a regulatory domain to reveal informations.  */
	uath_regdomain = sc->sc_devcap.regDomain;

	memset(bands, 0, sizeof(bands));
	setbit(bands, IEEE80211_MODE_11B);
	setbit(bands, IEEE80211_MODE_11G);
	if ((sc->sc_devcap.analog5GhzRevision & 0xf0) == 0x30)
		setbit(bands, IEEE80211_MODE_11A);
	/* XXX turbo */
	ieee80211_init_channels(ic, NULL, bands);

	ieee80211_ifattach(ic);
	ic->ic_raw_xmit = uath_raw_xmit;
	ic->ic_scan_start = uath_scan_start;
	ic->ic_scan_end = uath_scan_end;
	ic->ic_set_channel = uath_set_channel;
	ic->ic_vap_create = uath_vap_create;
	ic->ic_vap_delete = uath_vap_delete;
	ic->ic_update_mcast = uath_update_mcast;
	ic->ic_update_promisc = uath_update_promisc;
	ic->ic_transmit = uath_transmit;
	ic->ic_parent = uath_parent;

	ieee80211_radiotap_attach(ic,
	    &sc->sc_txtap.wt_ihdr, sizeof(sc->sc_txtap),
		UATH_TX_RADIOTAP_PRESENT,
	    &sc->sc_rxtap.wr_ihdr, sizeof(sc->sc_rxtap),
		UATH_RX_RADIOTAP_PRESENT);

	if (bootverbose)
		ieee80211_announce(ic);

	return (0);

fail2:	UATH_UNLOCK(sc);
	uath_free_cmd_list(sc, sc->sc_cmd);
fail1:	usbd_transfer_unsetup(sc->sc_xfer, UATH_N_XFERS);
fail:
	return (error);
}