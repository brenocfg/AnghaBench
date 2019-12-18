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
struct usie_softc {int /*<<< orphan*/ * sc_resp_temp; struct ucom_softc* sc_ucom; } ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct ucom_softc {struct usie_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int USIE_BUFSIZE ; 
 int USIE_HIPCNS_MIN ; 
 int /*<<< orphan*/  USIE_HIP_FRM_CHR ; 
 int /*<<< orphan*/  ucom_put_data (struct ucom_softc*,struct usb_page_cache*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ucom_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usie_hip_rsp (struct usie_softc*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
usie_uc_rx_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ucom_softc *ucom = usbd_xfer_softc(xfer);
	struct usie_softc *sc = ucom->sc_parent;
	struct usb_page_cache *pc;
	uint32_t actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		pc = usbd_xfer_get_frame(xfer, 0);

		/* handle CnS response */
		if (ucom == sc->sc_ucom && actlen >= USIE_HIPCNS_MIN) {

			DPRINTF("transferred=%u\n", actlen);

			/* check if it is really CnS reply */
			usbd_copy_out(pc, 0, sc->sc_resp_temp, 1);

			if (sc->sc_resp_temp[0] == USIE_HIP_FRM_CHR) {

				/* verify actlen */
				if (actlen > USIE_BUFSIZE)
					actlen = USIE_BUFSIZE;

				/* get complete message */
				usbd_copy_out(pc, 0, sc->sc_resp_temp, actlen);
				usie_hip_rsp(sc, sc->sc_resp_temp, actlen);

				/* need to fall though */
				goto tr_setup;
			}
			/* else call ucom_put_data() */
		}
		/* standard ucom transfer */
		ucom_put_data(ucom, pc, 0, actlen);

		/* fall though */
	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		break;
	}
}