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
typedef  int /*<<< orphan*/  usb_error_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct udbp_softc {int sc_flags; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_node; struct mbuf* sc_bulk_in_buffer; } ;
struct TYPE_2__ {int len; } ;
struct mbuf {int m_len; int /*<<< orphan*/  m_data; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  MCLGET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGETHDR (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int UDBP_FLAG_READ_STALL ; 
 size_t UDBP_T_RD_CS ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  ng_send_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udbp_bulk_read_complete ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct udbp_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
udbp_bulk_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct udbp_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	struct mbuf *m;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		/* allocate new mbuf */

		MGETHDR(m, M_NOWAIT, MT_DATA);

		if (m == NULL) {
			goto tr_setup;
		}

		if (!(MCLGET(m, M_NOWAIT))) {
			m_freem(m);
			goto tr_setup;
		}
		m->m_pkthdr.len = m->m_len = actlen;

		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_out(pc, 0, m->m_data, actlen);

		sc->sc_bulk_in_buffer = m;

		DPRINTF("received package %d bytes\n", actlen);

	case USB_ST_SETUP:
tr_setup:
		if (sc->sc_bulk_in_buffer) {
			ng_send_fn(sc->sc_node, NULL, &udbp_bulk_read_complete, NULL, 0);
			return;
		}
		if (sc->sc_flags & UDBP_FLAG_READ_STALL) {
			usbd_transfer_start(sc->sc_xfer[UDBP_T_RD_CS]);
			return;
		}
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		return;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			sc->sc_flags |= UDBP_FLAG_READ_STALL;
			usbd_transfer_start(sc->sc_xfer[UDBP_T_RD_CS]);
		}
		return;

	}
}