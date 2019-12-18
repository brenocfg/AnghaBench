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
struct bbb_transfer {int status_try; TYPE_1__* csw; } ;
struct bbb_csw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bCSWStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSWSTATUS_GOOD ; 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERR_CSW_FAILED ; 
 int /*<<< orphan*/  ST_DATA_RD_CS ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int /*<<< orphan*/  USB_ERR_SHORT_XFER ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  bbb_done (struct bbb_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbb_transfer_start (struct bbb_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 struct bbb_transfer* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bbb_status_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct bbb_transfer *sc = usbd_xfer_softc(xfer);
	int actlen;
	int sumlen;

	usbd_xfer_status(xfer, &actlen, &sumlen, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		/* very simple status check */

		if (actlen < (int)sizeof(struct bbb_csw)) {
			bbb_done(sc, USB_ERR_SHORT_XFER);
		} else if (sc->csw->bCSWStatus == CSWSTATUS_GOOD) {
			bbb_done(sc, 0);	/* success */
		} else {
			bbb_done(sc, ERR_CSW_FAILED);	/* error */
		}
		break;

	case USB_ST_SETUP:
		usbd_xfer_set_frame_len(xfer, 0,
		    sizeof(struct bbb_csw));
		usbd_transfer_submit(xfer);
		break;

	default:
		DPRINTF("Failed to read CSW: %s, try %d\n",
		    usbd_errstr(error), sc->status_try);

		if (error == USB_ERR_CANCELLED || sc->status_try) {
			bbb_done(sc, error);
		} else {
			sc->status_try = 1;
			bbb_transfer_start(sc, ST_DATA_RD_CS);
		}
		break;
	}
}