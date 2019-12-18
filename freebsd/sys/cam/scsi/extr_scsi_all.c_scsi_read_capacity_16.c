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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct scsi_read_capacity_16 {int /*<<< orphan*/  alloc_len; int /*<<< orphan*/  addr; int /*<<< orphan*/  service_action; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  SERVICE_ACTION_IN ; 
 int SRC16_PMI ; 
 int SRC16_RELADR ; 
 int /*<<< orphan*/  SRC16_SERVICE_ACTION ; 
 int /*<<< orphan*/  bzero (struct scsi_read_capacity_16*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_u64to8b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int /*<<< orphan*/ ) ; 

void
scsi_read_capacity_16(struct ccb_scsiio *csio, uint32_t retries,
		      void (*cbfcnp)(struct cam_periph *, union ccb *),
		      uint8_t tag_action, uint64_t lba, int reladr, int pmi,
		      uint8_t *rcap_buf, int rcap_buf_len, uint8_t sense_len,
		      uint32_t timeout)
{
	struct scsi_read_capacity_16 *scsi_cmd;

	
	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_IN,
		      tag_action,
		      /*data_ptr*/(u_int8_t *)rcap_buf,
		      /*dxfer_len*/rcap_buf_len,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
	scsi_cmd = (struct scsi_read_capacity_16 *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));
	scsi_cmd->opcode = SERVICE_ACTION_IN;
	scsi_cmd->service_action = SRC16_SERVICE_ACTION;
	scsi_u64to8b(lba, scsi_cmd->addr);
	scsi_ulto4b(rcap_buf_len, scsi_cmd->alloc_len);
	if (pmi)
		reladr |= SRC16_PMI;
	if (reladr)
		reladr |= SRC16_RELADR;
}