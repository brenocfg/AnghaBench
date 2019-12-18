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
struct scsi_sa_rw {scalar_t__ control; int /*<<< orphan*/  length; int /*<<< orphan*/  sli_fixed; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int CAM_DATA_BIO ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_OUT ; 
 int /*<<< orphan*/  SARW_FIXED ; 
 int /*<<< orphan*/  SAR_SLI ; 
 int /*<<< orphan*/  SA_READ ; 
 int /*<<< orphan*/  SA_WRITE ; 
 int SCSI_RW_BIO ; 
 int SCSI_RW_DIRMASK ; 
 int SCSI_RW_READ ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto3b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_sa_read_write(struct ccb_scsiio *csio, u_int32_t retries,
		   void (*cbfcnp)(struct cam_periph *, union ccb *),
		   u_int8_t tag_action, int readop, int sli,
		   int fixed, u_int32_t length, u_int8_t *data_ptr,
		   u_int32_t dxfer_len, u_int8_t sense_len, u_int32_t timeout)
{
	struct scsi_sa_rw *scsi_cmd;
	int read;

	read = (readop & SCSI_RW_DIRMASK) == SCSI_RW_READ;

	scsi_cmd = (struct scsi_sa_rw *)&csio->cdb_io.cdb_bytes;
	scsi_cmd->opcode = read ? SA_READ : SA_WRITE;
	scsi_cmd->sli_fixed = 0;
	if (sli && read)
		scsi_cmd->sli_fixed |= SAR_SLI;
	if (fixed)
		scsi_cmd->sli_fixed |= SARW_FIXED;
	scsi_ulto3b(length, scsi_cmd->length);
	scsi_cmd->control = 0;

	cam_fill_csio(csio, retries, cbfcnp, (read ? CAM_DIR_IN : CAM_DIR_OUT) |
	    ((readop & SCSI_RW_BIO) != 0 ? CAM_DATA_BIO : 0),
	    tag_action, data_ptr, dxfer_len, sense_len,
	    sizeof(*scsi_cmd), timeout);
}