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
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/ * wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct ulpt_softc {int sc_last_status; int /*<<< orphan*/  sc_iface_no; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int LPS_INVERT ; 
 int LPS_MASK ; 
 int LPS_NERR ; 
 int LPS_NOPAPER ; 
 int LPS_SELECT ; 
 int /*<<< orphan*/  UR_GET_PORT_STATUS ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_READ_CLASS_INTERFACE ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 struct ulpt_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
ulpt_status_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ulpt_softc *sc = usbd_xfer_softc(xfer);
	struct usb_device_request req;
	struct usb_page_cache *pc;
	uint8_t cur_status;
	uint8_t new_status;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		pc = usbd_xfer_get_frame(xfer, 1);
		usbd_copy_out(pc, 0, &cur_status, 1);

		cur_status = (cur_status ^ LPS_INVERT) & LPS_MASK;
		new_status = cur_status & ~sc->sc_last_status;
		sc->sc_last_status = cur_status;

		if (new_status & LPS_SELECT)
			log(LOG_NOTICE, "%s: offline\n",
			    device_get_nameunit(sc->sc_dev));
		else if (new_status & LPS_NOPAPER)
			log(LOG_NOTICE, "%s: out of paper\n",
			    device_get_nameunit(sc->sc_dev));
		else if (new_status & LPS_NERR)
			log(LOG_NOTICE, "%s: output error\n",
			    device_get_nameunit(sc->sc_dev));
		break;

	case USB_ST_SETUP:
		req.bmRequestType = UT_READ_CLASS_INTERFACE;
		req.bRequest = UR_GET_PORT_STATUS;
		USETW(req.wValue, 0);
		req.wIndex[0] = sc->sc_iface_no;
		req.wIndex[1] = 0;
		USETW(req.wLength, 1);

		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_in(pc, 0, &req, sizeof(req));

		usbd_xfer_set_frame_len(xfer, 0, sizeof(req));
		usbd_xfer_set_frame_len(xfer, 1, 1);
		usbd_xfer_set_frames(xfer, 2);
		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		DPRINTF("error=%s\n", usbd_errstr(error));
		if (error != USB_ERR_CANCELLED) {
			/* wait for next watchdog timeout */
		}
		break;
	}
}