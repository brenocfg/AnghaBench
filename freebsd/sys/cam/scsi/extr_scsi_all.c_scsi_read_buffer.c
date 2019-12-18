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
typedef  int /*<<< orphan*/  u_int32_t ;
struct scsi_read_buffer {int byte2; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  buffer_id; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  READ_BUFFER ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct scsi_read_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_ulto3b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_read_buffer(struct ccb_scsiio *csio, u_int32_t retries,
			void (*cbfcnp)(struct cam_periph *, union ccb*),
			uint8_t tag_action, int mode,
			uint8_t buffer_id, u_int32_t offset,
			uint8_t *data_ptr, uint32_t allocation_length,
			uint8_t sense_len, uint32_t timeout)
{
	struct scsi_read_buffer *scsi_cmd;

	scsi_cmd = (struct scsi_read_buffer *)&csio->cdb_io.cdb_bytes;
	memset(scsi_cmd, 0, sizeof(*scsi_cmd));
	scsi_cmd->opcode = READ_BUFFER;
	scsi_cmd->byte2 = mode;
	scsi_cmd->buffer_id = buffer_id;
	scsi_ulto3b(offset, scsi_cmd->offset);
	scsi_ulto3b(allocation_length, scsi_cmd->length);

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_IN,
		      tag_action,
		      data_ptr,
		      allocation_length,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}