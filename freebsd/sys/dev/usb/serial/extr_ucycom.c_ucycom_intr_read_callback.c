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
typedef  int uint32_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct ucycom_softc {int sc_ist; int /*<<< orphan*/  sc_ilen; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_model; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*) ; 
#define  MODEL_CY7C63743 131 
#define  MODEL_CY7C64013 130 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  ucom_put_data (int /*<<< orphan*/ *,struct usb_page_cache*,int,int) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ucycom_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ucycom_intr_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ucycom_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	uint8_t buf[2];
	uint32_t offset;
	int len;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);
	pc = usbd_xfer_get_frame(xfer, 0);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		switch (sc->sc_model) {
		case MODEL_CY7C63743:
			if (actlen < 1) {
				goto tr_setup;
			}
			usbd_copy_out(pc, 0, buf, 1);

			sc->sc_ist = buf[0] & ~0x07;
			len = buf[0] & 0x07;

			actlen--;
			offset = 1;

			break;

		case MODEL_CY7C64013:
			if (actlen < 2) {
				goto tr_setup;
			}
			usbd_copy_out(pc, 0, buf, 2);

			sc->sc_ist = buf[0] & ~0x07;
			len = buf[1];

			actlen -= 2;
			offset = 2;

			break;

		default:
			DPRINTFN(0, "unsupported model number\n");
			goto tr_setup;
		}

		if (len > actlen)
			len = actlen;
		if (len)
			ucom_put_data(&sc->sc_ucom, pc, offset, len);
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, sc->sc_ilen);
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