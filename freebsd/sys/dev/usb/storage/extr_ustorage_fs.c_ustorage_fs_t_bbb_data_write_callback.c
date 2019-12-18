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
typedef  int uint32_t ;
struct TYPE_2__ {int data_rem; int data_ptr; int offset; int data_error; int /*<<< orphan*/  data_short; } ;
struct ustorage_fs_softc {TYPE_1__ sc_transfer; int /*<<< orphan*/  sc_dma_ptr; } ;
struct usb_xfer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int /*<<< orphan*/  USB_FORCE_SHORT_XFER ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USTORAGE_FS_T_BBB_STATUS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_clr_flag (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_is_stalled (struct usb_xfer*) ; 
 int usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_flag (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ustorage_fs_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ustorage_fs_transfer_start (struct ustorage_fs_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ustorage_fs_t_bbb_data_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ustorage_fs_softc *sc = usbd_xfer_softc(xfer);
	uint32_t max_bulk = usbd_xfer_max_len(xfer);
	int actlen, sumlen;

	usbd_xfer_status(xfer, &actlen, &sumlen, NULL, NULL);

	DPRINTF("\n");

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		sc->sc_transfer.data_rem -= actlen;
		sc->sc_transfer.data_ptr += actlen;
		sc->sc_transfer.offset += actlen;

		if (actlen != sumlen || sc->sc_transfer.data_rem == 0) {
			/* short transfer or end of data */
			ustorage_fs_transfer_start(sc,
			    USTORAGE_FS_T_BBB_STATUS);
			break;
		}
	case USB_ST_SETUP:
tr_setup:
		if (max_bulk >= sc->sc_transfer.data_rem) {
			max_bulk = sc->sc_transfer.data_rem;
			if (sc->sc_transfer.data_short)
				usbd_xfer_set_flag(xfer, USB_FORCE_SHORT_XFER);
			else
				usbd_xfer_clr_flag(xfer, USB_FORCE_SHORT_XFER);
		} else
			usbd_xfer_clr_flag(xfer, USB_FORCE_SHORT_XFER);

		if (sc->sc_transfer.data_error) {
			sc->sc_transfer.data_error = 0;
			usbd_xfer_set_stall(xfer);
		}

		/* XXX copy data to DMA buffer */
		memcpy(sc->sc_dma_ptr, sc->sc_transfer.data_ptr, max_bulk);

		usbd_xfer_set_frame_data(xfer, 0, sc->sc_dma_ptr, max_bulk);
		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		if (error == USB_ERR_CANCELLED) {
			break;
		}
		/*
		 * If the pipe is already stalled, don't do another
		 * stall
		 */
		if (!usbd_xfer_is_stalled(xfer))
			sc->sc_transfer.data_error = 1;

		/* try again */
		goto tr_setup;
	}
}