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
typedef  int uint16_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct usb_cdc_notification {int bmRequestType; int bNotification; int* data; int /*<<< orphan*/  wLength; } ;
struct umodem_softc {int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_msr; int /*<<< orphan*/  sc_lsr; } ;
typedef  int /*<<< orphan*/  pkt ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  SER_DCD ; 
 int /*<<< orphan*/  SER_DSR ; 
 int /*<<< orphan*/  SER_RI ; 
 int UCDC_NOTIFICATION ; 
 int UCDC_N_SERIAL_DCD ; 
 int UCDC_N_SERIAL_DSR ; 
 int UCDC_N_SERIAL_RI ; 
#define  UCDC_N_SERIAL_STATE 130 
 int UGETW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  ucom_status_change (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_cdc_notification*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct umodem_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
umodem_intr_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct usb_cdc_notification pkt;
	struct umodem_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	uint16_t wLen;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		if (actlen < 8) {
			DPRINTF("received short packet, "
			    "%d bytes\n", actlen);
			goto tr_setup;
		}
		if (actlen > (int)sizeof(pkt)) {
			DPRINTF("truncating message\n");
			actlen = sizeof(pkt);
		}
		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_out(pc, 0, &pkt, actlen);

		actlen -= 8;

		wLen = UGETW(pkt.wLength);
		if (actlen > wLen) {
			actlen = wLen;
		}
		if (pkt.bmRequestType != UCDC_NOTIFICATION) {
			DPRINTF("unknown message type, "
			    "0x%02x, on notify pipe!\n",
			    pkt.bmRequestType);
			goto tr_setup;
		}
		switch (pkt.bNotification) {
		case UCDC_N_SERIAL_STATE:
			/*
			 * Set the serial state in ucom driver based on
			 * the bits from the notify message
			 */
			if (actlen < 2) {
				DPRINTF("invalid notification "
				    "length, %d bytes!\n", actlen);
				break;
			}
			DPRINTF("notify bytes = %02x%02x\n",
			    pkt.data[0],
			    pkt.data[1]);

			/* Currently, lsr is always zero. */
			sc->sc_lsr = 0;
			sc->sc_msr = 0;

			if (pkt.data[0] & UCDC_N_SERIAL_RI) {
				sc->sc_msr |= SER_RI;
			}
			if (pkt.data[0] & UCDC_N_SERIAL_DSR) {
				sc->sc_msr |= SER_DSR;
			}
			if (pkt.data[0] & UCDC_N_SERIAL_DCD) {
				sc->sc_msr |= SER_DCD;
			}
			ucom_status_change(&sc->sc_ucom);
			break;

		default:
			DPRINTF("unknown notify message: 0x%02x\n",
			    pkt.bNotification);
			break;
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