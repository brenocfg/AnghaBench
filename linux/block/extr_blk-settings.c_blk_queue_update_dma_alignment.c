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
struct request_queue {int dma_alignment; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SIZE ; 

void blk_queue_update_dma_alignment(struct request_queue *q, int mask)
{
	BUG_ON(mask > PAGE_SIZE);

	if (mask > q->dma_alignment)
		q->dma_alignment = mask;
}