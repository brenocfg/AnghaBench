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
struct spu_context {scalar_t__ state; TYPE_1__* spu; } ;
struct TYPE_4__ {int /*<<< orphan*/  list_mutex; } ;
struct TYPE_3__ {int node; } ;

/* Variables and functions */
 scalar_t__ SPU_STATE_RUNNABLE ; 
 int /*<<< orphan*/  __spu_update_sched_info (struct spu_context*) ; 
 TYPE_2__* cbe_spu_info ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void spu_update_sched_info(struct spu_context *ctx)
{
	int node;

	if (ctx->state == SPU_STATE_RUNNABLE) {
		node = ctx->spu->node;

		/*
		 * Take list_mutex to sync with find_victim().
		 */
		mutex_lock(&cbe_spu_info[node].list_mutex);
		__spu_update_sched_info(ctx);
		mutex_unlock(&cbe_spu_info[node].list_mutex);
	} else {
		__spu_update_sched_info(ctx);
	}
}