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
typedef  int u_int16_t ;
struct scsi_send_volume_tag_parameters {int dummy; } ;
struct scsi_send_volume_tag {int /*<<< orphan*/  pll; int /*<<< orphan*/  sac; int /*<<< orphan*/  ea; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  SEND_VOLUME_TAG ; 
 int /*<<< orphan*/  bzero (struct scsi_send_volume_tag*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 

void
scsi_send_volume_tag(struct ccb_scsiio *csio, u_int32_t retries,
		     void (*cbfcnp)(struct cam_periph *, union ccb *),
		     u_int8_t tag_action, 
		     u_int16_t element_address,
		     u_int8_t send_action_code,
		     struct scsi_send_volume_tag_parameters *parameters,
		     u_int8_t sense_len, u_int32_t timeout)
{
	struct scsi_send_volume_tag *scsi_cmd;

	scsi_cmd = (struct scsi_send_volume_tag *) &csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));

	scsi_cmd->opcode = SEND_VOLUME_TAG;
	scsi_ulto2b(element_address, scsi_cmd->ea);
	scsi_cmd->sac = send_action_code;
	scsi_ulto2b(sizeof(*parameters), scsi_cmd->pll);

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/ CAM_DIR_OUT,
		      tag_action,
		      /* data_ptr */ (u_int8_t *) parameters,
		      sizeof(*parameters),
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}