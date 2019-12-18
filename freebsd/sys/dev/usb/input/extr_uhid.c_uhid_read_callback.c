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
struct usb_device_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fp; } ;
struct uhid_softc {int sc_isize; TYPE_1__ sc_fifo; int /*<<< orphan*/  sc_iid; int /*<<< orphan*/  sc_iface_no; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  UHID_INPUT_REPORT ; 
 size_t USB_FIFO_RX ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  uhid_fill_get_report (struct usb_device_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_fifo_put_bytes_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fifo_put_data (int /*<<< orphan*/ ,struct usb_page_cache*,int,int,int) ; 
 int /*<<< orphan*/  usb_fifo_put_data_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 struct uhid_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
uhid_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct uhid_softc *sc = usbd_xfer_softc(xfer);
	struct usb_device_request req;
	struct usb_page_cache *pc;

	pc = usbd_xfer_get_frame(xfer, 0);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		usb_fifo_put_data(sc->sc_fifo.fp[USB_FIFO_RX], pc, sizeof(req),
		    sc->sc_isize, 1);
		return;

	case USB_ST_SETUP:

		if (usb_fifo_put_bytes_max(sc->sc_fifo.fp[USB_FIFO_RX]) > 0) {

			uhid_fill_get_report
			    (&req, sc->sc_iface_no, UHID_INPUT_REPORT,
			    sc->sc_iid, sc->sc_isize);

			usbd_copy_in(pc, 0, &req, sizeof(req));

			usbd_xfer_set_frame_len(xfer, 0, sizeof(req));
			usbd_xfer_set_frame_len(xfer, 1, sc->sc_isize);
			usbd_xfer_set_frames(xfer, sc->sc_isize ? 2 : 1);
			usbd_transfer_submit(xfer);
		}
		return;

	default:			/* Error */
		/* bomb out */
		usb_fifo_put_data_error(sc->sc_fifo.fp[USB_FIFO_RX]);
		return;
	}
}