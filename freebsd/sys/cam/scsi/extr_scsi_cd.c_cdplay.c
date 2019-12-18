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
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;
union ccb {struct ccb_scsiio csio; } ;
typedef  int u_int8_t ;
typedef  int u_int32_t ;
struct scsi_play_12 {scalar_t__ xfer_len; scalar_t__ blk_addr; int /*<<< orphan*/  op_code; } ;
struct scsi_play_10 {scalar_t__ xfer_len; scalar_t__ blk_addr; int /*<<< orphan*/  op_code; } ;
struct cam_periph {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  PLAY_10 ; 
 int /*<<< orphan*/  PLAY_12 ; 
 int /*<<< orphan*/  SF_RETRY_UA ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  bzero (struct scsi_play_12*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 union ccb* cam_periph_getccb (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd_retry_count ; 
 int /*<<< orphan*/  cderror ; 
 int cdrunccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int*) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int*) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static int
cdplay(struct cam_periph *periph, u_int32_t blk, u_int32_t len)
{
	struct ccb_scsiio *csio;
	union ccb *ccb;
	int error;
	u_int8_t cdb_len;

	error = 0;
	ccb = cam_periph_getccb(periph, CAM_PRIORITY_NORMAL);
	csio = &ccb->csio;
	/*
	 * Use the smallest possible command to perform the operation.
	 */
	if ((len & 0xffff0000) == 0) {
		/*
		 * We can fit in a 10 byte cdb.
		 */
		struct scsi_play_10 *scsi_cmd;

		scsi_cmd = (struct scsi_play_10 *)&csio->cdb_io.cdb_bytes;
		bzero (scsi_cmd, sizeof(*scsi_cmd));
		scsi_cmd->op_code = PLAY_10;
		scsi_ulto4b(blk, (u_int8_t *)scsi_cmd->blk_addr);
		scsi_ulto2b(len, (u_int8_t *)scsi_cmd->xfer_len);
		cdb_len = sizeof(*scsi_cmd);
	} else  {
		struct scsi_play_12 *scsi_cmd;

		scsi_cmd = (struct scsi_play_12 *)&csio->cdb_io.cdb_bytes;
		bzero (scsi_cmd, sizeof(*scsi_cmd));
		scsi_cmd->op_code = PLAY_12;
		scsi_ulto4b(blk, (u_int8_t *)scsi_cmd->blk_addr);
		scsi_ulto4b(len, (u_int8_t *)scsi_cmd->xfer_len);
		cdb_len = sizeof(*scsi_cmd);
	}
	cam_fill_csio(csio,
		      /*retries*/ cd_retry_count,
		      /*cbfcnp*/NULL,
		      /*flags*/CAM_DIR_NONE,
		      MSG_SIMPLE_Q_TAG,
		      /*dataptr*/NULL,
		      /*datalen*/0,
		      /*sense_len*/SSD_FULL_SIZE,
		      cdb_len,
		      /*timeout*/50 * 1000);

	error = cdrunccb(ccb, cderror, /*cam_flags*/CAM_RETRY_SELTO,
			 /*sense_flags*/SF_RETRY_UA);

	xpt_release_ccb(ccb);

	return(error);
}