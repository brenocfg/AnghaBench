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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_per_res_out {int action; int scope_type; int /*<<< orphan*/  length; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  PERSISTENT_RES_OUT ; 
 int /*<<< orphan*/  bzero (struct scsi_per_res_out*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  scsi_ulto4b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_persistent_reserve_out(struct ccb_scsiio *csio, uint32_t retries, 
			    void (*cbfcnp)(struct cam_periph *, union ccb *),
			    uint8_t tag_action, int service_action,
			    int scope, int res_type, uint8_t *data_ptr,
			    uint32_t dxfer_len, int sense_len, int timeout)
{
	struct scsi_per_res_out *scsi_cmd;

	scsi_cmd = (struct scsi_per_res_out *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));

	scsi_cmd->opcode = PERSISTENT_RES_OUT;
	scsi_cmd->action = service_action;
	scsi_cmd->scope_type = scope | res_type;
	scsi_ulto4b(dxfer_len, scsi_cmd->length);

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_OUT,
		      tag_action,
		      /*data_ptr*/data_ptr,
		      /*dxfer_len*/dxfer_len,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}