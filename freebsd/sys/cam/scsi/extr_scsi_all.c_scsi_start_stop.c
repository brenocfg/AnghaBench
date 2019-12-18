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
struct scsi_start_stop_unit {int /*<<< orphan*/  byte2; int /*<<< orphan*/  how; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int CAM_DIR_NONE ; 
 int CAM_HIGH_POWER ; 
 int /*<<< orphan*/  SSS_IMMED ; 
 int /*<<< orphan*/  SSS_LOEJ ; 
 int /*<<< orphan*/  SSS_START ; 
 int /*<<< orphan*/  START_STOP_UNIT ; 
 int /*<<< orphan*/  bzero (struct scsi_start_stop_unit*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void 
scsi_start_stop(struct ccb_scsiio *csio, u_int32_t retries,
		void (*cbfcnp)(struct cam_periph *, union ccb *),
		u_int8_t tag_action, int start, int load_eject,
		int immediate, u_int8_t sense_len, u_int32_t timeout)
{
	struct scsi_start_stop_unit *scsi_cmd;
	int extra_flags = 0;

	scsi_cmd = (struct scsi_start_stop_unit *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));
	scsi_cmd->opcode = START_STOP_UNIT;
	if (start != 0) {
		scsi_cmd->how |= SSS_START;
		/* it takes a lot of power to start a drive */
		extra_flags |= CAM_HIGH_POWER;
	}
	if (load_eject != 0)
		scsi_cmd->how |= SSS_LOEJ;
	if (immediate != 0)
		scsi_cmd->byte2 |= SSS_IMMED;

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_NONE | extra_flags,
		      tag_action,
		      /*data_ptr*/NULL,
		      /*dxfer_len*/0,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}