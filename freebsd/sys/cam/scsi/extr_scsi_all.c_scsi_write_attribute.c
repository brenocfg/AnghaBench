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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct scsi_write_attribute {int logical_volume; int partition; int /*<<< orphan*/  length; int /*<<< orphan*/  element; int /*<<< orphan*/  byte2; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  SWA_WTC ; 
 int /*<<< orphan*/  WRITE_ATTRIBUTE ; 
 int /*<<< orphan*/  bzero (struct scsi_write_attribute*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto3b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_write_attribute(struct ccb_scsiio *csio, u_int32_t retries, 
		    void (*cbfcnp)(struct cam_periph *, union ccb *),
		    u_int8_t tag_action, uint32_t element, int logical_volume,
		    int partition, int wtc, u_int8_t *data_ptr,
		    u_int32_t length, int sense_len, u_int32_t timeout)
{
	struct scsi_write_attribute *scsi_cmd;

	scsi_cmd = (struct scsi_write_attribute *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));

	scsi_cmd->opcode = WRITE_ATTRIBUTE;
	if (wtc != 0)
		scsi_cmd->byte2 = SWA_WTC;
	scsi_ulto3b(element, scsi_cmd->element);
	scsi_cmd->logical_volume = logical_volume;
	scsi_cmd->partition = partition;
	scsi_ulto4b(length, scsi_cmd->length);

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_OUT,
		      tag_action,
		      /*data_ptr*/data_ptr,
		      /*dxfer_len*/length,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}