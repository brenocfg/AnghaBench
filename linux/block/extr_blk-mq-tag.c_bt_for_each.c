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
struct sbitmap_queue {int /*<<< orphan*/  sb; } ;
struct bt_iter_data {void* data; int reserved; int /*<<< orphan*/ * fn; struct blk_mq_hw_ctx* hctx; } ;
struct blk_mq_hw_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  busy_iter_fn ;

/* Variables and functions */
 int /*<<< orphan*/  bt_iter ; 
 int /*<<< orphan*/  sbitmap_for_each_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bt_iter_data*) ; 

__attribute__((used)) static void bt_for_each(struct blk_mq_hw_ctx *hctx, struct sbitmap_queue *bt,
			busy_iter_fn *fn, void *data, bool reserved)
{
	struct bt_iter_data iter_data = {
		.hctx = hctx,
		.fn = fn,
		.data = data,
		.reserved = reserved,
	};

	sbitmap_for_each_set(&bt->sb, bt_iter, &iter_data);
}