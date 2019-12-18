#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct TYPE_7__ {scalar_t__ valid; } ;
struct TYPE_6__ {scalar_t__ valid; } ;
struct TYPE_8__ {int /*<<< orphan*/  func_code; } ;
struct ccb_trans_settings {TYPE_3__ xport_specific; TYPE_2__ proto_specific; int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  protocol; int /*<<< orphan*/  transport_version; int /*<<< orphan*/  transport; int /*<<< orphan*/  type; TYPE_4__ ccb_h; } ;
struct ccb_pathinq {int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  protocol; int /*<<< orphan*/  transport_version; int /*<<< orphan*/  transport; } ;
struct cam_path {TYPE_1__* device; } ;
struct TYPE_5__ {int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  protocol; int /*<<< orphan*/  transport_version; int /*<<< orphan*/  transport; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NONE ; 
 int /*<<< orphan*/  CTS_TYPE_CURRENT_SETTINGS ; 
 int /*<<< orphan*/  XPT_SET_TRAN_SETTINGS ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_inq (struct ccb_pathinq*,struct cam_path*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_4__*,struct cam_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_device_transport(struct cam_path *path)
{
	struct ccb_pathinq cpi;
	struct ccb_trans_settings cts;
	/* XXX get data from nvme namespace and other info ??? */

	/* Get transport information from the SIM */
	xpt_path_inq(&cpi, path);

	path->device->transport = cpi.transport;
	path->device->transport_version = cpi.transport_version;

	path->device->protocol = cpi.protocol;
	path->device->protocol_version = cpi.protocol_version;

	/* Tell the controller what we think */
	xpt_setup_ccb(&cts.ccb_h, path, CAM_PRIORITY_NONE);
	cts.ccb_h.func_code = XPT_SET_TRAN_SETTINGS;
	cts.type = CTS_TYPE_CURRENT_SETTINGS;
	cts.transport = path->device->transport;
	cts.transport_version = path->device->transport_version;
	cts.protocol = path->device->protocol;
	cts.protocol_version = path->device->protocol_version;
	cts.proto_specific.valid = 0;
	cts.xport_specific.valid = 0;
	xpt_action((union ccb *)&cts);
}