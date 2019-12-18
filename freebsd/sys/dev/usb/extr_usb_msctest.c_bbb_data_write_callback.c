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
typedef  int usb_frlength_t ;
typedef  int /*<<< orphan*/  usb_error_t ;
struct usb_xfer {int dummy; } ;
struct bbb_transfer {int data_rem; int data_ptr; int actlen; int /*<<< orphan*/  data_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,int) ; 
 int /*<<< orphan*/  ST_DATA_WR_CS ; 
 int /*<<< orphan*/  ST_STATUS ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  bbb_done (struct bbb_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbb_transfer_start (struct bbb_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_timeout (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 struct bbb_transfer* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bbb_data_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct bbb_transfer *sc = usbd_xfer_softc(xfer);
	usb_frlength_t max_bulk = usbd_xfer_max_len(xfer);
	int actlen, sumlen;

	usbd_xfer_status(xfer, &actlen, &sumlen, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		sc->data_rem -= actlen;
		sc->data_ptr += actlen;
		sc->actlen += actlen;

		if (actlen < sumlen) {
			/* short transfer */
			sc->data_rem = 0;
		}
	case USB_ST_SETUP:
		DPRINTF("max_bulk=%d, data_rem=%d\n",
		    max_bulk, sc->data_rem);

		if (sc->data_rem == 0) {
			bbb_transfer_start(sc, ST_STATUS);
			break;
		}
		if (max_bulk > sc->data_rem) {
			max_bulk = sc->data_rem;
		}
		usbd_xfer_set_timeout(xfer, sc->data_timeout);
		usbd_xfer_set_frame_data(xfer, 0, sc->data_ptr, max_bulk);
		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		if (error == USB_ERR_CANCELLED) {
			bbb_done(sc, error);
		} else {
			bbb_transfer_start(sc, ST_DATA_WR_CS);
		}
		break;
	}
}