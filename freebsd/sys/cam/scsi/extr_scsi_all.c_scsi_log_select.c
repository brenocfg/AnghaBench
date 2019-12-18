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
struct scsi_log_select {int page; int /*<<< orphan*/  length; int /*<<< orphan*/  byte2; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  LOG_SELECT ; 
 int SLS_PAGE_CODE ; 
 int /*<<< orphan*/  SLS_PCR ; 
 int /*<<< orphan*/  SLS_SP ; 
 int /*<<< orphan*/  bzero (struct scsi_log_select*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_log_select(struct ccb_scsiio *csio, u_int32_t retries,
		void (*cbfcnp)(struct cam_periph *, union ccb *),
		u_int8_t tag_action, u_int8_t page_code, int save_pages,
		int pc_reset, u_int8_t *param_buf, u_int32_t param_len,
		u_int8_t sense_len, u_int32_t timeout)
{
	struct scsi_log_select *scsi_cmd;
	u_int8_t cdb_len;

	scsi_cmd = (struct scsi_log_select *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));
	scsi_cmd->opcode = LOG_SELECT;
	scsi_cmd->page = page_code & SLS_PAGE_CODE;
	if (save_pages != 0)
		scsi_cmd->byte2 |= SLS_SP;
	if (pc_reset != 0)
		scsi_cmd->byte2 |= SLS_PCR;
	scsi_ulto2b(param_len, scsi_cmd->length);
	cdb_len = sizeof(*scsi_cmd);

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_OUT,
		      tag_action,
		      /*data_ptr*/param_buf,
		      /*dxfer_len*/param_len,
		      sense_len,
		      cdb_len,
		      timeout);
}