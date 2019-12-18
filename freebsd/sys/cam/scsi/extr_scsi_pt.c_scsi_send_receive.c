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
typedef  int /*<<< orphan*/  u_int ;
struct scsi_send_receive {scalar_t__ control; int /*<<< orphan*/  xfer_len; int /*<<< orphan*/  byte2; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  RECEIVE ; 
 int /*<<< orphan*/  SEND ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto3b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_send_receive(struct ccb_scsiio *csio, u_int32_t retries,
		  void (*cbfcnp)(struct cam_periph *, union ccb *),
		  u_int tag_action, int readop, u_int byte2,
		  u_int32_t xfer_len, u_int8_t *data_ptr, u_int8_t sense_len,
		  u_int32_t timeout)
{
	struct scsi_send_receive *scsi_cmd;

	scsi_cmd = (struct scsi_send_receive *)&csio->cdb_io.cdb_bytes;
	scsi_cmd->opcode = readop ? RECEIVE : SEND;
	scsi_cmd->byte2 = byte2;
	scsi_ulto3b(xfer_len, scsi_cmd->xfer_len);
	scsi_cmd->control = 0;

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/readop ? CAM_DIR_IN : CAM_DIR_OUT,
		      tag_action,
		      data_ptr,
		      xfer_len,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}