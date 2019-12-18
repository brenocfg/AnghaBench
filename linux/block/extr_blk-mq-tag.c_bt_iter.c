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
struct sbitmap {int dummy; } ;
struct request {scalar_t__ q; } ;
struct bt_iter_data {int reserved; int (* fn ) (struct blk_mq_hw_ctx*,struct request*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  data; struct blk_mq_hw_ctx* hctx; } ;
struct blk_mq_tags {struct request** rqs; scalar_t__ nr_reserved_tags; } ;
struct blk_mq_hw_ctx {scalar_t__ queue; struct blk_mq_tags* tags; } ;

/* Variables and functions */
 int stub1 (struct blk_mq_hw_ctx*,struct request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool bt_iter(struct sbitmap *bitmap, unsigned int bitnr, void *data)
{
	struct bt_iter_data *iter_data = data;
	struct blk_mq_hw_ctx *hctx = iter_data->hctx;
	struct blk_mq_tags *tags = hctx->tags;
	bool reserved = iter_data->reserved;
	struct request *rq;

	if (!reserved)
		bitnr += tags->nr_reserved_tags;
	rq = tags->rqs[bitnr];

	/*
	 * We can hit rq == NULL here, because the tagging functions
	 * test and set the bit before assigning ->rqs[].
	 */
	if (rq && rq->q == hctx->queue)
		return iter_data->fn(hctx, rq, iter_data->data, reserved);
	return true;
}