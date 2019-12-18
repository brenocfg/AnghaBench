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
struct spu_context {int prio; int /*<<< orphan*/  rq; } ;
struct TYPE_2__ {int /*<<< orphan*/  bitmap; int /*<<< orphan*/ * runq; int /*<<< orphan*/  nr_waiting; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 TYPE_1__* spu_prio ; 
 int /*<<< orphan*/  spusched_timer ; 

__attribute__((used)) static void __spu_del_from_rq(struct spu_context *ctx)
{
	int prio = ctx->prio;

	if (!list_empty(&ctx->rq)) {
		if (!--spu_prio->nr_waiting)
			del_timer(&spusched_timer);
		list_del_init(&ctx->rq);

		if (list_empty(&spu_prio->runq[prio]))
			clear_bit(prio, spu_prio->bitmap);
	}
}