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
struct nvme_controller {int num_io_queues; int /*<<< orphan*/ * ioq; int /*<<< orphan*/  adminq; int /*<<< orphan*/  is_failed; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  nvme_admin_qpair_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_io_qpair_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_notify_fail_consumers (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_qpair_fail (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvme_ctrlr_fail(struct nvme_controller *ctrlr)
{
	int i;

	ctrlr->is_failed = TRUE;
	nvme_admin_qpair_disable(&ctrlr->adminq);
	nvme_qpair_fail(&ctrlr->adminq);
	if (ctrlr->ioq != NULL) {
		for (i = 0; i < ctrlr->num_io_queues; i++) {
			nvme_io_qpair_disable(&ctrlr->ioq[i]);
			nvme_qpair_fail(&ctrlr->ioq[i]);
		}
	}
	nvme_notify_fail_consumers(ctrlr);
}