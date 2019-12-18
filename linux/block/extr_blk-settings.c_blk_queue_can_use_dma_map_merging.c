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
struct request_queue {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_virt_boundary (struct request_queue*,unsigned long) ; 
 unsigned long dma_get_merge_boundary (struct device*) ; 

bool blk_queue_can_use_dma_map_merging(struct request_queue *q,
				       struct device *dev)
{
	unsigned long boundary = dma_get_merge_boundary(dev);

	if (!boundary)
		return false;

	/* No need to update max_segment_size. see blk_queue_virt_boundary() */
	blk_queue_virt_boundary(q, boundary);

	return true;
}