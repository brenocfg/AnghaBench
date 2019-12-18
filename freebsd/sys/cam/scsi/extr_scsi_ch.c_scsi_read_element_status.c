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
struct scsi_read_element_status {int /*<<< orphan*/  byte2; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  count; int /*<<< orphan*/  sea; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  READ_ELEMENT_STATUS ; 
 int /*<<< orphan*/  READ_ELEMENT_STATUS_CURDATA ; 
 int /*<<< orphan*/  READ_ELEMENT_STATUS_DVCID ; 
 int /*<<< orphan*/  READ_ELEMENT_STATUS_VOLTAG ; 
 int /*<<< orphan*/  bzero (struct scsi_read_element_status*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto3b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_read_element_status(struct ccb_scsiio *csio, u_int32_t retries,
			 void (*cbfcnp)(struct cam_periph *, union ccb *),
			 u_int8_t tag_action, int voltag, u_int32_t sea,
			 int curdata, int dvcid,
			 u_int32_t count, u_int8_t *data_ptr,
			 u_int32_t dxfer_len, u_int8_t sense_len,
			 u_int32_t timeout)
{
	struct scsi_read_element_status *scsi_cmd;

	scsi_cmd = (struct scsi_read_element_status *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));

	scsi_cmd->opcode = READ_ELEMENT_STATUS;

	scsi_ulto2b(sea, scsi_cmd->sea);
	scsi_ulto2b(count, scsi_cmd->count);
	scsi_ulto3b(dxfer_len, scsi_cmd->len);
	if (dvcid)
		scsi_cmd->flags |= READ_ELEMENT_STATUS_DVCID;
	if (curdata)
		scsi_cmd->flags |= READ_ELEMENT_STATUS_CURDATA;

	if (voltag)
		scsi_cmd->byte2 |= READ_ELEMENT_STATUS_VOLTAG;

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/ CAM_DIR_IN,
		      tag_action,
		      data_ptr,
		      dxfer_len,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}