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
typedef  size_t uint8_t ;
struct usb_xfer {int dummy; } ;
struct umass_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 size_t UMASS_T_CBI_STATUS ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  umass_cbi_start_status (struct umass_softc*) ; 
 int /*<<< orphan*/  umass_tr_error (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umass_transfer_start (struct umass_softc*,size_t) ; 
 int /*<<< orphan*/  usbd_clear_stall_callback (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 struct umass_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
umass_t_cbi_data_clear_stall_callback(struct usb_xfer *xfer,
    uint8_t next_xfer, uint8_t stall_xfer, usb_error_t error)
{
	struct umass_softc *sc = usbd_xfer_softc(xfer);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
tr_transferred:
		if (next_xfer == UMASS_T_CBI_STATUS) {
			umass_cbi_start_status(sc);
		} else {
			umass_transfer_start(sc, next_xfer);
		}
		break;

	case USB_ST_SETUP:
		if (usbd_clear_stall_callback(xfer, sc->sc_xfer[stall_xfer])) {
			goto tr_transferred;	/* should not happen */
		}
		break;

	default:			/* Error */
		umass_tr_error(xfer, error);
		break;
	}
}