#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sbitmap {int dummy; } ;
struct dispatch_rq_data {TYPE_1__* rq; struct blk_mq_hw_ctx* hctx; } ;
struct blk_mq_hw_ctx {int type; struct blk_mq_ctx** ctxs; } ;
struct blk_mq_ctx {int /*<<< orphan*/  lock; TYPE_2__* rq_lists; } ;
typedef  enum hctx_type { ____Placeholder_hctx_type } hctx_type ;
struct TYPE_4__ {int /*<<< orphan*/  next; } ;
struct TYPE_3__ {int /*<<< orphan*/  queuelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (TYPE_2__*) ; 
 TYPE_1__* list_entry_rq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_clear_bit (struct sbitmap*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool dispatch_rq_from_ctx(struct sbitmap *sb, unsigned int bitnr,
		void *data)
{
	struct dispatch_rq_data *dispatch_data = data;
	struct blk_mq_hw_ctx *hctx = dispatch_data->hctx;
	struct blk_mq_ctx *ctx = hctx->ctxs[bitnr];
	enum hctx_type type = hctx->type;

	spin_lock(&ctx->lock);
	if (!list_empty(&ctx->rq_lists[type])) {
		dispatch_data->rq = list_entry_rq(ctx->rq_lists[type].next);
		list_del_init(&dispatch_data->rq->queuelist);
		if (list_empty(&ctx->rq_lists[type]))
			sbitmap_clear_bit(sb, bitnr);
	}
	spin_unlock(&ctx->lock);

	return !dispatch_data->rq;
}