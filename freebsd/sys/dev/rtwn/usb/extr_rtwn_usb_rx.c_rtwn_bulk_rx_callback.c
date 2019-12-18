#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
struct usb_xfer {int dummy; } ;
struct ieee80211com {int /*<<< orphan*/  ic_ierrors; } ;
struct rtwn_softc {struct ieee80211com sc_ic; } ;
struct rtwn_usb_softc {int /*<<< orphan*/  uc_rx_inactive; int /*<<< orphan*/  uc_rx_active; struct rtwn_softc uc_sc; } ;
struct rtwn_data {int /*<<< orphan*/  buf; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 struct rtwn_data* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct rtwn_data*,struct mbuf*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_input_mimo (struct ieee80211_node*,struct mbuf*) ; 
 int /*<<< orphan*/  ieee80211_input_mimo_all (struct ieee80211com*,struct mbuf*) ; 
 struct mbuf* rtwn_report_intr (struct rtwn_usb_softc*,struct usb_xfer*,struct rtwn_data*) ; 
 struct ieee80211_node* rtwn_rx_frame (struct rtwn_softc*,struct mbuf*) ; 
 int /*<<< orphan*/  rtwn_start (struct rtwn_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct rtwn_usb_softc* usbd_xfer_softc (struct usb_xfer*) ; 

void
rtwn_bulk_rx_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct rtwn_usb_softc *uc = usbd_xfer_softc(xfer);
	struct rtwn_softc *sc = &uc->uc_sc;
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211_node *ni;
	struct mbuf *m = NULL, *next;
	struct rtwn_data *data;

	RTWN_ASSERT_LOCKED(sc);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		data = STAILQ_FIRST(&uc->uc_rx_active);
		if (data == NULL)
			goto tr_setup;
		STAILQ_REMOVE_HEAD(&uc->uc_rx_active, next);
		m = rtwn_report_intr(uc, xfer, data);
		STAILQ_INSERT_TAIL(&uc->uc_rx_inactive, data, next);
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		data = STAILQ_FIRST(&uc->uc_rx_inactive);
		if (data == NULL) {
			KASSERT(m == NULL, ("mbuf isn't NULL"));
			goto finish;
		}
		STAILQ_REMOVE_HEAD(&uc->uc_rx_inactive, next);
		STAILQ_INSERT_TAIL(&uc->uc_rx_active, data, next);
		usbd_xfer_set_frame_data(xfer, 0, data->buf,
		    usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);

		/*
		 * To avoid LOR we should unlock our private mutex here to call
		 * ieee80211_input() because here is at the end of a USB
		 * callback and safe to unlock.
		 */
		while (m != NULL) {
			next = m->m_nextpkt;
			m->m_nextpkt = NULL;

			ni = rtwn_rx_frame(sc, m);

			RTWN_UNLOCK(sc);

			if (ni != NULL) {
				(void)ieee80211_input_mimo(ni, m);
				ieee80211_free_node(ni);
			} else {
				(void)ieee80211_input_mimo_all(ic, m);
			}
			RTWN_LOCK(sc);
			m = next;
		}
		break;
	default:
		/* needs it to the inactive queue due to a error. */
		data = STAILQ_FIRST(&uc->uc_rx_active);
		if (data != NULL) {
			STAILQ_REMOVE_HEAD(&uc->uc_rx_active, next);
			STAILQ_INSERT_TAIL(&uc->uc_rx_inactive, data, next);
		}
		if (error != USB_ERR_CANCELLED) {
			/* XXX restart device if frame was fragmented? */

			usbd_xfer_set_stall(xfer);
			counter_u64_add(ic->ic_ierrors, 1);
			goto tr_setup;
		}
		break;
	}
finish:
	/* Kick-start more transmit in case we stalled */
	rtwn_start(sc);
}