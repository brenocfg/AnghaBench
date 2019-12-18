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
struct usb_xfer {int dummy; } ;
struct cfumass_softc {int sc_current_stalled; int /*<<< orphan*/  sc_current_status; TYPE_1__* sc_csw; int /*<<< orphan*/  sc_current_residue; int /*<<< orphan*/  sc_current_tag; int /*<<< orphan*/ * sc_ctl_io; } ;
struct TYPE_2__ {int /*<<< orphan*/  bCSWStatus; int /*<<< orphan*/  dCSWDataResidue; int /*<<< orphan*/  dCSWTag; int /*<<< orphan*/  dCSWSignature; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFUMASS_DEBUG (struct cfumass_softc*,char*,...) ; 
 int /*<<< orphan*/  CFUMASS_T_COMMAND ; 
 int /*<<< orphan*/  CSWSIGNATURE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USETDW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfumass_transfer_start (struct cfumass_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct cfumass_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
cfumass_t_status_callback(struct usb_xfer *xfer, usb_error_t usb_error)
{
	struct cfumass_softc *sc;

	sc = usbd_xfer_softc(xfer);

	KASSERT(sc->sc_ctl_io == NULL,
	    ("sc_ctl_io is %p, should be NULL", sc->sc_ctl_io));

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		CFUMASS_DEBUG(sc, "USB_ST_TRANSFERRED");

		cfumass_transfer_start(sc, CFUMASS_T_COMMAND);
		break;

	case USB_ST_SETUP:
tr_setup:
		CFUMASS_DEBUG(sc, "USB_ST_SETUP");

		if (sc->sc_current_residue > 0 && !sc->sc_current_stalled) {
			CFUMASS_DEBUG(sc, "non-zero residue, stalling");
			usbd_xfer_set_stall(xfer);
			sc->sc_current_stalled = true;
		}

		USETDW(sc->sc_csw->dCSWSignature, CSWSIGNATURE);
		USETDW(sc->sc_csw->dCSWTag, sc->sc_current_tag);
		USETDW(sc->sc_csw->dCSWDataResidue, sc->sc_current_residue);
		sc->sc_csw->bCSWStatus = sc->sc_current_status;

		usbd_xfer_set_frame_len(xfer, 0, sizeof(*sc->sc_csw));
		usbd_transfer_submit(xfer);
		break;

	default:
		if (usb_error == USB_ERR_CANCELLED) {
			CFUMASS_DEBUG(sc, "USB_ERR_CANCELLED");
			break;
		}

		CFUMASS_DEBUG(sc, "USB_ST_ERROR: %s",
		    usbd_errstr(usb_error));

		goto tr_setup;
	}
}