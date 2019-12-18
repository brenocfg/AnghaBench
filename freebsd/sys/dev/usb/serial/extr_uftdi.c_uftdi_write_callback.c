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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_portno; } ;
struct uftdi_softc {scalar_t__ sc_hdrlen; TYPE_1__ sc_ucom; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  FTDI_OUT_TAG (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ UFTDI_OBUFSIZE ; 
 scalar_t__ UFTDI_OPKTSIZE ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  ucom_get_data (TYPE_1__*,struct usb_page_cache*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct uftdi_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
uftdi_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct uftdi_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	uint32_t pktlen;
	uint32_t buflen;
	uint8_t buf[1];

	DPRINTFN(3, "\n");

	switch (USB_GET_STATE(xfer)) {
	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
		}
		/* FALLTHROUGH */
	case USB_ST_SETUP:
	case USB_ST_TRANSFERRED:
		/*
		 * If output packets don't require headers (the common case) we
		 * can just load the buffer up with payload bytes all at once.
		 * Otherwise, loop to format packets into the buffer while there
		 * is data available, and room for a packet header and at least
		 * one byte of payload.
		 *
		 * NOTE: The FTDI chip doesn't accept zero length
		 * packets. This cannot happen because the "pktlen"
		 * will always be non-zero when "ucom_get_data()"
		 * returns non-zero which we check below.
		 */
		pc = usbd_xfer_get_frame(xfer, 0);
		if (sc->sc_hdrlen == 0) {
			if (ucom_get_data(&sc->sc_ucom, pc, 0, UFTDI_OBUFSIZE, 
			    &buflen) == 0)
				break;
		} else {
			buflen = 0;
			while (buflen < UFTDI_OBUFSIZE - sc->sc_hdrlen - 1 &&
			    ucom_get_data(&sc->sc_ucom, pc, buflen + 
			    sc->sc_hdrlen, UFTDI_OPKTSIZE - sc->sc_hdrlen, 
			    &pktlen) != 0) {
				buf[0] = FTDI_OUT_TAG(pktlen, 
				    sc->sc_ucom.sc_portno);
				usbd_copy_in(pc, buflen, buf, 1);
				buflen += pktlen + sc->sc_hdrlen;
			}
		}
		if (buflen != 0) {
			usbd_xfer_set_frame_len(xfer, 0, buflen);
			usbd_transfer_submit(xfer);
		}
		break;
	}
}