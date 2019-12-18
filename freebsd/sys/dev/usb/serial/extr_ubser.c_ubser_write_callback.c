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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct ubser_softc {scalar_t__ sc_curr_tx_unit; int /*<<< orphan*/  sc_tx_size; scalar_t__ sc_ucom; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  ubser_inc_tx_unit (struct ubser_softc*) ; 
 int /*<<< orphan*/  ucom_get_data (scalar_t__,struct usb_page_cache*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ubser_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
ubser_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ubser_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	uint8_t buf[1];
	uint8_t first_unit = sc->sc_curr_tx_unit;
	uint32_t actlen;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_SETUP:
	case USB_ST_TRANSFERRED:
tr_setup:
		pc = usbd_xfer_get_frame(xfer, 0);
		do {
			if (ucom_get_data(sc->sc_ucom + sc->sc_curr_tx_unit,
			    pc, 1, sc->sc_tx_size - 1,
			    &actlen)) {

				buf[0] = sc->sc_curr_tx_unit;

				usbd_copy_in(pc, 0, buf, 1);

				usbd_xfer_set_frame_len(xfer, 0, actlen + 1);
				usbd_transfer_submit(xfer);

				ubser_inc_tx_unit(sc);	/* round robin */

				break;
			}
			ubser_inc_tx_unit(sc);

		} while (sc->sc_curr_tx_unit != first_unit);

		return;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		return;

	}
}