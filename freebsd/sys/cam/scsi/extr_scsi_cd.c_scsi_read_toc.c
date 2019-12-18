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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_read_toc {int /*<<< orphan*/  data_len; void* from_track; void* format; void* byte2; int /*<<< orphan*/  op_code; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  READ_TOC ; 
 int /*<<< orphan*/  bzero (struct scsi_read_toc*,int) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,void*,void**,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
scsi_read_toc(struct ccb_scsiio *csio, uint32_t retries,
	      void (*cbfcnp)(struct cam_periph *, union ccb *),
	      uint8_t tag_action, uint8_t byte1_flags, uint8_t format,
	      uint8_t track, uint8_t *data_ptr, uint32_t dxfer_len,
	      int sense_len, int timeout)
{
	struct scsi_read_toc *scsi_cmd;

	scsi_cmd = (struct scsi_read_toc *)&csio->cdb_io.cdb_bytes;
	bzero(scsi_cmd, sizeof(*scsi_cmd));
	scsi_cmd->op_code = READ_TOC;

	/*
	 * The structure is counting from 1, the function counting from 0.
	 * The spec counts from 0.  In MMC-6, there is only one flag, the
	 * MSF flag.  But we put the whole byte in for a bit a future-proofing.
	 */
	scsi_cmd->byte2 = byte1_flags;
	scsi_cmd->format = format;
	scsi_cmd->from_track = track;
	scsi_ulto2b(dxfer_len, scsi_cmd->data_len);

	cam_fill_csio(csio,
		      /* retries */ retries,
		      /* cbfcnp */ cbfcnp,
		      /* flags */ CAM_DIR_IN,
		      /* tag_action */ tag_action,
		      /* data_ptr */ data_ptr,
		      /* dxfer_len */ dxfer_len,
		      /* sense_len */ sense_len,
		      sizeof(*scsi_cmd),
		      /* timeout */ timeout);
}