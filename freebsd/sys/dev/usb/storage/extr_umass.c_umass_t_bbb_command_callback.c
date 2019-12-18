#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  union ccb {int dummy; } ccb ;
typedef  int /*<<< orphan*/  uint32_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_5__ {int bCDBLength; int CBWCDB; int /*<<< orphan*/  bCBWLUN; int /*<<< orphan*/  bCBWFlags; int /*<<< orphan*/  dCBWDataTransferLength; int /*<<< orphan*/  dCBWTag; int /*<<< orphan*/  dCBWSignature; } ;
struct TYPE_4__ {int cmd_len; int /*<<< orphan*/  cmd_data; int /*<<< orphan*/  lun; int /*<<< orphan*/  dir; int /*<<< orphan*/  data_len; union ccb* ccb; } ;
struct umass_softc {TYPE_2__ cbw; TYPE_1__ sc_transfer; int /*<<< orphan*/  sc_status_try; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBWFLAGS_IN ; 
 int /*<<< orphan*/  CBWFLAGS_OUT ; 
 int /*<<< orphan*/  CBWSIGNATURE ; 
 int /*<<< orphan*/  DIF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIR_IN ; 
 int /*<<< orphan*/  DIR_OUT ; 
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UDMASS_BBB ; 
 int /*<<< orphan*/  UGETDW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMASS_T_BBB_DATA_READ ; 
 int /*<<< orphan*/  UMASS_T_BBB_DATA_WRITE ; 
 int /*<<< orphan*/  UMASS_T_BBB_STATUS ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USETDW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umass_bbb_dump_cbw (struct umass_softc*,TYPE_2__*) ; 
 int /*<<< orphan*/  umass_tr_error (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umass_transfer_start (struct umass_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 struct umass_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
umass_t_bbb_command_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = usbd_xfer_softc(xfer);
	union ccb *ccb = sc->sc_transfer.ccb;
	struct usb_page_cache *pc;
	uint32_t tag;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		umass_transfer_start
		    (sc, ((sc->sc_transfer.dir == DIR_IN) ? UMASS_T_BBB_DATA_READ :
		    (sc->sc_transfer.dir == DIR_OUT) ? UMASS_T_BBB_DATA_WRITE :
		    UMASS_T_BBB_STATUS));
		return;

	case USB_ST_SETUP:

		sc->sc_status_try = 0;

		if (ccb) {

			/*
		         * the initial value is not important,
		         * as long as the values are unique:
		         */
			tag = UGETDW(sc->cbw.dCBWTag) + 1;

			USETDW(sc->cbw.dCBWSignature, CBWSIGNATURE);
			USETDW(sc->cbw.dCBWTag, tag);

			/*
		         * dCBWDataTransferLength:
		         *   This field indicates the number of bytes of data that the host
		         *   intends to transfer on the IN or OUT Bulk endpoint(as indicated by
		         *   the Direction bit) during the execution of this command. If this
		         *   field is set to 0, the device will expect that no data will be
		         *   transferred IN or OUT during this command, regardless of the value
		         *   of the Direction bit defined in dCBWFlags.
		         */
			USETDW(sc->cbw.dCBWDataTransferLength, sc->sc_transfer.data_len);

			/*
		         * dCBWFlags:
		         *   The bits of the Flags field are defined as follows:
		         *     Bits 0-6  reserved
		         *     Bit  7    Direction - this bit shall be ignored if the
		         *                           dCBWDataTransferLength field is zero.
		         *               0 = data Out from host to device
		         *               1 = data In from device to host
		         */
			sc->cbw.bCBWFlags = ((sc->sc_transfer.dir == DIR_IN) ?
			    CBWFLAGS_IN : CBWFLAGS_OUT);
			sc->cbw.bCBWLUN = sc->sc_transfer.lun;

			if (sc->sc_transfer.cmd_len > sizeof(sc->cbw.CBWCDB)) {
				sc->sc_transfer.cmd_len = sizeof(sc->cbw.CBWCDB);
				DPRINTF(sc, UDMASS_BBB, "Truncating long command!\n");
			}
			sc->cbw.bCDBLength = sc->sc_transfer.cmd_len;

			/* copy SCSI command data */
			memcpy(sc->cbw.CBWCDB, sc->sc_transfer.cmd_data,
			    sc->sc_transfer.cmd_len);

			/* clear remaining command area */
			memset(sc->cbw.CBWCDB +
			    sc->sc_transfer.cmd_len, 0,
			    sizeof(sc->cbw.CBWCDB) -
			    sc->sc_transfer.cmd_len);

			DIF(UDMASS_BBB, umass_bbb_dump_cbw(sc, &sc->cbw));

			pc = usbd_xfer_get_frame(xfer, 0);
			usbd_copy_in(pc, 0, &sc->cbw, sizeof(sc->cbw));
			usbd_xfer_set_frame_len(xfer, 0, sizeof(sc->cbw));

			usbd_transfer_submit(xfer);
		}
		return;

	default:			/* Error */
		umass_tr_error(xfer, error);
		return;
	}
}