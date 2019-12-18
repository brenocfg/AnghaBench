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
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct cam_periph {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arcmsr_rescanLun_cb(struct cam_periph *periph, union ccb *ccb)
{
/*
	if (ccb->ccb_h.status != CAM_REQ_CMP)
		printf("arcmsr_rescanLun_cb: Rescan Target=%x, lun=%x,"
			"failure status=%x\n", ccb->ccb_h.target_id,
			ccb->ccb_h.target_lun, ccb->ccb_h.status);
	else
		printf("arcmsr_rescanLun_cb: Rescan lun successfully!\n");
*/
	xpt_free_path(ccb->ccb_h.path);
	xpt_free_ccb(ccb);
}