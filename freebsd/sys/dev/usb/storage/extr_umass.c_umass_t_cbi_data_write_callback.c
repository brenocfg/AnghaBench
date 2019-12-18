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
struct TYPE_2__ {int data_rem; int data_ptr; int actlen; int /*<<< orphan*/ * callback; int /*<<< orphan*/  data_timeout; } ;
struct umass_softc {TYPE_1__ sc_transfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  UDMASS_CBI ; 
 int /*<<< orphan*/  UMASS_T_CBI_DATA_WR_CS ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  umass_cam_cb ; 
 int /*<<< orphan*/  umass_cbi_start_status (struct umass_softc*) ; 
 int /*<<< orphan*/  umass_tr_error (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umass_transfer_start (struct umass_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_timeout (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 struct umass_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
umass_t_cbi_data_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = usbd_xfer_softc(xfer);
	uint32_t max_bulk = usbd_xfer_max_len(xfer);
	int actlen, sumlen;

	usbd_xfer_status(xfer, &actlen, &sumlen, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		sc->sc_transfer.data_rem -= actlen;
		sc->sc_transfer.data_ptr += actlen;
		sc->sc_transfer.actlen += actlen;

		if (actlen < sumlen) {
			/* short transfer */
			sc->sc_transfer.data_rem = 0;
		}
	case USB_ST_SETUP:
		DPRINTF(sc, UDMASS_CBI, "max_bulk=%d, data_rem=%d\n",
		    max_bulk, sc->sc_transfer.data_rem);

		if (sc->sc_transfer.data_rem == 0) {
			umass_cbi_start_status(sc);
			break;
		}
		if (max_bulk > sc->sc_transfer.data_rem) {
			max_bulk = sc->sc_transfer.data_rem;
		}
		usbd_xfer_set_timeout(xfer, sc->sc_transfer.data_timeout);

		usbd_xfer_set_frame_data(xfer, 0, sc->sc_transfer.data_ptr,
		    max_bulk);

		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		if ((error == USB_ERR_CANCELLED) ||
		    (sc->sc_transfer.callback != &umass_cam_cb)) {
			umass_tr_error(xfer, error);
		} else {
			umass_transfer_start(sc, UMASS_T_CBI_DATA_WR_CS);
		}
		break;
	}
}