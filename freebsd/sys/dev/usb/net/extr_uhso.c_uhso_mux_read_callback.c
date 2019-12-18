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
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct uhso_tty {size_t ht_muxport; int /*<<< orphan*/  ht_open; } ;
struct uhso_softc {int /*<<< orphan*/ * sc_ucom; int /*<<< orphan*/ * sc_xfer; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  UCDC_GET_ENCAPSULATED_RESPONSE ; 
 int /*<<< orphan*/  UHSO_DPRINTF (int,char*,...) ; 
 size_t UHSO_MUX_ENDPT_INTR ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_READ_CLASS_INTERFACE ; 
 int /*<<< orphan*/  memset (struct usb_device_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ucom_put_data (int /*<<< orphan*/ *,struct usb_page_cache*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 
 int usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int usbd_xfer_frame_len (struct usb_xfer*,int) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int) ; 
 struct uhso_tty* usbd_xfer_get_priv (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct uhso_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uhso_mux_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct uhso_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	struct usb_device_request req;
	struct uhso_tty *ht;
	int actlen, len;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	UHSO_DPRINTF(3, "status %d\n", USB_GET_STATE(xfer));

	ht = usbd_xfer_get_priv(xfer);
	UHSO_DPRINTF(3, "ht=%p open=%d\n", ht, ht->ht_open);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		/* Got data, send to ucom */
		pc = usbd_xfer_get_frame(xfer, 1);
		len = usbd_xfer_frame_len(xfer, 1);

		UHSO_DPRINTF(3, "got %d bytes on mux port %d\n", len,
		    ht->ht_muxport);
		if (len <= 0) {
			usbd_transfer_start(sc->sc_xfer[UHSO_MUX_ENDPT_INTR]);
			break;
		}

		/* Deliver data if the TTY is open, discard otherwise */
		if (ht->ht_open)
			ucom_put_data(&sc->sc_ucom[ht->ht_muxport], pc, 0, len);
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		memset(&req, 0, sizeof(struct usb_device_request));
		req.bmRequestType = UT_READ_CLASS_INTERFACE;
		req.bRequest = UCDC_GET_ENCAPSULATED_RESPONSE;
		USETW(req.wValue, 0);
		USETW(req.wIndex, ht->ht_muxport);
		USETW(req.wLength, 1024);

		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_in(pc, 0, &req, sizeof(req));

		usbd_xfer_set_frame_len(xfer, 0, sizeof(req));
		usbd_xfer_set_frame_len(xfer, 1, 1024);
		usbd_xfer_set_frames(xfer, 2);
		usbd_transfer_submit(xfer);
		break;
	default:
		UHSO_DPRINTF(0, "error: %s\n", usbd_errstr(error));
		if (error == USB_ERR_CANCELLED)
			break;
		usbd_xfer_set_stall(xfer);
		goto tr_setup;
	}
}