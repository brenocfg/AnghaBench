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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct scsi_zbc_in {void* zone_options; int /*<<< orphan*/  zone_start_lba; int /*<<< orphan*/  length; void* service_action; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  ZBC_IN ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,scalar_t__,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,void*,void**,scalar_t__,void*,int,scalar_t__) ; 
 int /*<<< orphan*/  scsi_u64to8b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (scalar_t__,int /*<<< orphan*/ ) ; 

void
scsi_zbc_in(struct ccb_scsiio *csio, uint32_t retries,
	    void (*cbfcnp)(struct cam_periph *, union ccb *),
	    uint8_t tag_action, uint8_t service_action, uint64_t zone_start_lba,
	    uint8_t zone_options, uint8_t *data_ptr, uint32_t dxfer_len,
	    uint8_t sense_len, uint32_t timeout)
{
	struct scsi_zbc_in *scsi_cmd;

	scsi_cmd = (struct scsi_zbc_in *)&csio->cdb_io.cdb_bytes;
	scsi_cmd->opcode = ZBC_IN;
	scsi_cmd->service_action = service_action;
	scsi_ulto4b(dxfer_len, scsi_cmd->length);
	scsi_u64to8b(zone_start_lba, scsi_cmd->zone_start_lba);
	scsi_cmd->zone_options = zone_options;

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/ (dxfer_len > 0) ? CAM_DIR_IN : CAM_DIR_NONE,
		      tag_action,
		      data_ptr,
		      dxfer_len,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);

}