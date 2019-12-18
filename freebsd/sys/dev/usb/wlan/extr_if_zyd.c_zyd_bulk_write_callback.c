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
typedef  int /*<<< orphan*/  usb_error_t ;
struct zyd_tx_radiotap_header {int /*<<< orphan*/  wt_rate; int /*<<< orphan*/  wt_flags; } ;
struct zyd_tx_data {int /*<<< orphan*/  rate; TYPE_1__* ni; int /*<<< orphan*/  desc; struct mbuf* m; } ;
struct TYPE_6__ {int /*<<< orphan*/  ic_oerrors; } ;
struct zyd_softc {int /*<<< orphan*/  sc_dev; TYPE_3__ sc_ic; struct zyd_tx_radiotap_header sc_txtap; int /*<<< orphan*/  tx_q; } ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_5__ {int len; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct ieee80211vap {int dummy; } ;
struct TYPE_4__ {struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct zyd_softc*,int /*<<< orphan*/ ,char*,int) ; 
 struct zyd_tx_data* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int /*<<< orphan*/  USB_ERR_TIMEOUT ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  ZYD_DEBUG_ANY ; 
 int ZYD_MAX_TXBUFSZ ; 
 int ZYD_TX_DESC_SIZE ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_radiotap_active_vap (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_radiotap_tx (struct ieee80211vap*,struct mbuf*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_m_copy_in (struct usb_page_cache*,int,struct mbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 struct zyd_tx_data* usbd_xfer_get_priv (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_priv (struct usb_xfer*,struct zyd_tx_data*) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct zyd_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zyd_start (struct zyd_softc*) ; 
 int /*<<< orphan*/  zyd_tx_free (struct zyd_tx_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zyd_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct zyd_softc *sc = usbd_xfer_softc(xfer);
	struct ieee80211vap *vap;
	struct zyd_tx_data *data;
	struct mbuf *m;
	struct usb_page_cache *pc;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTF(sc, ZYD_DEBUG_ANY, "transfer complete, %u bytes\n",
		    actlen);

		/* free resources */
		data = usbd_xfer_get_priv(xfer);
		zyd_tx_free(data, 0);
		usbd_xfer_set_priv(xfer, NULL);

		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		data = STAILQ_FIRST(&sc->tx_q);
		if (data) {
			STAILQ_REMOVE_HEAD(&sc->tx_q, next);
			m = data->m;

			if (m->m_pkthdr.len > (int)ZYD_MAX_TXBUFSZ) {
				DPRINTF(sc, ZYD_DEBUG_ANY, "data overflow, %u bytes\n",
				    m->m_pkthdr.len);
				m->m_pkthdr.len = ZYD_MAX_TXBUFSZ;
			}
			pc = usbd_xfer_get_frame(xfer, 0);
			usbd_copy_in(pc, 0, &data->desc, ZYD_TX_DESC_SIZE);
			usbd_m_copy_in(pc, ZYD_TX_DESC_SIZE, m, 0,
			    m->m_pkthdr.len);

			vap = data->ni->ni_vap;
			if (ieee80211_radiotap_active_vap(vap)) {
				struct zyd_tx_radiotap_header *tap = &sc->sc_txtap;

				tap->wt_flags = 0;
				tap->wt_rate = data->rate;

				ieee80211_radiotap_tx(vap, m);
			}

			usbd_xfer_set_frame_len(xfer, 0, ZYD_TX_DESC_SIZE + m->m_pkthdr.len);
			usbd_xfer_set_priv(xfer, data);
			usbd_transfer_submit(xfer);
		}
		zyd_start(sc);
		break;

	default:			/* Error */
		DPRINTF(sc, ZYD_DEBUG_ANY, "transfer error, %s\n",
		    usbd_errstr(error));

		counter_u64_add(sc->sc_ic.ic_oerrors, 1);
		data = usbd_xfer_get_priv(xfer);
		usbd_xfer_set_priv(xfer, NULL);
		if (data != NULL)
			zyd_tx_free(data, error);

		if (error != USB_ERR_CANCELLED) {
			if (error == USB_ERR_TIMEOUT)
				device_printf(sc->sc_dev, "device timeout\n");

			/*
			 * Try to clear stall first, also if other
			 * errors occur, hence clearing stall
			 * introduces a 50 ms delay:
			 */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		break;
	}
}