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
struct usb_page_search {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct uhso_tty {size_t ht_muxport; } ;
struct uhso_softc {int /*<<< orphan*/ * sc_ucom; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  UCDC_SEND_ENCAPSULATED_COMMAND ; 
 int /*<<< orphan*/  UHSO_DPRINTF (int,char*,int,...) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 int /*<<< orphan*/  memset (struct usb_device_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ucom_get_data (int /*<<< orphan*/ *,struct usb_page_cache*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_page_search*) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int) ; 
 struct uhso_tty* usbd_xfer_get_priv (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct uhso_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uhso_mux_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct uhso_softc *sc = usbd_xfer_softc(xfer);
	struct uhso_tty *ht;
	struct usb_page_cache *pc;
	struct usb_device_request req;
	int actlen;
	struct usb_page_search res;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	ht = usbd_xfer_get_priv(xfer);
	UHSO_DPRINTF(3, "status=%d, using mux port %d\n",
	    USB_GET_STATE(xfer), ht->ht_muxport);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		UHSO_DPRINTF(3, "wrote %zd data bytes to muxport %d\n",
		    actlen - sizeof(struct usb_device_request) ,
		    ht->ht_muxport);
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		pc = usbd_xfer_get_frame(xfer, 1);
		if (ucom_get_data(&sc->sc_ucom[ht->ht_muxport], pc,
		    0, 32, &actlen)) {

			usbd_get_page(pc, 0, &res);

			memset(&req, 0, sizeof(struct usb_device_request));
			req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
			req.bRequest = UCDC_SEND_ENCAPSULATED_COMMAND;
			USETW(req.wValue, 0);
			USETW(req.wIndex, ht->ht_muxport);
			USETW(req.wLength, actlen);

			pc = usbd_xfer_get_frame(xfer, 0);
			usbd_copy_in(pc, 0, &req, sizeof(req));

			usbd_xfer_set_frame_len(xfer, 0, sizeof(req));
			usbd_xfer_set_frame_len(xfer, 1, actlen);
			usbd_xfer_set_frames(xfer, 2);

			UHSO_DPRINTF(3, "Prepared %d bytes for transmit "
			    "on muxport %d\n", actlen, ht->ht_muxport);

			usbd_transfer_submit(xfer);
		}
		break;
	default:
		UHSO_DPRINTF(0, "error: %s\n", usbd_errstr(error));
		if (error == USB_ERR_CANCELLED)
			break;
		usbd_xfer_set_stall(xfer);
		goto tr_setup;
	}
}