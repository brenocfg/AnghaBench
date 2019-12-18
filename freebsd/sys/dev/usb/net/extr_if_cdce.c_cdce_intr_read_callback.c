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
struct TYPE_2__ {int /*<<< orphan*/  ue_udev; } ;
struct cdce_softc {TYPE_1__ sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
 int /*<<< orphan*/  USB_MODE_HOST ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  usbd_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct cdce_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cdce_intr_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct cdce_softc *sc = usbd_xfer_softc(xfer);
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		DPRINTF("Received %d bytes\n", actlen);

		/* TODO: decode some indications */

		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			/* start clear stall */
			if (usbd_get_mode(sc->sc_ue.ue_udev) == USB_MODE_HOST)
				usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		break;
	}
}