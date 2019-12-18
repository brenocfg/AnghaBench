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
struct blk_mq_hw_ctx {int /*<<< orphan*/  ctx_map; int /*<<< orphan*/  dispatch; } ;

/* Variables and functions */
 scalar_t__ blk_mq_sched_has_work (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 
 scalar_t__ sbitmap_any_bit_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool blk_mq_hctx_has_pending(struct blk_mq_hw_ctx *hctx)
{
	return !list_empty_careful(&hctx->dispatch) ||
		sbitmap_any_bit_set(&hctx->ctx_map) ||
			blk_mq_sched_has_work(hctx);
}