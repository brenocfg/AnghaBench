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
struct request {int dummy; } ;
struct bfq_data {int peak_rate_samples; int /*<<< orphan*/  tot_sectors_dispatched; scalar_t__ sequential_samples; int /*<<< orphan*/  last_rq_max_size; int /*<<< orphan*/  first_dispatch; int /*<<< orphan*/  last_dispatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_log (struct bfq_data*,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 

__attribute__((used)) static void bfq_reset_rate_computation(struct bfq_data *bfqd,
				       struct request *rq)
{
	if (rq != NULL) { /* new rq dispatch now, reset accordingly */
		bfqd->last_dispatch = bfqd->first_dispatch = ktime_get_ns();
		bfqd->peak_rate_samples = 1;
		bfqd->sequential_samples = 0;
		bfqd->tot_sectors_dispatched = bfqd->last_rq_max_size =
			blk_rq_sectors(rq);
	} else /* no new rq dispatched, just reset the number of samples */
		bfqd->peak_rate_samples = 0; /* full re-init on next disp. */

	bfq_log(bfqd,
		"reset_rate_computation at end, sample %u/%u tot_sects %llu",
		bfqd->peak_rate_samples, bfqd->sequential_samples,
		bfqd->tot_sectors_dispatched);
}