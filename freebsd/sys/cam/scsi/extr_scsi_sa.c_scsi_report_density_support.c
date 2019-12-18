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
struct scsi_report_density_support {int /*<<< orphan*/  length; int /*<<< orphan*/  byte1; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  REPORT_DENSITY_SUPPORT ; 
 int /*<<< orphan*/  SRDS_MEDIA ; 
 int /*<<< orphan*/  SRDS_MEDIUM_TYPE ; 
 int /*<<< orphan*/  bzero (struct scsi_report_density_support*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_report_density_support(struct ccb_scsiio *csio, u_int32_t retries,
			    void (*cbfcnp)(struct cam_periph *, union ccb *),
			    u_int8_t tag_action, int media, int medium_type,
			    u_int8_t *data_ptr, u_int32_t length,
			    u_int32_t sense_len, u_int32_t timeout)
{
	struct scsi_report_density_support *scsi_cmd;

	scsi_cmd =(struct scsi_report_density_support *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));

	scsi_cmd->opcode = REPORT_DENSITY_SUPPORT;
	if (media != 0)
		scsi_cmd->byte1 |= SRDS_MEDIA;
	if (medium_type != 0)
		scsi_cmd->byte1 |= SRDS_MEDIUM_TYPE;

	scsi_ulto2b(length, scsi_cmd->length);

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_IN,
		      tag_action,
		      /*data_ptr*/data_ptr,
		      /*dxfer_len*/length,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}