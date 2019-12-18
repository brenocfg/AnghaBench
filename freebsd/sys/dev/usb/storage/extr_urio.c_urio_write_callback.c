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
typedef  int /*<<< orphan*/  uint32_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct usb_fifo {int dummy; } ;
struct TYPE_2__ {struct usb_fifo** fp; } ;
struct urio_softc {int sc_flags; int /*<<< orphan*/ * sc_xfer; TYPE_1__ sc_fifo; } ;

/* Variables and functions */
 int URIO_FLAG_WRITE_STALL ; 
 size_t URIO_T_WR_CS ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 size_t USB_FIFO_TX ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  usb_fifo_get_data (struct usb_fifo*,struct usb_page_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct urio_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
urio_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct urio_softc *sc = usbd_xfer_softc(xfer);
	struct usb_fifo *f = sc->sc_fifo.fp[USB_FIFO_TX];
	struct usb_page_cache *pc;
	uint32_t actlen;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
	case USB_ST_SETUP:
		if (sc->sc_flags & URIO_FLAG_WRITE_STALL) {
			usbd_transfer_start(sc->sc_xfer[URIO_T_WR_CS]);
			return;
		}
		pc = usbd_xfer_get_frame(xfer, 0);
		if (usb_fifo_get_data(f, pc, 0,
		    usbd_xfer_max_len(xfer), &actlen, 0)) {

			usbd_xfer_set_frame_len(xfer, 0, actlen);
			usbd_transfer_submit(xfer);
		}
		return;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			sc->sc_flags |= URIO_FLAG_WRITE_STALL;
			usbd_transfer_start(sc->sc_xfer[URIO_T_WR_CS]);
		}
		return;
	}
}