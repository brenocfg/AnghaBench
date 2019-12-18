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
typedef  int /*<<< orphan*/  uint8_t ;
struct vmbus_xact_ctx {int xc_flags; struct vmbus_xact* xc_active; int /*<<< orphan*/  xc_lock; } ;
struct vmbus_xact {void* x_resp; size_t x_resp_len; struct vmbus_xact_ctx* x_ctx; } ;
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int VMBUS_XACT_CTXF_DESTROY ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vmbus_xact_save_resp (struct vmbus_xact*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const void *
vmbus_xact_return(struct vmbus_xact *xact, size_t *resp_len)
{
	struct vmbus_xact_ctx *ctx = xact->x_ctx;
	const void *resp;

	mtx_assert(&ctx->xc_lock, MA_OWNED);
	KASSERT(ctx->xc_active == xact, ("xact trashed"));

	if ((ctx->xc_flags & VMBUS_XACT_CTXF_DESTROY) && xact->x_resp == NULL) {
		uint8_t b = 0;

		/*
		 * Orphaned and no response was received yet; fake up
		 * an one byte response.
		 */
		printf("vmbus: xact ctx was orphaned w/ pending xact\n");
		vmbus_xact_save_resp(ctx->xc_active, &b, sizeof(b));
	}
	KASSERT(xact->x_resp != NULL, ("no response"));

	ctx->xc_active = NULL;

	resp = xact->x_resp;
	*resp_len = xact->x_resp_len;

	return (resp);
}