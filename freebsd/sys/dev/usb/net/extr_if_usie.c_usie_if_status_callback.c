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
struct usie_softc {int /*<<< orphan*/  sc_if_status_task; } ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct usb_cdc_notification {int bNotification; } ;
typedef  int /*<<< orphan*/  cdc ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 int UCDC_N_RESPONSE_AVAILABLE ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_cdc_notification*,int) ; 
 int usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct usie_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
usie_if_status_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct usie_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	struct usb_cdc_notification cdc;
	uint32_t actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTFN(4, "info received, actlen=%d\n", actlen);

		/* usb_cdc_notification - .data[16] */
		if (actlen < (sizeof(cdc) - 16)) {
			DPRINTF("data too short %d\n", actlen);
			goto tr_setup;
		}
		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_out(pc, 0, &cdc, (sizeof(cdc) - 16));

		DPRINTFN(4, "bNotification=%x\n", cdc.bNotification);

		if (cdc.bNotification & UCDC_N_RESPONSE_AVAILABLE) {
			taskqueue_enqueue(taskqueue_thread,
			    &sc->sc_if_status_task);
		}
		/* fall though */
	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		DPRINTF("USB transfer error, %s\n",
		    usbd_errstr(error));

		if (error != USB_ERR_CANCELLED) {
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		break;
	}
}