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
struct TYPE_3__ {scalar_t__ flags; int /*<<< orphan*/  valid; } ;
struct TYPE_4__ {TYPE_1__ scsi; } ;
struct ccb_trans_settings {TYPE_2__ proto_specific; int /*<<< orphan*/  transport_version; int /*<<< orphan*/  transport; int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ccb_h; } ;
struct cam_path {struct cam_ed* device; } ;
struct cam_ed {int flags; int inq_flags; } ;

/* Variables and functions */
 int CAM_DEV_TAG_AFTER_COUNT ; 
 int /*<<< orphan*/  CAM_PRIORITY_NONE ; 
 scalar_t__ CTS_SCSI_FLAGS_TAG_ENB ; 
 int /*<<< orphan*/  CTS_SCSI_VALID_TQ ; 
 int /*<<< orphan*/  PROTO_SCSI ; 
 int /*<<< orphan*/  PROTO_VERSION_UNSPECIFIED ; 
 int SID_CmdQue ; 
 int SID_Sync ; 
 int SID_WBus16 ; 
 int SID_WBus32 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XPORT_UNSPECIFIED ; 
 int /*<<< orphan*/  XPORT_VERSION_UNSPECIFIED ; 
 int /*<<< orphan*/  scsi_set_transfer_settings (struct ccb_trans_settings*,struct cam_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_setup_ccb (int /*<<< orphan*/ *,struct cam_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scsi_toggle_tags(struct cam_path *path)
{
	struct cam_ed *dev;

	/*
	 * Give controllers a chance to renegotiate
	 * before starting tag operations.  We
	 * "toggle" tagged queuing off then on
	 * which causes the tag enable command delay
	 * counter to come into effect.
	 */
	dev = path->device;
	if ((dev->flags & CAM_DEV_TAG_AFTER_COUNT) != 0
	 || ((dev->inq_flags & SID_CmdQue) != 0
 	  && (dev->inq_flags & (SID_Sync|SID_WBus16|SID_WBus32)) != 0)) {
		struct ccb_trans_settings cts;

		xpt_setup_ccb(&cts.ccb_h, path, CAM_PRIORITY_NONE);
		cts.protocol = PROTO_SCSI;
		cts.protocol_version = PROTO_VERSION_UNSPECIFIED;
		cts.transport = XPORT_UNSPECIFIED;
		cts.transport_version = XPORT_VERSION_UNSPECIFIED;
		cts.proto_specific.scsi.flags = 0;
		cts.proto_specific.scsi.valid = CTS_SCSI_VALID_TQ;
		scsi_set_transfer_settings(&cts, path,
					  /*async_update*/TRUE);
		cts.proto_specific.scsi.flags = CTS_SCSI_FLAGS_TAG_ENB;
		scsi_set_transfer_settings(&cts, path,
					  /*async_update*/TRUE);
	}
}