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
struct request_queue {int /*<<< orphan*/  limits; int /*<<< orphan*/ * make_request_fn; int /*<<< orphan*/  nr_requests; } ;
typedef  int /*<<< orphan*/  make_request_fn ;

/* Variables and functions */
 int /*<<< orphan*/  BLKDEV_MAX_RQ ; 
 int /*<<< orphan*/  blk_queue_dma_alignment (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_set_default_limits (int /*<<< orphan*/ *) ; 

void blk_queue_make_request(struct request_queue *q, make_request_fn *mfn)
{
	/*
	 * set defaults
	 */
	q->nr_requests = BLKDEV_MAX_RQ;

	q->make_request_fn = mfn;
	blk_queue_dma_alignment(q, 511);

	blk_set_default_limits(&q->limits);
}