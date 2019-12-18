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
struct scsi_space {scalar_t__ control; int /*<<< orphan*/  count; int /*<<< orphan*/  code; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;
typedef  int /*<<< orphan*/  scsi_space_code ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  SPACE ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto3b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_space(struct ccb_scsiio *csio, u_int32_t retries,
	   void (*cbfcnp)(struct cam_periph *, union ccb *),
	   u_int8_t tag_action, scsi_space_code code,
	   u_int32_t count, u_int8_t sense_len, u_int32_t timeout)
{
	struct scsi_space *scsi_cmd;

	scsi_cmd = (struct scsi_space *)&csio->cdb_io.cdb_bytes;
	scsi_cmd->opcode = SPACE;
	scsi_cmd->code = code;
	scsi_ulto3b(count, scsi_cmd->count);
	scsi_cmd->control = 0;

	cam_fill_csio(csio, retries, cbfcnp, CAM_DIR_NONE, tag_action, NULL,
	    0, sense_len, sizeof(*scsi_cmd), timeout);
}