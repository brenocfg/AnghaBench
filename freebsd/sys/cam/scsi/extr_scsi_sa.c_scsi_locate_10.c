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
struct scsi_tape_locate {int /*<<< orphan*/  partition; int /*<<< orphan*/  blkaddr; int /*<<< orphan*/  byte1; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  LOCATE ; 
 int /*<<< orphan*/  SA_SPOS_BT ; 
 int /*<<< orphan*/  SA_SPOS_CP ; 
 int /*<<< orphan*/  SA_SPOS_IMMED ; 
 int /*<<< orphan*/  bzero (struct scsi_tape_locate*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_locate_10(struct ccb_scsiio *csio, u_int32_t retries,
	       void (*cbfcnp)(struct cam_periph *, union ccb *),
	       u_int8_t tag_action, int immed, int cp, int hard,
	       int64_t partition, u_int32_t block_address,
	       int sense_len, u_int32_t timeout)
{
	struct scsi_tape_locate *scmd;

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      CAM_DIR_NONE,
		      tag_action,
		      /*data_ptr*/ NULL,
		      /*dxfer_len*/ 0,
		      sense_len,
		      sizeof(*scmd),
		      timeout);
	scmd = (struct scsi_tape_locate *)&csio->cdb_io.cdb_bytes;
	bzero(scmd, sizeof(*scmd));
	scmd->opcode = LOCATE;
	if (immed)
		scmd->byte1 |= SA_SPOS_IMMED;
	if (cp)
		scmd->byte1 |= SA_SPOS_CP;
	if (hard)
		scmd->byte1 |= SA_SPOS_BT;
	scsi_ulto4b(block_address, scmd->blkaddr);
	scmd->partition = partition;
}