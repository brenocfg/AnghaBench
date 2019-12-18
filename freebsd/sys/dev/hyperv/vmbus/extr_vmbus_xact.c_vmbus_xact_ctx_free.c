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
struct vmbus_xact_ctx {int xc_flags; int /*<<< orphan*/  xc_lock; int /*<<< orphan*/ * xc_orphan; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int VMBUS_XACT_CTXF_DESTROY ; 
 int /*<<< orphan*/  free (struct vmbus_xact_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_xact_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vmbus_xact_ctx_free(struct vmbus_xact_ctx *ctx)
{
	KASSERT(ctx->xc_flags & VMBUS_XACT_CTXF_DESTROY,
	    ("xact ctx was not orphaned"));
	KASSERT(ctx->xc_orphan != NULL, ("no orphaned xact"));

	vmbus_xact_free(ctx->xc_orphan);
	mtx_destroy(&ctx->xc_lock);
	free(ctx, M_DEVBUF);
}