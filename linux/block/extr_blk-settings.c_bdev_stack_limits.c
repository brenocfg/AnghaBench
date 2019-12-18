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
struct request_queue {int /*<<< orphan*/  limits; } ;
struct queue_limits {int dummy; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 int blk_stack_limits (struct queue_limits*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_start_sect (struct block_device*) ; 

int bdev_stack_limits(struct queue_limits *t, struct block_device *bdev,
		      sector_t start)
{
	struct request_queue *bq = bdev_get_queue(bdev);

	start += get_start_sect(bdev);

	return blk_stack_limits(t, &bq->limits, start);
}