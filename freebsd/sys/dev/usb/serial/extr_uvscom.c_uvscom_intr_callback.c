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
typedef  int uint8_t ;
struct uvscom_softc {int sc_unit_status; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_msr; int /*<<< orphan*/  sc_lsr; } ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  SER_CTS ; 
 int /*<<< orphan*/  SER_DCD ; 
 int /*<<< orphan*/  SER_DSR ; 
 int /*<<< orphan*/  ULSR_RXRDY ; 
 int /*<<< orphan*/  ULSR_TXRDY ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int UVSCOM_CTS ; 
 int UVSCOM_DCD ; 
 int UVSCOM_DSR ; 
 int UVSCOM_RXRDY ; 
 int UVSCOM_TXRDY ; 
 int /*<<< orphan*/  ucom_status_change (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct uvscom_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uvscom_intr_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct uvscom_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	uint8_t buf[2];
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		if (actlen >= 2) {

			pc = usbd_xfer_get_frame(xfer, 0);
			usbd_copy_out(pc, 0, buf, sizeof(buf));

			sc->sc_lsr = 0;
			sc->sc_msr = 0;
			sc->sc_unit_status = buf[1];

			if (buf[0] & UVSCOM_TXRDY) {
				sc->sc_lsr |= ULSR_TXRDY;
			}
			if (buf[0] & UVSCOM_RXRDY) {
				sc->sc_lsr |= ULSR_RXRDY;
			}
			if (buf[1] & UVSCOM_CTS) {
				sc->sc_msr |= SER_CTS;
			}
			if (buf[1] & UVSCOM_DSR) {
				sc->sc_msr |= SER_DSR;
			}
			if (buf[1] & UVSCOM_DCD) {
				sc->sc_msr |= SER_DCD;
			}
			/*
			 * the UCOM layer will ignore this call if the TTY
			 * device is closed!
			 */
			ucom_status_change(&sc->sc_ucom);
		}
	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
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