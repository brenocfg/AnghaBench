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
struct blk_mq_hw_ctx {unsigned int dispatch_busy; TYPE_1__* queue; } ;
struct TYPE_2__ {scalar_t__ elevator; } ;

/* Variables and functions */
 int BLK_MQ_DISPATCH_BUSY_EWMA_FACTOR ; 
 int BLK_MQ_DISPATCH_BUSY_EWMA_WEIGHT ; 

__attribute__((used)) static void blk_mq_update_dispatch_busy(struct blk_mq_hw_ctx *hctx, bool busy)
{
	unsigned int ewma;

	if (hctx->queue->elevator)
		return;

	ewma = hctx->dispatch_busy;

	if (!ewma && !busy)
		return;

	ewma *= BLK_MQ_DISPATCH_BUSY_EWMA_WEIGHT - 1;
	if (busy)
		ewma += 1 << BLK_MQ_DISPATCH_BUSY_EWMA_FACTOR;
	ewma /= BLK_MQ_DISPATCH_BUSY_EWMA_WEIGHT;

	hctx->dispatch_busy = ewma;
}