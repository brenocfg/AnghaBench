#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uintmax_t ;
struct sbp_ocb {TYPE_7__* ccb; TYPE_4__* sdev; } ;
struct TYPE_12__ {int* cdb_bytes; } ;
struct ccb_scsiio {int cdb_len; int dxfer_len; TYPE_5__ cdb_io; int /*<<< orphan*/  sense_len; } ;
struct TYPE_13__ {int target_id; int flags; scalar_t__ target_lun; } ;
struct TYPE_14__ {TYPE_6__ ccb_h; struct ccb_scsiio csio; } ;
struct TYPE_11__ {TYPE_3__* target; } ;
struct TYPE_10__ {TYPE_2__* sbp; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {TYPE_1__ fd; } ;

/* Variables and functions */
 int CAM_DIR_MASK ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sbp_print_scsi_cmd(struct sbp_ocb *ocb)
{
	struct ccb_scsiio *csio;

	csio = &ocb->ccb->csio;
	printf("%s:%d:%jx XPT_SCSI_IO: "
		"cmd: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x"
		", flags: 0x%02x, "
		"%db cmd/%db data/%db sense\n",
		device_get_nameunit(ocb->sdev->target->sbp->fd.dev),
		ocb->ccb->ccb_h.target_id,
		(uintmax_t)ocb->ccb->ccb_h.target_lun,
		csio->cdb_io.cdb_bytes[0],
		csio->cdb_io.cdb_bytes[1],
		csio->cdb_io.cdb_bytes[2],
		csio->cdb_io.cdb_bytes[3],
		csio->cdb_io.cdb_bytes[4],
		csio->cdb_io.cdb_bytes[5],
		csio->cdb_io.cdb_bytes[6],
		csio->cdb_io.cdb_bytes[7],
		csio->cdb_io.cdb_bytes[8],
		csio->cdb_io.cdb_bytes[9],
		ocb->ccb->ccb_h.flags & CAM_DIR_MASK,
		csio->cdb_len, csio->dxfer_len,
		csio->sense_len);
}