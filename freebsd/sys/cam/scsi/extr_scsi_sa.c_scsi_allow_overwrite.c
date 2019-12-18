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
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct scsi_allow_overwrite {int allow_overwrite; int partition; int /*<<< orphan*/  logical_id; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOW_OVERWRITE ; 
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  bzero (struct scsi_allow_overwrite*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_u64to8b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_allow_overwrite(struct ccb_scsiio *csio, u_int32_t retries,
		   void (*cbfcnp)(struct cam_periph *, union ccb *),
		   u_int8_t tag_action, int allow_overwrite, int partition, 
		   u_int64_t logical_id, u_int32_t sense_len, u_int32_t timeout)
{
	struct scsi_allow_overwrite *scsi_cmd;

	scsi_cmd = (struct scsi_allow_overwrite *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));

	scsi_cmd->opcode = ALLOW_OVERWRITE;

	scsi_cmd->allow_overwrite = allow_overwrite;
	scsi_cmd->partition = partition;
	scsi_u64to8b(logical_id, scsi_cmd->logical_id);

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      CAM_DIR_NONE,
		      tag_action,
		      /*data_ptr*/ NULL,
		      /*dxfer_len*/ 0,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}