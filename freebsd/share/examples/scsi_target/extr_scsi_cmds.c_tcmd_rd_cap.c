#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct scsi_read_capacity_data {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int flags; } ;
struct ccb_scsiio {int dxfer_len; int /*<<< orphan*/  scsi_status; TYPE_2__ ccb_h; scalar_t__ data_ptr; } ;
struct TYPE_3__ {scalar_t__ targ_descr; } ;
struct ccb_accept_tio {int /*<<< orphan*/  init_id; TYPE_1__ ccb_h; } ;
struct atio_descr {int /*<<< orphan*/  cdb; } ;

/* Variables and functions */
 int CAM_DIR_IN ; 
 int CAM_SEND_STATUS ; 
 int /*<<< orphan*/  SCSI_STATUS_OK ; 
 int /*<<< orphan*/  bzero (struct scsi_read_capacity_data*,int) ; 
 int /*<<< orphan*/  cdb_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int /*<<< orphan*/ ) ; 
 int sector_size ; 
 int volume_size ; 

__attribute__((used)) static int
tcmd_rd_cap(struct ccb_accept_tio *atio, struct ccb_scsiio *ctio)
{
	struct scsi_read_capacity_data *srp;
	struct atio_descr *a_descr;
	uint32_t vsize;

	a_descr = (struct atio_descr *)atio->ccb_h.targ_descr;
	srp = (struct scsi_read_capacity_data *)ctio->data_ptr;

	if (volume_size > 0xffffffff)
		vsize = 0xffffffff;
	else
		vsize = (uint32_t)(volume_size - 1);

	if (debug) {
		cdb_debug(a_descr->cdb, "READ CAP from %u (%u, %u): ",
			  atio->init_id, vsize, sector_size);
	}

	bzero(srp, sizeof(*srp));
	scsi_ulto4b(vsize, srp->addr);
	scsi_ulto4b(sector_size, srp->length);

	ctio->dxfer_len = sizeof(*srp);
	ctio->ccb_h.flags |= CAM_DIR_IN | CAM_SEND_STATUS;
	ctio->scsi_status = SCSI_STATUS_OK;
	return (0);
}