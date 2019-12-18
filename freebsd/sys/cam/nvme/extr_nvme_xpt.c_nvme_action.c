#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int func_code; TYPE_3__* path; } ;
union ccb {TYPE_2__ crcn; TYPE_1__ ccb_h; } ;
struct TYPE_7__ {int /*<<< orphan*/  periph; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
#define  XPT_DEV_ADVINFO 131 
#define  XPT_SCAN_BUS 130 
#define  XPT_SCAN_LUN 129 
#define  XPT_SCAN_TGT 128 
 int /*<<< orphan*/  nvme_dev_advinfo (union ccb*) ; 
 int /*<<< orphan*/  nvme_scan_lun (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  xpt_action_default (union ccb*) ; 

__attribute__((used)) static void
nvme_action(union ccb *start_ccb)
{
	CAM_DEBUG(start_ccb->ccb_h.path, CAM_DEBUG_TRACE,
	    ("nvme_action: func= %#x\n", start_ccb->ccb_h.func_code));

	switch (start_ccb->ccb_h.func_code) {
	case XPT_SCAN_BUS:
	case XPT_SCAN_TGT:
	case XPT_SCAN_LUN:
		nvme_scan_lun(start_ccb->ccb_h.path->periph,
			      start_ccb->ccb_h.path, start_ccb->crcn.flags,
			      start_ccb);
		break;
	case XPT_DEV_ADVINFO:
		nvme_dev_advinfo(start_ccb);
		break;

	default:
		xpt_action_default(start_ccb);
		break;
	}
}