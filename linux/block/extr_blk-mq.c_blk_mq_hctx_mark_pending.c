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
struct blk_mq_hw_ctx {size_t type; int /*<<< orphan*/  ctx_map; } ;
struct blk_mq_ctx {int* index_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbitmap_set_bit (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  sbitmap_test_bit (int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static void blk_mq_hctx_mark_pending(struct blk_mq_hw_ctx *hctx,
				     struct blk_mq_ctx *ctx)
{
	const int bit = ctx->index_hw[hctx->type];

	if (!sbitmap_test_bit(&hctx->ctx_map, bit))
		sbitmap_set_bit(&hctx->ctx_map, bit);
}