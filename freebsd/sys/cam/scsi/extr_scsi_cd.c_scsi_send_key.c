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
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct scsi_send_key {int agid_keyformat; int /*<<< orphan*/  param_len; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int RK_KF_AGID_SHIFT ; 
 int RK_KF_KEYFORMAT_MASK ; 
 int /*<<< orphan*/  SEND_KEY ; 
 int /*<<< orphan*/  bzero (struct scsi_send_key*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_send_key(struct ccb_scsiio *csio, u_int32_t retries,
	      void (*cbfcnp)(struct cam_periph *, union ccb *),
	      u_int8_t tag_action, u_int8_t agid, u_int8_t key_format,
	      u_int8_t *data_ptr, u_int32_t dxfer_len, u_int8_t sense_len,
	      u_int32_t timeout)
{
	struct scsi_send_key *scsi_cmd;

	scsi_cmd = (struct scsi_send_key *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));
	scsi_cmd->opcode = SEND_KEY;

	scsi_ulto2b(dxfer_len, scsi_cmd->param_len);
	scsi_cmd->agid_keyformat = (agid << RK_KF_AGID_SHIFT) |
		(key_format & RK_KF_KEYFORMAT_MASK);

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/ CAM_DIR_OUT,
		      tag_action,
		      /*data_ptr*/ data_ptr,
		      /*dxfer_len*/ dxfer_len,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}