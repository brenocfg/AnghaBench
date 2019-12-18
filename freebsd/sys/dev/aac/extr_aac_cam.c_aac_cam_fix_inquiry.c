#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; scalar_t__ status; scalar_t__ target_lun; } ;
struct TYPE_4__ {scalar_t__* cdb_bytes; scalar_t__* cdb_ptr; } ;
struct TYPE_5__ {scalar_t__* data_ptr; TYPE_1__ cdb_io; } ;
union ccb {TYPE_3__ ccb_h; TYPE_2__ csio; } ;
typedef  scalar_t__ uint8_t ;
struct scsi_inquiry_data {int dummy; } ;
struct aac_softc {int flags; } ;

/* Variables and functions */
 int AAC_FLAGS_CAM_PASSONLY ; 
 int CAM_CDB_POINTER ; 
 scalar_t__ CAM_DEV_NOT_THERE ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SEL_TIMEOUT ; 
 scalar_t__ INQUIRY ; 
 scalar_t__ SID_QUAL (struct scsi_inquiry_data*) ; 
 scalar_t__ SID_QUAL_LU_CONNECTED ; 
 scalar_t__ SID_QUAL_LU_OFFLINE ; 
 scalar_t__ SID_TYPE (struct scsi_inquiry_data*) ; 
 scalar_t__ SI_EVPD ; 
 scalar_t__ T_DIRECT ; 
 scalar_t__ T_NODEVICE ; 
 scalar_t__ T_PROCESSOR ; 

__attribute__((used)) static void
aac_cam_fix_inquiry(struct aac_softc *sc, union ccb *ccb)
{
	struct scsi_inquiry_data *inq;
	uint8_t *data;
	uint8_t device, qual;

	/* If this is an inquiry command, fake things out */
	if (ccb->ccb_h.flags & CAM_CDB_POINTER)
		data = ccb->csio.cdb_io.cdb_ptr;
	else
		data = ccb->csio.cdb_io.cdb_bytes;

	if (data[0] != INQUIRY)
		return;

	if (ccb->ccb_h.status == CAM_REQ_CMP) {
		inq = (struct scsi_inquiry_data *)ccb->csio.data_ptr;
		device = SID_TYPE(inq);
		qual = SID_QUAL(inq);

		/*
		 * We want DASD and PROC devices to only be
		 * visible through the pass device.
		 */
		if (((device == T_DIRECT) ||
		    (device == T_PROCESSOR) ||
		    (sc->flags & AAC_FLAGS_CAM_PASSONLY))) {
			/*
			 * Some aac(4) adapters will always report that a direct
			 * access device is offline in response to a INQUIRY
			 * command that does not retrieve vital product data.
			 * Force the qualifier to connected so that upper layers
			 * correctly recognize that a disk is present.
			 */
			if ((data[1] & SI_EVPD) == 0 && device == T_DIRECT &&
			    qual == SID_QUAL_LU_OFFLINE)
				qual = SID_QUAL_LU_CONNECTED;
			ccb->csio.data_ptr[0] = (qual << 5) | T_NODEVICE;
		}
	} else if (ccb->ccb_h.status == CAM_SEL_TIMEOUT &&
		ccb->ccb_h.target_lun != 0) {
		/* fix for INQUIRYs on Lun>0 */
		ccb->ccb_h.status = CAM_DEV_NOT_THERE;
	}
}