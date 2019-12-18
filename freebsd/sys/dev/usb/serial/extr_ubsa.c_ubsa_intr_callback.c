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
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct ubsa_softc {int sc_lsr; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_msr; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int /*<<< orphan*/  SER_CTS ; 
 int /*<<< orphan*/  SER_DCD ; 
 int /*<<< orphan*/  SER_DSR ; 
 int /*<<< orphan*/  SER_RI ; 
 int UBSA_MSR_CTS ; 
 int UBSA_MSR_DCD ; 
 int UBSA_MSR_DSR ; 
 int UBSA_MSR_RI ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  ucom_status_change (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ubsa_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ubsa_intr_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ubsa_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	uint8_t buf[4];
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		if (actlen >= (int)sizeof(buf)) {
			pc = usbd_xfer_get_frame(xfer, 0);
			usbd_copy_out(pc, 0, buf, sizeof(buf));

			/*
			 * MSR bits need translation from ns16550 to SER_* values.
			 * LSR bits are ns16550 in hardware and ucom.
			 */
			sc->sc_msr = 0;
			if (buf[3] & UBSA_MSR_CTS)
				sc->sc_msr |= SER_CTS;
			if (buf[3] & UBSA_MSR_DCD)
				sc->sc_msr |= SER_DCD;
			if (buf[3] & UBSA_MSR_RI)
				sc->sc_msr |= SER_RI;
			if (buf[3] & UBSA_MSR_DSR)
				sc->sc_msr |= SER_DSR;
			sc->sc_lsr = buf[2];

			DPRINTF("lsr = 0x%02x, msr = 0x%02x\n",
			    sc->sc_lsr, sc->sc_msr);

			ucom_status_change(&sc->sc_ucom);
		} else {
			DPRINTF("ignoring short packet, %d bytes\n", actlen);
		}
		/* FALLTHROUGH */
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