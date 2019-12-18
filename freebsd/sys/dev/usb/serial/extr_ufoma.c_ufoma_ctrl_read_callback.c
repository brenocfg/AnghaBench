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
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct ufoma_softc {int sc_ctrl_iface_no; int /*<<< orphan*/  sc_num_msg; int /*<<< orphan*/  sc_ucom; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UCDC_GET_ENCAPSULATED_RESPONSE ; 
 int UFOMA_CMD_BUF_SIZE ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_READ_CLASS_INTERFACE ; 
 int /*<<< orphan*/  ucom_put_data (int /*<<< orphan*/ *,struct usb_page_cache*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int usbd_xfer_frame_len (struct usb_xfer*,int) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 struct ufoma_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static void
ufoma_ctrl_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ufoma_softc *sc = usbd_xfer_softc(xfer);
	struct usb_device_request req;
	struct usb_page_cache *pc0, *pc1;
	int len, aframes, nframes;

	usbd_xfer_status(xfer, NULL, NULL, &aframes, &nframes);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
tr_transferred:
		if (aframes != nframes)
			goto tr_setup;
		pc1 = usbd_xfer_get_frame(xfer, 1);
		len = usbd_xfer_frame_len(xfer, 1);
		if (len > 0)
			ucom_put_data(&sc->sc_ucom, pc1, 0, len);
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		if (sc->sc_num_msg) {
			sc->sc_num_msg--;

			req.bmRequestType = UT_READ_CLASS_INTERFACE;
			req.bRequest = UCDC_GET_ENCAPSULATED_RESPONSE;
			USETW(req.wIndex, sc->sc_ctrl_iface_no);
			USETW(req.wValue, 0);
			USETW(req.wLength, UFOMA_CMD_BUF_SIZE);

			pc0 = usbd_xfer_get_frame(xfer, 0);
			usbd_copy_in(pc0, 0, &req, sizeof(req));

			usbd_xfer_set_frame_len(xfer, 0, sizeof(req));
			usbd_xfer_set_frame_len(xfer, 1, UFOMA_CMD_BUF_SIZE);
			usbd_xfer_set_frames(xfer, 2);
			usbd_transfer_submit(xfer);
		}
		return;

	default:			/* Error */
		DPRINTF("error = %s\n",
		    usbd_errstr(error));

		if (error == USB_ERR_CANCELLED) {
			return;
		}
		goto tr_transferred;
	}
}