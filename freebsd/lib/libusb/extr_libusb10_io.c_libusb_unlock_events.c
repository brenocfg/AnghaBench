#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ctx_handler; int /*<<< orphan*/  ctx_cond; } ;
typedef  TYPE_1__ libusb_context ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_UNLOCK (TYPE_1__*) ; 
 TYPE_1__* GET_CONTEXT (TYPE_1__*) ; 
 scalar_t__ NO_THREAD ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_self () ; 

void
libusb_unlock_events(libusb_context *ctx)
{
	ctx = GET_CONTEXT(ctx);
	if (ctx->ctx_handler == pthread_self()) {
		ctx->ctx_handler = NO_THREAD;
		pthread_cond_broadcast(&ctx->ctx_cond);
	}
	CTX_UNLOCK(ctx);
}