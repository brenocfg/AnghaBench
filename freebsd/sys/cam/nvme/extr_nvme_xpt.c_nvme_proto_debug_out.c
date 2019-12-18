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
struct TYPE_3__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {scalar_t__ func_code; int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ nvmeio; TYPE_2__ ccb_h; } ;
struct nvme_command {int dummy; } ;
typedef  int /*<<< orphan*/  cdb_str ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_CDB ; 
 scalar_t__ XPT_NVME_ADMIN ; 
 scalar_t__ XPT_NVME_IO ; 
 int /*<<< orphan*/  nvme_cmd_string (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nvme_op_string (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
nvme_proto_debug_out(union ccb *ccb)
{
	char cdb_str[(sizeof(struct nvme_command) * 3) + 1];

	if (ccb->ccb_h.func_code != XPT_NVME_IO &&
	    ccb->ccb_h.func_code != XPT_NVME_ADMIN)
		return;

	CAM_DEBUG(ccb->ccb_h.path,
	    CAM_DEBUG_CDB,("%s. NCB: %s\n", nvme_op_string(&ccb->nvmeio.cmd,
		ccb->ccb_h.func_code == XPT_NVME_ADMIN),
		nvme_cmd_string(&ccb->nvmeio.cmd, cdb_str, sizeof(cdb_str))));
}