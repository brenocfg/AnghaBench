#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ustorage_fs_bbb_csw_t ;
typedef  int /*<<< orphan*/  usb_error_t ;
struct TYPE_3__ {int data_error; int /*<<< orphan*/  data_rem; } ;
struct ustorage_fs_softc {TYPE_1__ sc_transfer; TYPE_2__* sc_csw; } ;
struct usb_xfer {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dCSWDataResidue; int /*<<< orphan*/  dCSWSignature; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSWSIGNATURE ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USETDW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USTORAGE_FS_T_BBB_COMMAND ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_is_stalled (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ustorage_fs_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  ustorage_fs_transfer_start (struct ustorage_fs_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ustorage_fs_t_bbb_status_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ustorage_fs_softc *sc = usbd_xfer_softc(xfer);

	DPRINTF("\n");

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		ustorage_fs_transfer_start(sc, USTORAGE_FS_T_BBB_COMMAND);
		break;

	case USB_ST_SETUP:
tr_setup:
		USETDW(sc->sc_csw->dCSWSignature, CSWSIGNATURE);
		USETDW(sc->sc_csw->dCSWDataResidue, sc->sc_transfer.data_rem);

		if (sc->sc_transfer.data_error) {
			sc->sc_transfer.data_error = 0;
			usbd_xfer_set_stall(xfer);
		}
		usbd_xfer_set_frame_len(xfer, 0,
		    sizeof(ustorage_fs_bbb_csw_t));
		usbd_transfer_submit(xfer);
		break;

	default:
		if (error == USB_ERR_CANCELLED) {
			break;
		}
		/* If the pipe is already stalled, don't do another stall */
		if (!usbd_xfer_is_stalled(xfer))
			sc->sc_transfer.data_error = 1;

		/* try again */
		goto tr_setup;
	}
}