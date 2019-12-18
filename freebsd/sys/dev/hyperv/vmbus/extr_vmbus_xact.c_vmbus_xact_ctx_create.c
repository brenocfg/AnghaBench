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
struct vmbus_xact_ctx {size_t xc_req_size; size_t xc_resp_size; size_t xc_priv_size; int /*<<< orphan*/  xc_lock; int /*<<< orphan*/ * xc_free; } ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (struct vmbus_xact_ctx*,int /*<<< orphan*/ ) ; 
 struct vmbus_xact_ctx* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmbus_xact_alloc (struct vmbus_xact_ctx*,int /*<<< orphan*/ ) ; 

struct vmbus_xact_ctx *
vmbus_xact_ctx_create(bus_dma_tag_t dtag, size_t req_size, size_t resp_size,
    size_t priv_size)
{
	struct vmbus_xact_ctx *ctx;

	KASSERT(req_size > 0, ("request size is 0"));
	KASSERT(resp_size > 0, ("response size is 0"));

	ctx = malloc(sizeof(*ctx), M_DEVBUF, M_WAITOK | M_ZERO);
	ctx->xc_req_size = req_size;
	ctx->xc_resp_size = resp_size;
	ctx->xc_priv_size = priv_size;

	ctx->xc_free = vmbus_xact_alloc(ctx, dtag);
	if (ctx->xc_free == NULL) {
		free(ctx, M_DEVBUF);
		return (NULL);
	}

	mtx_init(&ctx->xc_lock, "vmbus xact", NULL, MTX_DEF);

	return (ctx);
}