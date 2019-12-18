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
struct bfq_queue {int dummy; } ;
struct bfq_data {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct bfq_queue* bfqq_find_close (struct bfq_data*,struct bfq_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bfq_queue *bfq_find_close_cooperator(struct bfq_data *bfqd,
						   struct bfq_queue *cur_bfqq,
						   sector_t sector)
{
	struct bfq_queue *bfqq;

	/*
	 * We shall notice if some of the queues are cooperating,
	 * e.g., working closely on the same area of the device. In
	 * that case, we can group them together and: 1) don't waste
	 * time idling, and 2) serve the union of their requests in
	 * the best possible order for throughput.
	 */
	bfqq = bfqq_find_close(bfqd, cur_bfqq, sector);
	if (!bfqq || bfqq == cur_bfqq)
		return NULL;

	return bfqq;
}