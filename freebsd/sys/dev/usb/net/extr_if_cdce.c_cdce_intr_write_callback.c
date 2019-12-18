#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint32_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct usb_cdc_notification {int /*<<< orphan*/  data; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/ * wIndex; int /*<<< orphan*/  bNotification; void* bmRequestType; } ;
struct TYPE_2__ {int /*<<< orphan*/  ue_udev; } ;
struct cdce_softc {int sc_notify_state; TYPE_1__ sc_ue; int /*<<< orphan*/ * sc_ifaces_index; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int CDCE_NOTIFY_DONE ; 
#define  CDCE_NOTIFY_NETWORK_CONNECTION 131 
#define  CDCE_NOTIFY_SPEED_CHANGE 130 
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 void* UCDC_NOTIFICATION ; 
 int /*<<< orphan*/  UCDC_N_CONNECTION_SPEED_CHANGE ; 
 int /*<<< orphan*/  UCDC_N_NETWORK_CONNECTION ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
 int /*<<< orphan*/  USB_MODE_HOST ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USETDW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_cdc_notification*,int) ; 
 int /*<<< orphan*/  usbd_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_get_speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct cdce_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cdce_intr_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct cdce_softc *sc = usbd_xfer_softc(xfer);
	struct usb_cdc_notification req;
	struct usb_page_cache *pc;
	uint32_t speed;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		DPRINTF("Transferred %d bytes\n", actlen);

		switch (sc->sc_notify_state) {
		case CDCE_NOTIFY_NETWORK_CONNECTION:
			sc->sc_notify_state = CDCE_NOTIFY_SPEED_CHANGE;
			break;
		case CDCE_NOTIFY_SPEED_CHANGE:
			sc->sc_notify_state = CDCE_NOTIFY_DONE;
			break;
		default:
			break;
		}

		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		/*
		 * Inform host about connection. Required according to USB CDC
		 * specification and communicating to Mac OS X USB host stack.
		 * Some of the values seems ignored by Mac OS X though.
		 */
		if (sc->sc_notify_state == CDCE_NOTIFY_NETWORK_CONNECTION) {
			req.bmRequestType = UCDC_NOTIFICATION;
			req.bNotification = UCDC_N_NETWORK_CONNECTION;
			req.wIndex[0] = sc->sc_ifaces_index[1];
			req.wIndex[1] = 0;
			USETW(req.wValue, 1); /* Connected */
			USETW(req.wLength, 0);

			pc = usbd_xfer_get_frame(xfer, 0);
			usbd_copy_in(pc, 0, &req, sizeof(req));
			usbd_xfer_set_frame_len(xfer, 0, sizeof(req));
			usbd_xfer_set_frames(xfer, 1);
			usbd_transfer_submit(xfer); 

		} else if (sc->sc_notify_state == CDCE_NOTIFY_SPEED_CHANGE) {
			req.bmRequestType = UCDC_NOTIFICATION;
			req.bNotification = UCDC_N_CONNECTION_SPEED_CHANGE;
			req.wIndex[0] = sc->sc_ifaces_index[1];
			req.wIndex[1] = 0;
			USETW(req.wValue, 0);
			USETW(req.wLength, 8);

			/* Peak theoretical bulk trasfer rate in bits/s */
			if (usbd_get_speed(sc->sc_ue.ue_udev) != USB_SPEED_FULL)
				speed = (13 * 512 * 8 * 1000 * 8);
			else
				speed = (19 * 64 * 1 * 1000 * 8);

			USETDW(req.data + 0, speed); /* Upstream bit rate */
			USETDW(req.data + 4, speed); /* Downstream bit rate */
 
			pc = usbd_xfer_get_frame(xfer, 0);
			usbd_copy_in(pc, 0, &req, sizeof(req));
			usbd_xfer_set_frame_len(xfer, 0, sizeof(req));
			usbd_xfer_set_frames(xfer, 1);
			usbd_transfer_submit(xfer); 
		}
		break;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			if (usbd_get_mode(sc->sc_ue.ue_udev) == USB_MODE_HOST) {
				/* start clear stall */
				usbd_xfer_set_stall(xfer);
			}
			goto tr_setup;
		}
		break;
	}
}