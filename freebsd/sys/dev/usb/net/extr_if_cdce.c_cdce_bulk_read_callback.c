#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
struct usb_xfer {int dummy; } ;
struct mbuf {int /*<<< orphan*/  m_len; int /*<<< orphan*/  m_data; } ;
struct ether_header {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ue_udev; } ;
struct cdce_softc {int sc_flags; struct mbuf** sc_rx_buf; TYPE_1__ sc_ue; } ;

/* Variables and functions */
 int CDCE_FLAG_ZAURUS ; 
 int /*<<< orphan*/  CDCE_FRAMES_MAX ; 
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
 int /*<<< orphan*/  USB_MODE_HOST ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  cdce_free_queue (struct mbuf**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* uether_newbuf () ; 
 int /*<<< orphan*/  uether_rxflush (TYPE_1__*) ; 
 int /*<<< orphan*/  uether_rxmbuf (TYPE_1__*,struct mbuf*,int) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int usbd_xfer_frame_len (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct cdce_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cdce_bulk_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct cdce_softc *sc = usbd_xfer_softc(xfer);
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

			/* Strip off CRC added by Zaurus, if any */
			if ((sc->sc_flags & CDCE_FLAG_ZAURUS) && len >= 14)
				len -= 4;

			if (len < (int)sizeof(struct ether_header)) {
				m_freem(m);
				continue;
			}
			/* queue up mbuf */
			uether_rxmbuf(&sc->sc_ue, m, len);
		}

		/* FALLTHROUGH */
	case USB_ST_SETUP:
		/* 
		 * TODO: Implement support for multi frame transfers,
		 * when the USB hardware supports it.
		 */
		for (x = 0; x != 1; x++) {
			if (sc->sc_rx_buf[x] == NULL) {
				m = uether_newbuf();
				if (m == NULL)
					goto tr_stall;
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
		DPRINTF("error = %s\n",
		    usbd_errstr(error));

		if (error != USB_ERR_CANCELLED) {
tr_stall:
			if (usbd_get_mode(sc->sc_ue.ue_udev) == USB_MODE_HOST) {
				/* try to clear stall first */
				usbd_xfer_set_stall(xfer);
				usbd_xfer_set_frames(xfer, 0);
				usbd_transfer_submit(xfer);
			}
			break;
		}

		/* need to free the RX-mbufs when we are cancelled */
		cdce_free_queue(sc->sc_rx_buf, CDCE_FRAMES_MAX);
		break;
	}
}