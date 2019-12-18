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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct mrsas_mpt_cmd {scalar_t__ ccb_ptr; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_RELEASE_SIMQ ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  xpt_freeze_simq (struct cam_sim*,int) ; 

__attribute__((used)) static void
mrsas_freeze_simq(struct mrsas_mpt_cmd *cmd, struct cam_sim *sim)
{
	union ccb *ccb = (union ccb *)(cmd->ccb_ptr);

	xpt_freeze_simq(sim, 1);
	ccb->ccb_h.status |= CAM_RELEASE_SIMQ;
	ccb->ccb_h.status |= CAM_REQUEUE_REQ;
}