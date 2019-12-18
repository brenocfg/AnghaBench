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
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct scsi_target_group {int service_action; int /*<<< orphan*/  length; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  MAINTENANCE_IN ; 
 int REPORT_TARGET_PORT_GROUPS ; 
 int /*<<< orphan*/  bzero (struct scsi_target_group*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_report_target_group(struct ccb_scsiio *csio, u_int32_t retries,
		 void (*cbfcnp)(struct cam_periph *, union ccb *),
		 u_int8_t tag_action, u_int8_t pdf,
		 void *buf, u_int32_t alloc_len,
		 u_int8_t sense_len, u_int32_t timeout)
{
	struct scsi_target_group *scsi_cmd;

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_IN,
		      tag_action,
		      /*data_ptr*/(u_int8_t *)buf,
		      /*dxfer_len*/alloc_len,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
	scsi_cmd = (struct scsi_target_group *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));
	scsi_cmd->opcode = MAINTENANCE_IN;
	scsi_cmd->service_action = REPORT_TARGET_PORT_GROUPS | pdf;
	scsi_ulto4b(alloc_len, scsi_cmd->length);
}