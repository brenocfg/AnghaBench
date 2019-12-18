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
struct scsi_tape_locate {int /*<<< orphan*/  blkaddr; int /*<<< orphan*/  byte1; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  LOCATE ; 
 int /*<<< orphan*/  SA_SPOS_BT ; 
 int /*<<< orphan*/  bzero (struct scsi_tape_locate*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_set_position(struct ccb_scsiio *csio, u_int32_t retries,
		   void (*cbfcnp)(struct cam_periph *, union ccb *),
		   u_int8_t tag_action, int hardsoft, u_int32_t blkno,
		   u_int8_t sense_len, u_int32_t timeout)
{
	struct scsi_tape_locate *scmd;

	cam_fill_csio(csio, retries, cbfcnp, CAM_DIR_NONE, tag_action,
	    (u_int8_t *)NULL, 0, sense_len, sizeof(*scmd), timeout);
	scmd = (struct scsi_tape_locate *)&csio->cdb_io.cdb_bytes;
	bzero(scmd, sizeof(*scmd));
	scmd->opcode = LOCATE;
	if (hardsoft)
		scmd->byte1 |= SA_SPOS_BT;
	scsi_ulto4b(blkno, scmd->blkaddr);
}