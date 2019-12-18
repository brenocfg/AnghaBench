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
struct usb_page_search {scalar_t__ buffer; } ;
struct usb_page_cache {int dummy; } ;
struct uhso_softc {TYPE_1__* sc_tty; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ht_xfer; } ;

/* Variables and functions */
 size_t UHSO_CTRL_READ ; 
 int /*<<< orphan*/  UHSO_DPRINTF (int,char*,int,...) ; 
 unsigned int UHSO_MPORT_TYPE_NOMAX ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_page_search*) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_priv (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct uhso_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
uhso_mux_intr_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct usb_page_cache *pc;
	struct usb_page_search res;
	struct uhso_softc *sc = usbd_xfer_softc(xfer);
	unsigned int i, mux;

	UHSO_DPRINTF(3, "status %d\n", USB_GET_STATE(xfer));

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		/*
		 * The multiplexed port number can be found at the first byte.
		 * It contains a bit mask, we transform this in to an integer.
		 */
		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_get_page(pc, 0, &res);

		i = *((unsigned char *)res.buffer);
		mux = 0;
		while (i >>= 1) {
			mux++;
		}

		UHSO_DPRINTF(3, "mux port %d (%d)\n", mux, i);
		if (mux > UHSO_MPORT_TYPE_NOMAX)
			break;

		/* Issue a read for this serial port */
		usbd_xfer_set_priv(
		    sc->sc_tty[mux].ht_xfer[UHSO_CTRL_READ],
		    &sc->sc_tty[mux]);
		usbd_transfer_start(sc->sc_tty[mux].ht_xfer[UHSO_CTRL_READ]);

		break;
	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		break;
	default:
		UHSO_DPRINTF(0, "error: %s\n", usbd_errstr(error));
		if (error == USB_ERR_CANCELLED)
			break;

		usbd_xfer_set_stall(xfer);
		goto tr_setup;
	}
}