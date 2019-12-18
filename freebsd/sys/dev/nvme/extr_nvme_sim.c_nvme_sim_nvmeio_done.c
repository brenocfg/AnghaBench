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
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpl; } ;
union ccb {TYPE_2__ ccb_h; TYPE_1__ nvmeio; } ;
struct nvme_completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_SIM_QUEUED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct nvme_completion const*,int) ; 
 scalar_t__ nvme_completion_is_error (struct nvme_completion const*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_done_direct (union ccb*) ; 

__attribute__((used)) static void
nvme_sim_nvmeio_done(void *ccb_arg, const struct nvme_completion *cpl)
{
	union ccb *ccb = (union ccb *)ccb_arg;

	/*
	 * Let the periph know the completion, and let it sort out what
	 * it means. Make our best guess, though for the status code.
	 */
	memcpy(&ccb->nvmeio.cpl, cpl, sizeof(*cpl));
	ccb->ccb_h.status &= ~CAM_SIM_QUEUED;
	if (nvme_completion_is_error(cpl)) {
		ccb->ccb_h.status = CAM_REQ_CMP_ERR;
		xpt_done(ccb);
	} else {
		ccb->ccb_h.status = CAM_REQ_CMP;
		xpt_done_direct(ccb);
	}
}