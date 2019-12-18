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
typedef  int uint16_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct usb_cdc_notification {int* data; int /*<<< orphan*/  bNotification; int /*<<< orphan*/  bmRequestType; int /*<<< orphan*/  wLength; } ;
struct ucom_softc {size_t sc_subunit; struct u3g_softc* sc_parent; } ;
struct u3g_softc {int /*<<< orphan*/ * sc_msr; int /*<<< orphan*/ * sc_lsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int /*<<< orphan*/  SER_DCD ; 
 int /*<<< orphan*/  SER_DSR ; 
 int /*<<< orphan*/  SER_RI ; 
 int /*<<< orphan*/  UCDC_NOTIFICATION ; 
 int UCDC_N_SERIAL_DCD ; 
 int UCDC_N_SERIAL_DSR ; 
 int UCDC_N_SERIAL_RI ; 
 int /*<<< orphan*/  UCDC_N_SERIAL_STATE ; 
 int UGETW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  ucom_status_change (struct ucom_softc*) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_cdc_notification*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ucom_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
u3g_intr_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ucom_softc *ucom = usbd_xfer_softc(xfer);
	struct u3g_softc *sc = ucom->sc_parent;
	struct usb_page_cache *pc;
	struct usb_cdc_notification pkt;
	int actlen;
	uint16_t wLen;
	uint8_t mstatus;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		if (actlen < 8) {	/* usb_cdc_notification with 2 data bytes */
			DPRINTF("message too short (expected 8, received %d)\n", actlen);
			goto tr_setup;
		}
		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_out(pc, 0, &pkt, actlen);

		wLen = UGETW(pkt.wLength);
		if (wLen < 2) {
			DPRINTF("message too short (expected 2 data bytes, received %d)\n", wLen);
			goto tr_setup;
		}

		if (pkt.bmRequestType == UCDC_NOTIFICATION
		    && pkt.bNotification == UCDC_N_SERIAL_STATE) {
			/*
		         * Set the serial state in ucom driver based on
		         * the bits from the notify message
		         */
			DPRINTF("notify bytes = 0x%02x, 0x%02x\n",
			    pkt.data[0], pkt.data[1]);

			/* currently, lsr is always zero. */
			sc->sc_lsr[ucom->sc_subunit] = 0;
			sc->sc_msr[ucom->sc_subunit] = 0;

			mstatus = pkt.data[0];

			if (mstatus & UCDC_N_SERIAL_RI)
				sc->sc_msr[ucom->sc_subunit] |= SER_RI;
			if (mstatus & UCDC_N_SERIAL_DSR)
				sc->sc_msr[ucom->sc_subunit] |= SER_DSR;
			if (mstatus & UCDC_N_SERIAL_DCD)
				sc->sc_msr[ucom->sc_subunit] |= SER_DCD;
			ucom_status_change(ucom);
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