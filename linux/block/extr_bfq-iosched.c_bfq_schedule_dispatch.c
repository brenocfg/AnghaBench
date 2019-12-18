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
struct bfq_data {scalar_t__ queued; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_log (struct bfq_data*,char*) ; 
 int /*<<< orphan*/  blk_mq_run_hw_queues (int /*<<< orphan*/ ,int) ; 

void bfq_schedule_dispatch(struct bfq_data *bfqd)
{
	if (bfqd->queued != 0) {
		bfq_log(bfqd, "schedule dispatch");
		blk_mq_run_hw_queues(bfqd->queue, true);
	}
}