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
struct rsu_softc {int /*<<< orphan*/  sc_rx_inactive; int /*<<< orphan*/  sc_rx_active; struct ieee80211com sc_ic; } ;
struct rsu_data {int /*<<< orphan*/  buf; } ;
struct mbuf {int /*<<< orphan*/  m_flags; struct mbuf* m_next; } ;
struct ieee80211_node {int ni_flags; } ;

/* Variables and functions */
 int IEEE80211_NODE_HT ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_AMPDU ; 
 int /*<<< orphan*/  RSU_ASSERT_LOCKED (struct rsu_softc*) ; 
 int /*<<< orphan*/  RSU_LOCK (struct rsu_softc*) ; 
 int /*<<< orphan*/  RSU_UNLOCK (struct rsu_softc*) ; 
 struct rsu_data* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct rsu_data*,struct mbuf*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_input_mimo (struct ieee80211_node*,struct mbuf*) ; 
 int /*<<< orphan*/  ieee80211_input_mimo_all (struct ieee80211com*,struct mbuf*) ; 
 struct ieee80211_node* rsu_rx_frame (struct rsu_softc*,struct mbuf*) ; 
 struct mbuf* rsu_rxeof (struct usb_xfer*,struct rsu_data*) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct rsu_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
rsu_bulk_rx_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct rsu_softc *sc = usbd_xfer_softc(xfer);
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211_node *ni;
	struct mbuf *m = NULL, *next;
	struct rsu_data *data;

	RSU_ASSERT_LOCKED(sc);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		data = STAILQ_FIRST(&sc->sc_rx_active);
		if (data == NULL)
			goto tr_setup;
		STAILQ_REMOVE_HEAD(&sc->sc_rx_active, next);
		m = rsu_rxeof(xfer, data);
		STAILQ_INSERT_TAIL(&sc->sc_rx_inactive, data, next);
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		data = STAILQ_FIRST(&sc->sc_rx_inactive);
		if (data == NULL) {
			KASSERT(m == NULL, ("mbuf isn't NULL"));
			return;
		}
		STAILQ_REMOVE_HEAD(&sc->sc_rx_inactive, next);
		STAILQ_INSERT_TAIL(&sc->sc_rx_active, data, next);
		usbd_xfer_set_frame_data(xfer, 0, data->buf,
		    usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		/*
		 * To avoid LOR we should unlock our private mutex here to call
		 * ieee80211_input() because here is at the end of a USB
		 * callback and safe to unlock.
		 */
		while (m != NULL) {
			next = m->m_next;
			m->m_next = NULL;

			ni = rsu_rx_frame(sc, m);
			RSU_UNLOCK(sc);

			if (ni != NULL) {
				if (ni->ni_flags & IEEE80211_NODE_HT)
					m->m_flags |= M_AMPDU;
				(void)ieee80211_input_mimo(ni, m);
				ieee80211_free_node(ni);
			} else
				(void)ieee80211_input_mimo_all(ic, m);

			RSU_LOCK(sc);
			m = next;
		}
		break;
	default:
		/* needs it to the inactive queue due to a error. */
		data = STAILQ_FIRST(&sc->sc_rx_active);
		if (data != NULL) {
			STAILQ_REMOVE_HEAD(&sc->sc_rx_active, next);
			STAILQ_INSERT_TAIL(&sc->sc_rx_inactive, data, next);
		}
		if (error != USB_ERR_CANCELLED) {
			usbd_xfer_set_stall(xfer);
			counter_u64_add(ic->ic_ierrors, 1);
			goto tr_setup;
		}
		break;
	}

}