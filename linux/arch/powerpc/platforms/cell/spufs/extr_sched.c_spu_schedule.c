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
struct spu_context {scalar_t__ state; int /*<<< orphan*/  state_mutex; } ;
struct spu {int dummy; } ;

/* Variables and functions */
 scalar_t__ SPU_STATE_SAVED ; 
 int /*<<< orphan*/  __spu_schedule (struct spu*,struct spu_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 

__attribute__((used)) static void spu_schedule(struct spu *spu, struct spu_context *ctx)
{
	/* not a candidate for interruptible because it's called either
	   from the scheduler thread or from spu_deactivate */
	mutex_lock(&ctx->state_mutex);
	if (ctx->state == SPU_STATE_SAVED)
		__spu_schedule(spu, ctx);
	spu_release(ctx);
}