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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_int32_t ;
struct scsi_write_buffer {int byte2; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  buffer_id; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  WRITE_BUFFER ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,scalar_t__,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct scsi_write_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_ulto3b (scalar_t__,int /*<<< orphan*/ ) ; 

void
scsi_write_buffer(struct ccb_scsiio *csio, u_int32_t retries,
			void (*cbfcnp)(struct cam_periph *, union ccb *),
			uint8_t tag_action, int mode,
			uint8_t buffer_id, u_int32_t offset,
			uint8_t *data_ptr, uint32_t param_list_length,
			uint8_t sense_len, uint32_t timeout)
{
	struct scsi_write_buffer *scsi_cmd;

	scsi_cmd = (struct scsi_write_buffer *)&csio->cdb_io.cdb_bytes;
	memset(scsi_cmd, 0, sizeof(*scsi_cmd));
	scsi_cmd->opcode = WRITE_BUFFER;
	scsi_cmd->byte2 = mode;
	scsi_cmd->buffer_id = buffer_id;
	scsi_ulto3b(offset, scsi_cmd->offset);
	scsi_ulto3b(param_list_length, scsi_cmd->length);

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/param_list_length ? CAM_DIR_OUT : CAM_DIR_NONE,
		      tag_action,
		      data_ptr,
		      param_list_length,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}