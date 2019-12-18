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
typedef  scalar_t__ usb_error_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_config {int dummy; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  wr_ihdr; } ;
struct TYPE_3__ {int /*<<< orphan*/  wt_ihdr; } ;
struct ieee80211com {int ic_caps; int /*<<< orphan*/  ic_transmit; int /*<<< orphan*/  ic_parent; int /*<<< orphan*/  ic_update_mcast; int /*<<< orphan*/  ic_update_promisc; int /*<<< orphan*/  ic_vap_delete; int /*<<< orphan*/  ic_vap_create; int /*<<< orphan*/  ic_updateslot; int /*<<< orphan*/  ic_set_channel; int /*<<< orphan*/  (* ic_getradiocaps ) (struct ieee80211com*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ic_scan_end; int /*<<< orphan*/  ic_scan_start; int /*<<< orphan*/  ic_raw_xmit; int /*<<< orphan*/  ic_channels; int /*<<< orphan*/  ic_nchans; int /*<<< orphan*/  ic_opmode; int /*<<< orphan*/  ic_phytype; int /*<<< orphan*/  ic_name; struct urtw_softc* ic_softc; } ;
struct urtw_softc {int sc_flags; int /*<<< orphan*/ * sc_xfer; TYPE_2__ sc_rxtap; TYPE_1__ sc_txtap; int /*<<< orphan*/  sc_preamble_mode; int /*<<< orphan*/  sc_currate; int /*<<< orphan*/  sc_tx_retry; int /*<<< orphan*/  sc_rts_retry; int /*<<< orphan*/  sc_epromtype; void* sc_tx_dma_buf; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_watchdog_ch; int /*<<< orphan*/  sc_updateslot_task; int /*<<< orphan*/  sc_led_task; int /*<<< orphan*/  sc_led_ch; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_debug; int /*<<< orphan*/  sc_udev; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IEEE80211_CHAN_MAX ; 
 int IEEE80211_C_BGSCAN ; 
 int IEEE80211_C_MONITOR ; 
 int IEEE80211_C_SHPREAMBLE ; 
 int IEEE80211_C_SHSLOT ; 
 int IEEE80211_C_STA ; 
 int IEEE80211_C_TXPMGT ; 
 int IEEE80211_C_WPA ; 
 int /*<<< orphan*/  IEEE80211_M_STA ; 
 int /*<<< orphan*/  IEEE80211_T_OFDM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct urtw_softc*) ; 
 size_t URTW_8187B_BULK_TX_BE ; 
 int /*<<< orphan*/  URTW_8187B_N_XFERS ; 
 size_t URTW_8187L_BULK_TX_LOW ; 
 int /*<<< orphan*/  URTW_8187L_N_XFERS ; 
 int /*<<< orphan*/  URTW_DEFAULT_RTS_RETRY ; 
 int /*<<< orphan*/  URTW_DEFAULT_TX_RETRY ; 
 int /*<<< orphan*/  URTW_EEPROM_93C46 ; 
 int /*<<< orphan*/  URTW_EEPROM_93C56 ; 
 int /*<<< orphan*/  URTW_IFACE_INDEX ; 
 int /*<<< orphan*/  URTW_LOCK (struct urtw_softc*) ; 
 scalar_t__ URTW_REV_RTL8187B ; 
 int /*<<< orphan*/  URTW_RIDX_CCK11 ; 
 int URTW_RTL8187B ; 
 int /*<<< orphan*/  URTW_RX ; 
 int URTW_RX_9356SEL ; 
 int /*<<< orphan*/  URTW_RX_RADIOTAP_PRESENT ; 
 int /*<<< orphan*/  URTW_TX_RADIOTAP_PRESENT ; 
 int /*<<< orphan*/  URTW_UNLOCK (struct urtw_softc*) ; 
 scalar_t__ USB_GET_DRIVER_INFO (struct usb_attach_arg*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct urtw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_announce (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_ifattach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_radiotap_attach (struct ieee80211com*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_config* urtw_8187b_usbconfig ; 
 struct usb_config* urtw_8187l_usbconfig ; 
 int /*<<< orphan*/  urtw_debug ; 
 scalar_t__ urtw_get_macaddr (struct urtw_softc*) ; 
 scalar_t__ urtw_get_rfchip (struct urtw_softc*) ; 
 scalar_t__ urtw_get_txpwr (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_getradiocaps (struct ieee80211com*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ urtw_led_init (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_ledtask ; 
 int /*<<< orphan*/  urtw_parent ; 
 int /*<<< orphan*/  urtw_preamble_mode ; 
 int /*<<< orphan*/  urtw_raw_xmit ; 
 int /*<<< orphan*/  urtw_read32_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  urtw_scan_end ; 
 int /*<<< orphan*/  urtw_scan_start ; 
 int /*<<< orphan*/  urtw_set_channel ; 
 int /*<<< orphan*/  urtw_sysctl_node (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_transmit ; 
 int /*<<< orphan*/  urtw_update_mcast ; 
 int /*<<< orphan*/  urtw_update_promisc ; 
 int /*<<< orphan*/  urtw_updateslot ; 
 int /*<<< orphan*/  urtw_updateslottask ; 
 int /*<<< orphan*/  urtw_vap_create ; 
 int /*<<< orphan*/  urtw_vap_delete ; 
 int /*<<< orphan*/  usb_callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 
 scalar_t__ usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct usb_config const*,int /*<<< orphan*/ ,struct urtw_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* usbd_xfer_get_frame_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
urtw_attach(device_t dev)
{
	const struct usb_config *setup_start;
	int ret = ENXIO;
	struct urtw_softc *sc = device_get_softc(dev);
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct ieee80211com *ic = &sc->sc_ic;
	uint8_t iface_index = URTW_IFACE_INDEX;		/* XXX */
	uint16_t n_setup;
	uint32_t data;
	usb_error_t error;

	device_set_usb_desc(dev);

	sc->sc_dev = dev;
	sc->sc_udev = uaa->device;
	if (USB_GET_DRIVER_INFO(uaa) == URTW_REV_RTL8187B)
		sc->sc_flags |= URTW_RTL8187B;
#ifdef URTW_DEBUG
	sc->sc_debug = urtw_debug;
#endif

	mtx_init(&sc->sc_mtx, device_get_nameunit(sc->sc_dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	usb_callout_init_mtx(&sc->sc_led_ch, &sc->sc_mtx, 0);
	TASK_INIT(&sc->sc_led_task, 0, urtw_ledtask, sc);
	TASK_INIT(&sc->sc_updateslot_task, 0, urtw_updateslottask, sc);
	callout_init(&sc->sc_watchdog_ch, 0);
	mbufq_init(&sc->sc_snd, ifqmaxlen);

	if (sc->sc_flags & URTW_RTL8187B) {
		setup_start = urtw_8187b_usbconfig;
		n_setup = URTW_8187B_N_XFERS;
	} else {
		setup_start = urtw_8187l_usbconfig;
		n_setup = URTW_8187L_N_XFERS;
	}

	error = usbd_transfer_setup(uaa->device, &iface_index, sc->sc_xfer,
	    setup_start, n_setup, sc, &sc->sc_mtx);
	if (error) {
		device_printf(dev, "could not allocate USB transfers, "
		    "err=%s\n", usbd_errstr(error));
		ret = ENXIO;
		goto fail0;
	}

	if (sc->sc_flags & URTW_RTL8187B) {
		sc->sc_tx_dma_buf = 
		    usbd_xfer_get_frame_buffer(sc->sc_xfer[
		    URTW_8187B_BULK_TX_BE], 0);
	} else {
		sc->sc_tx_dma_buf =
		    usbd_xfer_get_frame_buffer(sc->sc_xfer[
		    URTW_8187L_BULK_TX_LOW], 0);
	}

	URTW_LOCK(sc);

	urtw_read32_m(sc, URTW_RX, &data);
	sc->sc_epromtype = (data & URTW_RX_9356SEL) ? URTW_EEPROM_93C56 :
	    URTW_EEPROM_93C46;

	error = urtw_get_rfchip(sc);
	if (error != 0)
		goto fail;
	error = urtw_get_macaddr(sc);
	if (error != 0)
		goto fail;
	error = urtw_get_txpwr(sc);
	if (error != 0)
		goto fail;
	error = urtw_led_init(sc);
	if (error != 0)
		goto fail;

	URTW_UNLOCK(sc);

	sc->sc_rts_retry = URTW_DEFAULT_RTS_RETRY;
	sc->sc_tx_retry = URTW_DEFAULT_TX_RETRY;
	sc->sc_currate = URTW_RIDX_CCK11;
	sc->sc_preamble_mode = urtw_preamble_mode;

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
	    IEEE80211_C_BGSCAN |	/* capable of bg scanning */
	    IEEE80211_C_WPA;		/* 802.11i */

	/* XXX TODO: setup regdomain if URTW_EPROM_CHANPLAN_BY_HW bit is set.*/
 
	urtw_getradiocaps(ic, IEEE80211_CHAN_MAX, &ic->ic_nchans,
	    ic->ic_channels);

	ieee80211_ifattach(ic);
	ic->ic_raw_xmit = urtw_raw_xmit;
	ic->ic_scan_start = urtw_scan_start;
	ic->ic_scan_end = urtw_scan_end;
	ic->ic_getradiocaps = urtw_getradiocaps;
	ic->ic_set_channel = urtw_set_channel;
	ic->ic_updateslot = urtw_updateslot;
	ic->ic_vap_create = urtw_vap_create;
	ic->ic_vap_delete = urtw_vap_delete;
	ic->ic_update_promisc = urtw_update_promisc;
	ic->ic_update_mcast = urtw_update_mcast;
	ic->ic_parent = urtw_parent;
	ic->ic_transmit = urtw_transmit;

	ieee80211_radiotap_attach(ic,
	    &sc->sc_txtap.wt_ihdr, sizeof(sc->sc_txtap),
	    URTW_TX_RADIOTAP_PRESENT,
	    &sc->sc_rxtap.wr_ihdr, sizeof(sc->sc_rxtap),
	    URTW_RX_RADIOTAP_PRESENT);

	urtw_sysctl_node(sc);

	if (bootverbose)
		ieee80211_announce(ic);
	return (0);

fail:
	URTW_UNLOCK(sc);
	usbd_transfer_unsetup(sc->sc_xfer, (sc->sc_flags & URTW_RTL8187B) ?
	    URTW_8187B_N_XFERS : URTW_8187L_N_XFERS);
fail0:
	return (ret);
}