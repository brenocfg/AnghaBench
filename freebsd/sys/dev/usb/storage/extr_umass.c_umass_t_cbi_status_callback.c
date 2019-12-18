#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  union ccb {int dummy; } ccb ;
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* callback ) (struct umass_softc*,union ccb*,scalar_t__,int) ;union ccb* ccb; scalar_t__ actlen; scalar_t__ data_len; } ;
struct TYPE_6__ {int value; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  ascq; int /*<<< orphan*/  asc; } ;
struct TYPE_8__ {TYPE_2__ common; TYPE_1__ ufi; } ;
struct umass_softc {int sc_proto; TYPE_3__ sc_transfer; void* sc_last_xfer_index; TYPE_4__ sbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  IDB_TYPE_CCI ; 
 int IDB_VALUE_FAIL ; 
 int IDB_VALUE_PASS ; 
 int IDB_VALUE_PERSISTENT ; 
 int IDB_VALUE_STATUS_MASK ; 
 int STATUS_CMD_FAILED ; 
 int STATUS_CMD_OK ; 
 int STATUS_WIRE_FAILED ; 
 int /*<<< orphan*/  UDMASS_CBI ; 
 int UMASS_PROTO_UFI ; 
 void* UMASS_T_CBI_COMMAND ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  stub1 (struct umass_softc*,union ccb*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub2 (struct umass_softc*,union ccb*,scalar_t__,int) ; 
 int /*<<< orphan*/  umass_tr_error (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct umass_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
umass_t_cbi_status_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = usbd_xfer_softc(xfer);
	union ccb *ccb = sc->sc_transfer.ccb;
	struct usb_page_cache *pc;
	uint32_t residue;
	uint8_t status;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		if (actlen < (int)sizeof(sc->sbl)) {
			goto tr_setup;
		}
		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_out(pc, 0, &sc->sbl, sizeof(sc->sbl));

		residue = (sc->sc_transfer.data_len -
		    sc->sc_transfer.actlen);

		/* dissect the information in the buffer */

		if (sc->sc_proto & UMASS_PROTO_UFI) {

			/*
			 * Section 3.4.3.1.3 specifies that the UFI command
			 * protocol returns an ASC and ASCQ in the interrupt
			 * data block.
			 */

			DPRINTF(sc, UDMASS_CBI, "UFI CCI, ASC = 0x%02x, "
			    "ASCQ = 0x%02x\n", sc->sbl.ufi.asc,
			    sc->sbl.ufi.ascq);

			status = (((sc->sbl.ufi.asc == 0) &&
			    (sc->sbl.ufi.ascq == 0)) ?
			    STATUS_CMD_OK : STATUS_CMD_FAILED);

			sc->sc_transfer.ccb = NULL;

			sc->sc_last_xfer_index = UMASS_T_CBI_COMMAND;

			(sc->sc_transfer.callback)
			    (sc, ccb, residue, status);

			break;

		} else {

			/* Command Interrupt Data Block */

			DPRINTF(sc, UDMASS_CBI, "type=0x%02x, value=0x%02x\n",
			    sc->sbl.common.type, sc->sbl.common.value);

			if (sc->sbl.common.type == IDB_TYPE_CCI) {

				status = (sc->sbl.common.value & IDB_VALUE_STATUS_MASK);

				status = ((status == IDB_VALUE_PASS) ? STATUS_CMD_OK :
				    (status == IDB_VALUE_FAIL) ? STATUS_CMD_FAILED :
				    (status == IDB_VALUE_PERSISTENT) ? STATUS_CMD_FAILED :
				    STATUS_WIRE_FAILED);

				sc->sc_transfer.ccb = NULL;

				sc->sc_last_xfer_index = UMASS_T_CBI_COMMAND;

				(sc->sc_transfer.callback)
				    (sc, ccb, residue, status);

				break;
			}
		}

		/* fallthrough */

	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		DPRINTF(sc, UDMASS_CBI, "Failed to read CSW: %s\n",
		    usbd_errstr(error));
		umass_tr_error(xfer, error);
		break;
	}
}