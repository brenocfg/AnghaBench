#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int8_t ;
typedef  int u_int64_t ;
typedef  int u_int32_t ;
struct scsi_write_same_16 {int /*<<< orphan*/ * length; int /*<<< orphan*/ * addr; scalar_t__ control; scalar_t__ group; void* byte2; int /*<<< orphan*/  opcode; } ;
struct scsi_write_same_10 {int /*<<< orphan*/ * length; int /*<<< orphan*/ * addr; scalar_t__ control; scalar_t__ group; void* byte2; int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
struct TYPE_3__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_2__ ccb_h; TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_SUBTRACE ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  WRITE_SAME_10 ; 
 int /*<<< orphan*/  WRITE_SAME_16 ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,void*,void**,int,void*,void*,int) ; 
 int /*<<< orphan*/  scsi_u64to8b (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int /*<<< orphan*/ *) ; 

void
scsi_write_same(struct ccb_scsiio *csio, u_int32_t retries,
		void (*cbfcnp)(struct cam_periph *, union ccb *),
		u_int8_t tag_action, u_int8_t byte2,
		int minimum_cmd_size, u_int64_t lba, u_int32_t block_count,
		u_int8_t *data_ptr, u_int32_t dxfer_len, u_int8_t sense_len,
		u_int32_t timeout)
{
	u_int8_t cdb_len;
	if ((minimum_cmd_size < 16) &&
	    ((block_count & 0xffff) == block_count) &&
	    ((lba & 0xffffffff) == lba)) {
		/*
		 * Need a 10 byte cdb.
		 */
		struct scsi_write_same_10 *scsi_cmd;

		scsi_cmd = (struct scsi_write_same_10 *)&csio->cdb_io.cdb_bytes;
		scsi_cmd->opcode = WRITE_SAME_10;
		scsi_cmd->byte2 = byte2;
		scsi_ulto4b(lba, scsi_cmd->addr);
		scsi_cmd->group = 0;
		scsi_ulto2b(block_count, scsi_cmd->length);
		scsi_cmd->control = 0;
		cdb_len = sizeof(*scsi_cmd);

		CAM_DEBUG(csio->ccb_h.path, CAM_DEBUG_SUBTRACE,
			  ("10byte: %x%x%x%x:%x%x: %d\n", scsi_cmd->addr[0],
			   scsi_cmd->addr[1], scsi_cmd->addr[2],
			   scsi_cmd->addr[3], scsi_cmd->length[0],
			   scsi_cmd->length[1], dxfer_len));
	} else {
		/*
		 * 16 byte CDB.  We'll only get here if the LBA is larger
		 * than 2^32, or if the user asks for a 16 byte command.
		 */
		struct scsi_write_same_16 *scsi_cmd;

		scsi_cmd = (struct scsi_write_same_16 *)&csio->cdb_io.cdb_bytes;
		scsi_cmd->opcode = WRITE_SAME_16;
		scsi_cmd->byte2 = byte2;
		scsi_u64to8b(lba, scsi_cmd->addr);
		scsi_ulto4b(block_count, scsi_cmd->length);
		scsi_cmd->group = 0;
		scsi_cmd->control = 0;
		cdb_len = sizeof(*scsi_cmd);

		CAM_DEBUG(csio->ccb_h.path, CAM_DEBUG_SUBTRACE,
			  ("16byte: %x%x%x%x%x%x%x%x:%x%x%x%x: %d\n",
			   scsi_cmd->addr[0], scsi_cmd->addr[1],
			   scsi_cmd->addr[2], scsi_cmd->addr[3],
			   scsi_cmd->addr[4], scsi_cmd->addr[5],
			   scsi_cmd->addr[6], scsi_cmd->addr[7],
			   scsi_cmd->length[0], scsi_cmd->length[1],
			   scsi_cmd->length[2], scsi_cmd->length[3],
			   dxfer_len));
	}
	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_OUT,
		      tag_action,
		      data_ptr,
		      dxfer_len,
		      sense_len,
		      cdb_len,
		      timeout);
}