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
struct vmbus_xact_ctx {size_t xc_resp_size; struct vmbus_xact* xc_active; int /*<<< orphan*/  xc_lock; } ;
struct vmbus_xact {size_t x_resp_len; int /*<<< orphan*/  x_resp0; int /*<<< orphan*/  x_resp; struct vmbus_xact_ctx* x_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,size_t,size_t) ; 

__attribute__((used)) static void
vmbus_xact_save_resp(struct vmbus_xact *xact, const void *data, size_t dlen)
{
	struct vmbus_xact_ctx *ctx = xact->x_ctx;
	size_t cplen = dlen;

	mtx_assert(&ctx->xc_lock, MA_OWNED);

	if (cplen > ctx->xc_resp_size) {
		printf("vmbus: xact response truncated %zu -> %zu\n",
		    cplen, ctx->xc_resp_size);
		cplen = ctx->xc_resp_size;
	}

	KASSERT(ctx->xc_active == xact, ("xact mismatch"));
	memcpy(xact->x_resp0, data, cplen);
	xact->x_resp_len = cplen;
	xact->x_resp = xact->x_resp0;
}