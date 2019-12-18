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
struct scsi_position_to_element {int /*<<< orphan*/  invert; int /*<<< orphan*/  dst; int /*<<< orphan*/  tea; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  POSITION_TO_ELEMENT ; 
 int /*<<< orphan*/  POSITION_TO_ELEMENT_INVERT ; 
 int /*<<< orphan*/  bzero (struct scsi_position_to_element*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_position_to_element(struct ccb_scsiio *csio, u_int32_t retries,
			 void (*cbfcnp)(struct cam_periph *, union ccb *),
			 u_int8_t tag_action, u_int32_t tea, u_int32_t dst,
			 int invert, u_int8_t sense_len, u_int32_t timeout)
{
	struct scsi_position_to_element *scsi_cmd;

	scsi_cmd = (struct scsi_position_to_element *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));

	scsi_cmd->opcode = POSITION_TO_ELEMENT;

	scsi_ulto2b(tea, scsi_cmd->tea);
	scsi_ulto2b(dst, scsi_cmd->dst);

	if (invert)
		scsi_cmd->invert |= POSITION_TO_ELEMENT_INVERT;

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/ CAM_DIR_NONE,
		      tag_action,
		      /*data_ptr*/ NULL,
		      /*dxfer_len*/ 0,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}