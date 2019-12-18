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
typedef  int /*<<< orphan*/  uint8_t ;
struct virtio_scsi_cmd_req {uintptr_t tag; int /*<<< orphan*/  cdb; int /*<<< orphan*/  task_attr; int /*<<< orphan*/  lun; } ;
struct TYPE_3__ {int /*<<< orphan*/  cdb_bytes; int /*<<< orphan*/  cdb_ptr; } ;
struct TYPE_4__ {int flags; } ;
struct ccb_scsiio {int tag_action; int /*<<< orphan*/  cdb_len; TYPE_1__ cdb_io; TYPE_2__ ccb_h; } ;

/* Variables and functions */
 int CAM_CDB_POINTER ; 
#define  MSG_ACA_TASK 130 
#define  MSG_HEAD_OF_Q_TAG 129 
#define  MSG_ORDERED_Q_TAG 128 
 int /*<<< orphan*/  VIRTIO_SCSI_S_ACA ; 
 int /*<<< orphan*/  VIRTIO_SCSI_S_HEAD ; 
 int /*<<< orphan*/  VIRTIO_SCSI_S_ORDERED ; 
 int /*<<< orphan*/  VIRTIO_SCSI_S_SIMPLE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtscsi_set_request_lun (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtscsi_init_scsi_cmd_req(struct ccb_scsiio *csio,
    struct virtio_scsi_cmd_req *cmd_req)
{
	uint8_t attr;

	switch (csio->tag_action) {
	case MSG_HEAD_OF_Q_TAG:
		attr = VIRTIO_SCSI_S_HEAD;
		break;
	case MSG_ORDERED_Q_TAG:
		attr = VIRTIO_SCSI_S_ORDERED;
		break;
	case MSG_ACA_TASK:
		attr = VIRTIO_SCSI_S_ACA;
		break;
	default: /* MSG_SIMPLE_Q_TAG */
		attr = VIRTIO_SCSI_S_SIMPLE;
		break;
	}

	vtscsi_set_request_lun(&csio->ccb_h, cmd_req->lun);
	cmd_req->tag = (uintptr_t) csio;
	cmd_req->task_attr = attr;

	memcpy(cmd_req->cdb,
	    csio->ccb_h.flags & CAM_CDB_POINTER ?
	        csio->cdb_io.cdb_ptr : csio->cdb_io.cdb_bytes,
	    csio->cdb_len);
}