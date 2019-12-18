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
struct vmbus_xact_ctx {int xc_flags; int /*<<< orphan*/ * xc_orphan; int /*<<< orphan*/  xc_active; int /*<<< orphan*/  xc_free; int /*<<< orphan*/  xc_lock; } ;

/* Variables and functions */
 int VMBUS_XACT_CTXF_DESTROY ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/ * vmbus_xact_get1 (struct vmbus_xact_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

bool
vmbus_xact_ctx_orphan(struct vmbus_xact_ctx *ctx)
{
	mtx_lock(&ctx->xc_lock);
	if (ctx->xc_flags & VMBUS_XACT_CTXF_DESTROY) {
		mtx_unlock(&ctx->xc_lock);
		return (false);
	}
	ctx->xc_flags |= VMBUS_XACT_CTXF_DESTROY;
	mtx_unlock(&ctx->xc_lock);

	wakeup(&ctx->xc_free);
	wakeup(&ctx->xc_active);

	ctx->xc_orphan = vmbus_xact_get1(ctx, 0);
	if (ctx->xc_orphan == NULL)
		panic("can't get xact");
	return (true);
}