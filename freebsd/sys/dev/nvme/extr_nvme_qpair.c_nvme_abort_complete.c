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
struct nvme_tracker {size_t cid; TYPE_1__* qpair; } ;
struct nvme_completion {int cdw0; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrlr; int /*<<< orphan*/ ** act_tr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_PRINT_ALL ; 
 int /*<<< orphan*/  NVME_SCT_GENERIC ; 
 int /*<<< orphan*/  NVME_SC_ABORTED_BY_REQUEST ; 
 int /*<<< orphan*/  nvme_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nvme_qpair_manual_complete_tracker (TYPE_1__*,struct nvme_tracker*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_abort_complete(void *arg, const struct nvme_completion *status)
{
	struct nvme_tracker	*tr = arg;

	/*
	 * If cdw0 == 1, the controller was not able to abort the command
	 *  we requested.  We still need to check the active tracker array,
	 *  to cover race where I/O timed out at same time controller was
	 *  completing the I/O.
	 */
	if (status->cdw0 == 1 && tr->qpair->act_tr[tr->cid] != NULL) {
		/*
		 * An I/O has timed out, and the controller was unable to
		 *  abort it for some reason.  Construct a fake completion
		 *  status, and then complete the I/O's tracker manually.
		 */
		nvme_printf(tr->qpair->ctrlr,
		    "abort command failed, aborting command manually\n");
		nvme_qpair_manual_complete_tracker(tr->qpair, tr,
		    NVME_SCT_GENERIC, NVME_SC_ABORTED_BY_REQUEST, 0, ERROR_PRINT_ALL);
	}
}