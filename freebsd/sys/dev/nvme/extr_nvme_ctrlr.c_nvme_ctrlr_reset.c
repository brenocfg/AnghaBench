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
struct nvme_controller {int /*<<< orphan*/  reset_task; int /*<<< orphan*/  taskqueue; scalar_t__ is_failed; int /*<<< orphan*/  is_resetting; } ;

/* Variables and functions */
 int atomic_cmpset_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
nvme_ctrlr_reset(struct nvme_controller *ctrlr)
{
	int cmpset;

	cmpset = atomic_cmpset_32(&ctrlr->is_resetting, 0, 1);

	if (cmpset == 0 || ctrlr->is_failed)
		/*
		 * Controller is already resetting or has failed.  Return
		 *  immediately since there is no need to kick off another
		 *  reset in these cases.
		 */
		return;

	taskqueue_enqueue(ctrlr->taskqueue, &ctrlr->reset_task);
}