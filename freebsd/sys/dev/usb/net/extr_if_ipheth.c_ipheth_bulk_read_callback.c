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
typedef  int uint8_t ;
struct usb_xfer {int dummy; } ;
struct mbuf {int /*<<< orphan*/  m_len; int /*<<< orphan*/  m_data; } ;
struct ipheth_softc {struct mbuf** sc_rx_buf; int /*<<< orphan*/  sc_ue; } ;
struct ether_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int /*<<< orphan*/  ETHER_ALIGN ; 
 int /*<<< orphan*/  IPHETH_RX_ADJ ; 
 int IPHETH_RX_FRAMES_MAX ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  ipheth_free_queue (struct mbuf**,int) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* uether_newbuf () ; 
 int /*<<< orphan*/  uether_rxflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uether_rxmbuf (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int usbd_xfer_frame_len (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ipheth_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipheth_bulk_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ipheth_softc *sc = usbd_xfer_softc(xfer);
	struct mbuf *m;
	uint8_t x;
	int actlen;
	int aframes;
	int len;

	usbd_xfer_status(xfer, &actlen, NULL, &aframes, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		DPRINTF("received %u bytes in %u frames\n", actlen, aframes);

		for (x = 0; x != aframes; x++) {

			m = sc->sc_rx_buf[x];
			sc->sc_rx_buf[x] = NULL;
			len = usbd_xfer_frame_len(xfer, x);

			if (len < (int)(sizeof(struct ether_header) +
			    IPHETH_RX_ADJ)) {
				m_freem(m);
				continue;
			}

			m_adj(m, IPHETH_RX_ADJ);

			/* queue up mbuf */
			uether_rxmbuf(&sc->sc_ue, m, len - IPHETH_RX_ADJ);
		}

		/* FALLTHROUGH */
	case USB_ST_SETUP:

		for (x = 0; x != IPHETH_RX_FRAMES_MAX; x++) {
			if (sc->sc_rx_buf[x] == NULL) {
				m = uether_newbuf();
				if (m == NULL)
					goto tr_stall;

				/* cancel alignment for ethernet */
				m_adj(m, ETHER_ALIGN);

				sc->sc_rx_buf[x] = m;
			} else {
				m = sc->sc_rx_buf[x];
			}

			usbd_xfer_set_frame_data(xfer, x, m->m_data, m->m_len);
		}
		/* set number of frames and start hardware */
		usbd_xfer_set_frames(xfer, x);
		usbd_transfer_submit(xfer);
		/* flush any received frames */
		uether_rxflush(&sc->sc_ue);
		break;

	default:			/* Error */
		DPRINTF("error = %s\n", usbd_errstr(error));

		if (error != USB_ERR_CANCELLED) {
	tr_stall:
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			usbd_xfer_set_frames(xfer, 0);
			usbd_transfer_submit(xfer);
			break;
		}
		/* need to free the RX-mbufs when we are cancelled */
		ipheth_free_queue(sc->sc_rx_buf, IPHETH_RX_FRAMES_MAX);
		break;
	}
}