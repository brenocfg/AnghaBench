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
struct vmbus_xact_ctx {int xc_flags; int /*<<< orphan*/ * xc_active; int /*<<< orphan*/  xc_lock; } ;
struct vmbus_xact {struct vmbus_xact_ctx* x_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int VMBUS_XACT_CTXF_DESTROY ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vmbus_xact_save_resp (struct vmbus_xact*,void const*,size_t) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ **) ; 

void
vmbus_xact_wakeup(struct vmbus_xact *xact, const void *data, size_t dlen)
{
	struct vmbus_xact_ctx *ctx = xact->x_ctx;
	int do_wakeup = 0;

	mtx_lock(&ctx->xc_lock);
	/*
	 * NOTE:
	 * xc_active could be NULL, if the ctx has been orphaned.
	 */
	if (ctx->xc_active != NULL) {
		vmbus_xact_save_resp(xact, data, dlen);
		do_wakeup = 1;
	} else {
		KASSERT(ctx->xc_flags & VMBUS_XACT_CTXF_DESTROY,
		    ("no active xact pending"));
		printf("vmbus: drop xact response\n");
	}
	mtx_unlock(&ctx->xc_lock);

	if (do_wakeup)
		wakeup(&ctx->xc_active);
}