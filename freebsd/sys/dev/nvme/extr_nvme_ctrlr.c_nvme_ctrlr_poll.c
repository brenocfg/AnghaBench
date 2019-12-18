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
struct TYPE_2__ {scalar_t__ cpl; } ;
struct nvme_controller {int num_io_queues; TYPE_1__* ioq; TYPE_1__ adminq; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_qpair_process_completions (TYPE_1__*) ; 

void
nvme_ctrlr_poll(struct nvme_controller *ctrlr)
{
	int i;

	nvme_qpair_process_completions(&ctrlr->adminq);

	for (i = 0; i < ctrlr->num_io_queues; i++)
		if (ctrlr->ioq && ctrlr->ioq[i].cpl)
			nvme_qpair_process_completions(&ctrlr->ioq[i]);
}