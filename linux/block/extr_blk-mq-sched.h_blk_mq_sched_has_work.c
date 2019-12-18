#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct elevator_queue {TYPE_3__* type; } ;
struct blk_mq_hw_ctx {TYPE_1__* queue; } ;
struct TYPE_5__ {int (* has_work ) (struct blk_mq_hw_ctx*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {struct elevator_queue* elevator; } ;

/* Variables and functions */
 int stub1 (struct blk_mq_hw_ctx*) ; 

__attribute__((used)) static inline bool blk_mq_sched_has_work(struct blk_mq_hw_ctx *hctx)
{
	struct elevator_queue *e = hctx->queue->elevator;

	if (e && e->type->ops.has_work)
		return e->type->ops.has_work(hctx);

	return false;
}