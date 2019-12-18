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
struct nvme_qpair {int phase; int num_entries; int /*<<< orphan*/  cpl; int /*<<< orphan*/  cmd; scalar_t__ cq_head; scalar_t__ sq_tail; scalar_t__ sq_head; } ;
struct nvme_completion {int dummy; } ;
struct nvme_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nvme_qpair_reset(struct nvme_qpair *qpair)
{

	qpair->sq_head = qpair->sq_tail = qpair->cq_head = 0;

	/*
	 * First time through the completion queue, HW will set phase
	 *  bit on completions to 1.  So set this to 1 here, indicating
	 *  we're looking for a 1 to know which entries have completed.
	 *  we'll toggle the bit each time when the completion queue
	 *  rolls over.
	 */
	qpair->phase = 1;

	memset(qpair->cmd, 0,
	    qpair->num_entries * sizeof(struct nvme_command));
	memset(qpair->cpl, 0,
	    qpair->num_entries * sizeof(struct nvme_completion));
}