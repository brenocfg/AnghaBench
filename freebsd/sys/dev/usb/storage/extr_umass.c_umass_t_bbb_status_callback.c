#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  union ccb {int dummy; } ccb ;
typedef  int uint32_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_7__ {int data_len; int actlen; int /*<<< orphan*/  (* callback ) (struct umass_softc*,union ccb*,int,int /*<<< orphan*/ ) ;union ccb* ccb; } ;
struct TYPE_8__ {int bCSWStatus; int /*<<< orphan*/  dCSWTag; int /*<<< orphan*/  dCSWSignature; int /*<<< orphan*/  dCSWDataResidue; } ;
struct TYPE_6__ {int /*<<< orphan*/  dCBWTag; } ;
struct umass_softc {int sc_status_try; int sc_quirks; TYPE_2__ sc_transfer; void* sc_last_xfer_index; TYPE_3__ csw; TYPE_1__ cbw; } ;

/* Variables and functions */
 int CSWSIGNATURE ; 
 int CSWSIGNATURE_IMAGINATION_DBX1 ; 
 int CSWSIGNATURE_OLYMPUS_C1 ; 
 int CSWSTATUS_FAILED ; 
 int CSWSTATUS_PHASE ; 
 int /*<<< orphan*/  DIF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*,int,...) ; 
 int IGNORE_RESIDUE ; 
 int /*<<< orphan*/  STATUS_CMD_FAILED ; 
 int /*<<< orphan*/  STATUS_CMD_OK ; 
 int /*<<< orphan*/  UDMASS_BBB ; 
 int UGETDW (int /*<<< orphan*/ ) ; 
 void* UMASS_T_BBB_COMMAND ; 
 int /*<<< orphan*/  UMASS_T_BBB_DATA_RD_CS ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USETDW (int /*<<< orphan*/ ,int) ; 
 int WRONG_CSWSIG ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct umass_softc*,union ccb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct umass_softc*,union ccb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umass_bbb_dump_csw (struct umass_softc*,TYPE_3__*) ; 
 int /*<<< orphan*/  umass_tr_error (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umass_transfer_start (struct umass_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct umass_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
umass_t_bbb_status_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = usbd_xfer_softc(xfer);
	union ccb *ccb = sc->sc_transfer.ccb;
	struct usb_page_cache *pc;
	uint32_t residue;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		/*
		 * Do a full reset if there is something wrong with the CSW:
		 */
		sc->sc_status_try = 1;

		/* Zero missing parts of the CSW: */

		if (actlen < (int)sizeof(sc->csw))
			memset(&sc->csw, 0, sizeof(sc->csw));

		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_out(pc, 0, &sc->csw, actlen);

		DIF(UDMASS_BBB, umass_bbb_dump_csw(sc, &sc->csw));

		residue = UGETDW(sc->csw.dCSWDataResidue);

		if ((!residue) || (sc->sc_quirks & IGNORE_RESIDUE)) {
			residue = (sc->sc_transfer.data_len -
			    sc->sc_transfer.actlen);
		}
		if (residue > sc->sc_transfer.data_len) {
			DPRINTF(sc, UDMASS_BBB, "truncating residue from %d "
			    "to %d bytes\n", residue, sc->sc_transfer.data_len);
			residue = sc->sc_transfer.data_len;
		}
		/* translate weird command-status signatures: */
		if (sc->sc_quirks & WRONG_CSWSIG) {

			uint32_t temp = UGETDW(sc->csw.dCSWSignature);

			if ((temp == CSWSIGNATURE_OLYMPUS_C1) ||
			    (temp == CSWSIGNATURE_IMAGINATION_DBX1)) {
				USETDW(sc->csw.dCSWSignature, CSWSIGNATURE);
			}
		}
		/* check CSW and handle eventual error */
		if (UGETDW(sc->csw.dCSWSignature) != CSWSIGNATURE) {
			DPRINTF(sc, UDMASS_BBB, "bad CSW signature 0x%08x != 0x%08x\n",
			    UGETDW(sc->csw.dCSWSignature), CSWSIGNATURE);
			/*
			 * Invalid CSW: Wrong signature or wrong tag might
			 * indicate that we lost synchronization. Reset the
			 * device.
			 */
			goto tr_error;
		} else if (UGETDW(sc->csw.dCSWTag) != UGETDW(sc->cbw.dCBWTag)) {
			DPRINTF(sc, UDMASS_BBB, "Invalid CSW: tag 0x%08x should be "
			    "0x%08x\n", UGETDW(sc->csw.dCSWTag),
			    UGETDW(sc->cbw.dCBWTag));
			goto tr_error;
		} else if (sc->csw.bCSWStatus > CSWSTATUS_PHASE) {
			DPRINTF(sc, UDMASS_BBB, "Invalid CSW: status %d > %d\n",
			    sc->csw.bCSWStatus, CSWSTATUS_PHASE);
			goto tr_error;
		} else if (sc->csw.bCSWStatus == CSWSTATUS_PHASE) {
			DPRINTF(sc, UDMASS_BBB, "Phase error, residue = "
			    "%d\n", residue);
			goto tr_error;
		} else if (sc->sc_transfer.actlen > sc->sc_transfer.data_len) {
			DPRINTF(sc, UDMASS_BBB, "Buffer overrun %d > %d\n",
			    sc->sc_transfer.actlen, sc->sc_transfer.data_len);
			goto tr_error;
		} else if (sc->csw.bCSWStatus == CSWSTATUS_FAILED) {
			DPRINTF(sc, UDMASS_BBB, "Command failed, residue = "
			    "%d\n", residue);

			sc->sc_transfer.ccb = NULL;

			sc->sc_last_xfer_index = UMASS_T_BBB_COMMAND;

			(sc->sc_transfer.callback)
			    (sc, ccb, residue, STATUS_CMD_FAILED);
		} else {
			sc->sc_transfer.ccb = NULL;

			sc->sc_last_xfer_index = UMASS_T_BBB_COMMAND;

			(sc->sc_transfer.callback)
			    (sc, ccb, residue, STATUS_CMD_OK);
		}
		return;

	case USB_ST_SETUP:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		return;

	default:
tr_error:
		DPRINTF(sc, UDMASS_BBB, "Failed to read CSW: %s, try %d\n",
		    usbd_errstr(error), sc->sc_status_try);

		if ((error == USB_ERR_CANCELLED) ||
		    (sc->sc_status_try)) {
			umass_tr_error(xfer, error);
		} else {
			sc->sc_status_try = 1;
			umass_transfer_start(sc, UMASS_T_BBB_DATA_RD_CS);
		}
		return;
	}
}