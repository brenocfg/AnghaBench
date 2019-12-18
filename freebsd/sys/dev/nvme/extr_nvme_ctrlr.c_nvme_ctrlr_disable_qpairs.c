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
struct nvme_controller {int num_io_queues; int /*<<< orphan*/ * ioq; scalar_t__ is_initialized; int /*<<< orphan*/  adminq; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_admin_qpair_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_io_qpair_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvme_ctrlr_disable_qpairs(struct nvme_controller *ctrlr)
{
	int i;

	nvme_admin_qpair_disable(&ctrlr->adminq);
	/*
	 * I/O queues are not allocated before the initial HW
	 *  reset, so do not try to disable them.  Use is_initialized
	 *  to determine if this is the initial HW reset.
	 */
	if (ctrlr->is_initialized) {
		for (i = 0; i < ctrlr->num_io_queues; i++)
			nvme_io_qpair_disable(&ctrlr->ioq[i]);
	}
}