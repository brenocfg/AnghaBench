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
struct scsi_tape_read_position {int byte1; int /*<<< orphan*/  opcode; } ;
struct scsi_tape_position_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  READ_POSITION ; 
 int /*<<< orphan*/  bzero (struct scsi_tape_read_position*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
scsi_read_position(struct ccb_scsiio *csio, u_int32_t retries,
		   void (*cbfcnp)(struct cam_periph *, union ccb *),
		   u_int8_t tag_action, int hardsoft,
		   struct scsi_tape_position_data *sbp,
		   u_int8_t sense_len, u_int32_t timeout)
{
	struct scsi_tape_read_position *scmd;

	cam_fill_csio(csio, retries, cbfcnp, CAM_DIR_IN, tag_action,
	    (u_int8_t *)sbp, sizeof (*sbp), sense_len, sizeof(*scmd), timeout);
	scmd = (struct scsi_tape_read_position *)&csio->cdb_io.cdb_bytes;
	bzero(scmd, sizeof(*scmd));
	scmd->opcode = READ_POSITION;
	scmd->byte1 = hardsoft;
}