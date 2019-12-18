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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct scsi_inquiry {int /*<<< orphan*/  length; int /*<<< orphan*/  page_code; int /*<<< orphan*/  byte2; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  INQUIRY ; 
 int /*<<< orphan*/  SI_EVPD ; 
 int /*<<< orphan*/  bzero (struct scsi_inquiry*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_inquiry(struct ccb_scsiio *csio, u_int32_t retries,
	     void (*cbfcnp)(struct cam_periph *, union ccb *),
	     u_int8_t tag_action, u_int8_t *inq_buf, u_int32_t inq_len,
	     int evpd, u_int8_t page_code, u_int8_t sense_len,
	     u_int32_t timeout)
{
	struct scsi_inquiry *scsi_cmd;

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_IN,
		      tag_action,
		      /*data_ptr*/inq_buf,
		      /*dxfer_len*/inq_len,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);

	scsi_cmd = (struct scsi_inquiry *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));
	scsi_cmd->opcode = INQUIRY;
	if (evpd) {
		scsi_cmd->byte2 |= SI_EVPD;
		scsi_cmd->page_code = page_code;		
	}
	scsi_ulto2b(inq_len, scsi_cmd->length);
}