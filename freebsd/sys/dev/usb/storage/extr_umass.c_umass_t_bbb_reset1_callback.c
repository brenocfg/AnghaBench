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
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/ * wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct umass_softc {int /*<<< orphan*/  sc_iface_no; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UDMASS_BBB ; 
 int /*<<< orphan*/  UMASS_T_BBB_RESET2 ; 
 int /*<<< orphan*/  UR_BBB_RESET ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 int /*<<< orphan*/  umass_tr_error (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umass_transfer_start (struct umass_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 struct umass_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
umass_t_bbb_reset1_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = usbd_xfer_softc(xfer);
	struct usb_device_request req;
	struct usb_page_cache *pc;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		umass_transfer_start(sc, UMASS_T_BBB_RESET2);
		return;

	case USB_ST_SETUP:
		/*
		 * Reset recovery (5.3.4 in Universal Serial Bus Mass Storage Class)
		 *
		 * For Reset Recovery the host shall issue in the following order:
		 * a) a Bulk-Only Mass Storage Reset
		 * b) a Clear Feature HALT to the Bulk-In endpoint
		 * c) a Clear Feature HALT to the Bulk-Out endpoint
		 *
		 * This is done in 3 steps, using 3 transfers:
		 * UMASS_T_BBB_RESET1
		 * UMASS_T_BBB_RESET2
		 * UMASS_T_BBB_RESET3
		 */

		DPRINTF(sc, UDMASS_BBB, "BBB reset!\n");

		req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
		req.bRequest = UR_BBB_RESET;	/* bulk only reset */
		USETW(req.wValue, 0);
		req.wIndex[0] = sc->sc_iface_no;
		req.wIndex[1] = 0;
		USETW(req.wLength, 0);

		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_in(pc, 0, &req, sizeof(req));

		usbd_xfer_set_frame_len(xfer, 0, sizeof(req));
		usbd_xfer_set_frames(xfer, 1);
		usbd_transfer_submit(xfer);
		return;

	default:			/* Error */
		umass_tr_error(xfer, error);
		return;
	}
}