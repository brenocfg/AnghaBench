#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int status; int /*<<< orphan*/  path; int /*<<< orphan*/  timeout; int /*<<< orphan*/  func_code; } ;
struct TYPE_9__ {int /*<<< orphan*/  error_code; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cdb_bytes; } ;
struct ccb_scsiio {int /*<<< orphan*/  sense_len; TYPE_4__ sense_data; scalar_t__ data_ptr; TYPE_1__ cdb_io; int /*<<< orphan*/  resid; } ;
union ccb {TYPE_5__ ccb_h; struct ccb_scsiio csio; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int* cmd_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  opcode; int /*<<< orphan*/  length; } ;
struct umass_softc {int sc_quirks; TYPE_3__ sc_transfer; TYPE_2__ cam_scsi_sense; int /*<<< orphan*/  sc_udev; } ;
struct scsi_vpd_supported_page_list {size_t length; int /*<<< orphan*/ * list; } ;
struct scsi_read_capacity_data {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int CAM_DEV_QFRZN ; 
 int CAM_REQ_CMP ; 
 int CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  DIR_IN ; 
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int FORCE_SHORT_INQUIRY ; 
 int INQUIRY ; 
 int /*<<< orphan*/  READ_CAPACITY ; 
 int READ_CAPACITY_OFFBY1 ; 
 int /*<<< orphan*/  SHORT_INQUIRY_LENGTH ; 
 int SI_EVPD ; 
#define  STATUS_CMD_FAILED 130 
#define  STATUS_CMD_OK 129 
#define  STATUS_CMD_UNKNOWN 128 
 int /*<<< orphan*/  SVPD_SUPPORTED_PAGES_SIZE ; 
 int SVPD_SUPPORTED_PAGE_LIST ; 
 int /*<<< orphan*/  SVPD_UNIT_SERIAL_NUMBER ; 
 int /*<<< orphan*/  UDMASS_SCSI ; 
 int /*<<< orphan*/  XPT_SCSI_IO ; 
 int /*<<< orphan*/  scsi_4btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umass_cam_sense_cb ; 
 int /*<<< orphan*/  umass_command_start (struct umass_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union ccb*) ; 
 int /*<<< orphan*/  umass_std_transform (struct umass_softc*,union ccb*,int /*<<< orphan*/ *,int) ; 
 char* usb_get_serial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
umass_cam_cb(struct umass_softc *sc, union ccb *ccb, uint32_t residue,
    uint8_t status)
{
	ccb->csio.resid = residue;

	switch (status) {
	case STATUS_CMD_OK:
		ccb->ccb_h.status = CAM_REQ_CMP;
		if ((sc->sc_quirks & READ_CAPACITY_OFFBY1) &&
		    (ccb->ccb_h.func_code == XPT_SCSI_IO) &&
		    (ccb->csio.cdb_io.cdb_bytes[0] == READ_CAPACITY)) {
			struct scsi_read_capacity_data *rcap;
			uint32_t maxsector;

			rcap = (void *)(ccb->csio.data_ptr);
			maxsector = scsi_4btoul(rcap->addr) - 1;
			scsi_ulto4b(maxsector, rcap->addr);
		}
		/*
		 * We have to add SVPD_UNIT_SERIAL_NUMBER to the list
		 * of pages supported by the device - otherwise, CAM
		 * will never ask us for the serial number if the
		 * device cannot handle that by itself.
		 */
		if (ccb->ccb_h.func_code == XPT_SCSI_IO &&
		    sc->sc_transfer.cmd_data[0] == INQUIRY &&
		    (sc->sc_transfer.cmd_data[1] & SI_EVPD) &&
		    sc->sc_transfer.cmd_data[2] == SVPD_SUPPORTED_PAGE_LIST &&
		    (usb_get_serial(sc->sc_udev)[0] != '\0')) {
			struct ccb_scsiio *csio;
			struct scsi_vpd_supported_page_list *page_list;

			csio = &ccb->csio;
			page_list = (struct scsi_vpd_supported_page_list *)csio->data_ptr;
			if (page_list->length + 1 < SVPD_SUPPORTED_PAGES_SIZE) {
				page_list->list[page_list->length] = SVPD_UNIT_SERIAL_NUMBER;
				page_list->length++;
			}
		}
		xpt_done(ccb);
		break;

	case STATUS_CMD_UNKNOWN:
	case STATUS_CMD_FAILED:

		/* fetch sense data */

		/* the rest of the command was filled in at attach */
		sc->cam_scsi_sense.length = ccb->csio.sense_len;

		DPRINTF(sc, UDMASS_SCSI, "Fetching %d bytes of "
		    "sense data\n", ccb->csio.sense_len);

		if (umass_std_transform(sc, ccb, &sc->cam_scsi_sense.opcode,
		    sizeof(sc->cam_scsi_sense))) {

			if ((sc->sc_quirks & FORCE_SHORT_INQUIRY) &&
			    (sc->sc_transfer.cmd_data[0] == INQUIRY)) {
				ccb->csio.sense_len = SHORT_INQUIRY_LENGTH;
			}
			umass_command_start(sc, DIR_IN, &ccb->csio.sense_data.error_code,
			    ccb->csio.sense_len, ccb->ccb_h.timeout,
			    &umass_cam_sense_cb, ccb);
		}
		break;

	default:
		/*
		 * The wire protocol failed and will hopefully have
		 * recovered. We return an error to CAM and let CAM
		 * retry the command if necessary.
		 */
		xpt_freeze_devq(ccb->ccb_h.path, 1);
		ccb->ccb_h.status = CAM_REQ_CMP_ERR | CAM_DEV_QFRZN;
		xpt_done(ccb);
		break;
	}
}