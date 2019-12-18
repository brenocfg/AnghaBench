#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvme_controller {int /*<<< orphan*/  is_resetting; scalar_t__ is_failed; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_cmpset_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_ctrlr_fail (struct nvme_controller*) ; 
 scalar_t__ nvme_ctrlr_hw_reset (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_start (struct nvme_controller*,int) ; 
 int /*<<< orphan*/  nvme_printf (struct nvme_controller*,char*) ; 

int
nvme_ctrlr_resume(struct nvme_controller *ctrlr)
{

	/*
	 * Can't touch failed controllers, so nothing to do to resume.
	 */
	if (ctrlr->is_failed)
		return (0);

	/*
	 * Have to reset the hardware twice, just like we do on attach. See
	 * nmve_attach() for why.
	 */
	if (nvme_ctrlr_hw_reset(ctrlr) != 0)
		goto fail;
	if (nvme_ctrlr_hw_reset(ctrlr) != 0)
		goto fail;

	/*
	 * Now that we're reset the hardware, we can restart the controller. Any
	 * I/O that was pending is requeued. Any admin commands are aborted with
	 * an error. Once we've restarted, take the controller out of reset.
	 */
	nvme_ctrlr_start(ctrlr, true);
	atomic_cmpset_32(&ctrlr->is_resetting, 1, 0);

	return (0);
fail:
	/*
	 * Since we can't bring the controller out of reset, announce and fail
	 * the controller. However, we have to return success for the resume
	 * itself, due to questionable APIs.
	 */
	nvme_printf(ctrlr, "Failed to reset on resume, failing.\n");
	nvme_ctrlr_fail(ctrlr);
	atomic_cmpset_32(&ctrlr->is_resetting, 1, 0);
	return (0);
}