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
struct TYPE_2__ {int /*<<< orphan*/ * fp; } ;
struct uhid_softc {int sc_isize; TYPE_1__ sc_fifo; int /*<<< orphan*/  sc_iid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 size_t USB_FIFO_RX ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  usb_fifo_put_bytes_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fifo_put_data (int /*<<< orphan*/ ,struct usb_page_cache*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct uhid_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uhid_intr_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct uhid_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTF("transferred!\n");

		pc = usbd_xfer_get_frame(xfer, 0);

		/* 
		 * If the ID byte is non zero we allow descriptors
		 * having multiple sizes:
		 */
		if ((actlen >= (int)sc->sc_isize) ||
		    ((actlen > 0) && (sc->sc_iid != 0))) {
			/* limit report length to the maximum */
			if (actlen > (int)sc->sc_isize)
				actlen = sc->sc_isize;
			usb_fifo_put_data(sc->sc_fifo.fp[USB_FIFO_RX], pc,
			    0, actlen, 1);
		} else {
			/* ignore it */
			DPRINTF("ignored transfer, %d bytes\n", actlen);
		}

	case USB_ST_SETUP:
re_submit:
		if (usb_fifo_put_bytes_max(
		    sc->sc_fifo.fp[USB_FIFO_RX]) != 0) {
			usbd_xfer_set_frame_len(xfer, 0, sc->sc_isize);
			usbd_transfer_submit(xfer);
		}
		return;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			goto re_submit;
		}
		return;
	}
}