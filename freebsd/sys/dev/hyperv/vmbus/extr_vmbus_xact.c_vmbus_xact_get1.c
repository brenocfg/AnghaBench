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
typedef  int uint32_t ;
struct vmbus_xact_ctx {int xc_flags; int /*<<< orphan*/  xc_lock; struct vmbus_xact* xc_free; } ;
struct vmbus_xact {int /*<<< orphan*/ * x_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (struct vmbus_xact**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vmbus_xact *
vmbus_xact_get1(struct vmbus_xact_ctx *ctx, uint32_t dtor_flag)
{
	struct vmbus_xact *xact;

	mtx_lock(&ctx->xc_lock);

	while ((ctx->xc_flags & dtor_flag) == 0 && ctx->xc_free == NULL)
		mtx_sleep(&ctx->xc_free, &ctx->xc_lock, 0, "gxact", 0);
	if (ctx->xc_flags & dtor_flag) {
		/* Being destroyed */
		xact = NULL;
	} else {
		xact = ctx->xc_free;
		KASSERT(xact != NULL, ("no free xact"));
		KASSERT(xact->x_resp == NULL, ("xact has pending response"));
		ctx->xc_free = NULL;
	}

	mtx_unlock(&ctx->xc_lock);

	return (xact);
}