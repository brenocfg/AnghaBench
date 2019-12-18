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
struct scsi_write_filemarks {int /*<<< orphan*/  num_marks; int /*<<< orphan*/  byte2; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  SWFMRK_IMMED ; 
 int /*<<< orphan*/  SWFMRK_WSMK ; 
 int /*<<< orphan*/  WRITE_FILEMARKS ; 
 int /*<<< orphan*/  bzero (struct scsi_write_filemarks*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto3b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_write_filemarks(struct ccb_scsiio *csio, u_int32_t retries,
		     void (*cbfcnp)(struct cam_periph *, union ccb *),
		     u_int8_t tag_action, int immediate, int setmark,
		     u_int32_t num_marks, u_int8_t sense_len,
		     u_int32_t timeout)
{
	struct scsi_write_filemarks *scsi_cmd;

	scsi_cmd = (struct scsi_write_filemarks *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));
	scsi_cmd->opcode = WRITE_FILEMARKS;
	if (immediate)
		scsi_cmd->byte2 |= SWFMRK_IMMED;
	if (setmark)
		scsi_cmd->byte2 |= SWFMRK_WSMK;
	
	scsi_ulto3b(num_marks, scsi_cmd->num_marks);

	cam_fill_csio(csio, retries, cbfcnp, CAM_DIR_NONE, tag_action, NULL,
	    0, sense_len, sizeof(*scsi_cmd), timeout);
}