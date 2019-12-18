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
struct nvme_controller {int /*<<< orphan*/  is_resetting; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_cmpset_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  nvme_ctrlr_fail (struct nvme_controller*) ; 
 int nvme_ctrlr_hw_reset (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_start (struct nvme_controller*,int) ; 
 int /*<<< orphan*/  nvme_printf (struct nvme_controller*,char*) ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static void
nvme_ctrlr_reset_task(void *arg, int pending)
{
	struct nvme_controller	*ctrlr = arg;
	int			status;

	nvme_printf(ctrlr, "resetting controller\n");
	status = nvme_ctrlr_hw_reset(ctrlr);
	/*
	 * Use pause instead of DELAY, so that we yield to any nvme interrupt
	 *  handlers on this CPU that were blocked on a qpair lock. We want
	 *  all nvme interrupts completed before proceeding with restarting the
	 *  controller.
	 *
	 * XXX - any way to guarantee the interrupt handlers have quiesced?
	 */
	pause("nvmereset", hz / 10);
	if (status == 0)
		nvme_ctrlr_start(ctrlr, true);
	else
		nvme_ctrlr_fail(ctrlr);

	atomic_cmpset_32(&ctrlr->is_resetting, 1, 0);
}