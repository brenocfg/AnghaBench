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
struct vmbus_xact_ctx {struct vmbus_xact* xc_free; int /*<<< orphan*/  xc_lock; int /*<<< orphan*/ * xc_active; } ;
struct vmbus_xact {int /*<<< orphan*/ * x_resp; struct vmbus_xact_ctx* x_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct vmbus_xact**) ; 

void
vmbus_xact_put(struct vmbus_xact *xact)
{
	struct vmbus_xact_ctx *ctx = xact->x_ctx;

	KASSERT(ctx->xc_active == NULL, ("pending active xact"));
	xact->x_resp = NULL;

	mtx_lock(&ctx->xc_lock);
	KASSERT(ctx->xc_free == NULL, ("has free xact"));
	ctx->xc_free = xact;
	mtx_unlock(&ctx->xc_lock);
	wakeup(&ctx->xc_free);
}