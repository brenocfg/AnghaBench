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
typedef  int uint32_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct ucom_softc {int dummy; } ;

/* Variables and functions */
 int U3G_TXFRAMES ; 
 int U3G_TXSIZE ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  ucom_get_data (struct ucom_softc*,struct usb_page_cache*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_offset (struct usb_xfer*,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ucom_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
u3g_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ucom_softc *ucom = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	uint32_t actlen;
	uint32_t frame;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
	case USB_ST_SETUP:
tr_setup:
		for (frame = 0; frame != U3G_TXFRAMES; frame++) {
			usbd_xfer_set_frame_offset(xfer, frame * U3G_TXSIZE, frame);

			pc = usbd_xfer_get_frame(xfer, frame);
			if (ucom_get_data(ucom, pc, 0, U3G_TXSIZE, &actlen) == 0)
				break;
			usbd_xfer_set_frame_len(xfer, frame, actlen);
		}
		if (frame != 0) {
			usbd_xfer_set_frames(xfer, frame);
			usbd_transfer_submit(xfer);
		}
		break;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			/* do a builtin clear-stall */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		break;
	}
}