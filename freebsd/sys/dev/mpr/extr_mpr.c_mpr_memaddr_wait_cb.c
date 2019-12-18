#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpr_busdma_context {int error; int completed; scalar_t__ abandoned; scalar_t__* addr; int /*<<< orphan*/  buffer_dmamap; int /*<<< orphan*/  buffer_dmat; int /*<<< orphan*/  softc; } ;
struct TYPE_3__ {scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_MPR ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct mpr_busdma_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpr_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpr_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct mpr_busdma_context*) ; 

void
mpr_memaddr_wait_cb(void *arg, bus_dma_segment_t *segs, int nsegs, int error)
{
	struct mpr_busdma_context *ctx;
	int need_unload, need_free;

	ctx = (struct mpr_busdma_context *)arg;
	need_unload = 0;
	need_free = 0;

	mpr_lock(ctx->softc);
	ctx->error = error;
	ctx->completed = 1;
	if ((error == 0) && (ctx->abandoned == 0)) {
		*ctx->addr = segs[0].ds_addr;
	} else {
		if (nsegs != 0)
			need_unload = 1;
		if (ctx->abandoned != 0)
			need_free = 1;
	}
	if (need_free == 0)
		wakeup(ctx);

	mpr_unlock(ctx->softc);

	if (need_unload != 0) {
		bus_dmamap_unload(ctx->buffer_dmat,
				  ctx->buffer_dmamap);
		*ctx->addr = 0;
	}

	if (need_free != 0)
		free(ctx, M_MPR);
}