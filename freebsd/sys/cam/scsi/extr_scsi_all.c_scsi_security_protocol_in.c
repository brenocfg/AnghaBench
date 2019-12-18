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
struct scsi_security_protocol_in {int byte4; int /*<<< orphan*/  length; int /*<<< orphan*/  security_protocol_specific; int /*<<< orphan*/  security_protocol; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  SECURITY_PROTOCOL_IN ; 
 int /*<<< orphan*/  bzero (struct scsi_security_protocol_in*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_security_protocol_in(struct ccb_scsiio *csio, uint32_t retries, 
			  void (*cbfcnp)(struct cam_periph *, union ccb *),
			  uint8_t tag_action, uint32_t security_protocol,
			  uint32_t security_protocol_specific, int byte4,
			  uint8_t *data_ptr, uint32_t dxfer_len, int sense_len,
			  int timeout)
{
	struct scsi_security_protocol_in *scsi_cmd;

	scsi_cmd = (struct scsi_security_protocol_in *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));

	scsi_cmd->opcode = SECURITY_PROTOCOL_IN;

	scsi_cmd->security_protocol = security_protocol;
	scsi_ulto2b(security_protocol_specific,
		    scsi_cmd->security_protocol_specific); 
	scsi_cmd->byte4 = byte4;
	scsi_ulto4b(dxfer_len, scsi_cmd->length);

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_IN,
		      tag_action,
		      data_ptr,
		      dxfer_len,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}