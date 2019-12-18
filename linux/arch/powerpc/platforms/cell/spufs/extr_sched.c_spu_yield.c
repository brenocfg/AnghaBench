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
struct spu_context {int flags; int /*<<< orphan*/  state_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PRIO ; 
 int SPU_CREATE_NOSCHED ; 
 int /*<<< orphan*/  __spu_deactivate (struct spu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_context_nospu_trace (int /*<<< orphan*/ ,struct spu_context*) ; 
 int /*<<< orphan*/  spu_yield__enter ; 

void spu_yield(struct spu_context *ctx)
{
	spu_context_nospu_trace(spu_yield__enter, ctx);
	if (!(ctx->flags & SPU_CREATE_NOSCHED)) {
		mutex_lock(&ctx->state_mutex);
		__spu_deactivate(ctx, 0, MAX_PRIO);
		mutex_unlock(&ctx->state_mutex);
	}
}