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
struct TYPE_3__ {scalar_t__ func_code; TYPE_2__* path; } ;
union ccb {int /*<<< orphan*/  csio; TYPE_1__ ccb_h; } ;
struct cam_ed {int /*<<< orphan*/  inq_data; } ;
typedef  int /*<<< orphan*/  cdb_str ;
struct TYPE_4__ {struct cam_ed* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_CDB ; 
 int SCSI_MAX_CDBLEN ; 
 scalar_t__ XPT_SCSI_IO ; 
 int /*<<< orphan*/  scsi_cdb_string (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  scsi_op_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scsiio_cdb_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scsi_proto_debug_out(union ccb *ccb)
{
	char cdb_str[(SCSI_MAX_CDBLEN * 3) + 1];
	struct cam_ed *device;

	if (ccb->ccb_h.func_code != XPT_SCSI_IO)
		return;

	device = ccb->ccb_h.path->device;
	CAM_DEBUG(ccb->ccb_h.path,
	    CAM_DEBUG_CDB,("%s. CDB: %s\n",
		scsi_op_desc(scsiio_cdb_ptr(&ccb->csio)[0], &device->inq_data),
		scsi_cdb_string(scsiio_cdb_ptr(&ccb->csio), cdb_str, sizeof(cdb_str))));
}