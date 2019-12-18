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
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct scsi_locate_16 {int byte1; int byte2; int /*<<< orphan*/  logical_id; int /*<<< orphan*/  partition; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  LOCATE_16 ; 
 int SA_LC_CP ; 
 int SA_LC_DEST_TYPE_SHIFT ; 
 int SA_LC_IMMEDIATE ; 
 int /*<<< orphan*/  bzero (struct scsi_locate_16*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_u64to8b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_locate_16(struct ccb_scsiio *csio, u_int32_t retries,
	       void (*cbfcnp)(struct cam_periph *, union ccb *),
	       u_int8_t tag_action, int immed, int cp, u_int8_t dest_type,
	       int bam, int64_t partition, u_int64_t logical_id,
	       int sense_len, u_int32_t timeout)
{

	struct scsi_locate_16 *scsi_cmd;

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/CAM_DIR_NONE,
		      tag_action,
		      /*data_ptr*/NULL,
		      /*dxfer_len*/0,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);

	scsi_cmd = (struct scsi_locate_16 *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));
	scsi_cmd->opcode = LOCATE_16;
	if (immed)
		scsi_cmd->byte1 |= SA_LC_IMMEDIATE;
	if (cp)
		scsi_cmd->byte1 |= SA_LC_CP;
	scsi_cmd->byte1 |= (dest_type << SA_LC_DEST_TYPE_SHIFT);

	scsi_cmd->byte2 |= bam;
	scsi_cmd->partition = partition;
	scsi_u64to8b(logical_id, scsi_cmd->logical_id);
}