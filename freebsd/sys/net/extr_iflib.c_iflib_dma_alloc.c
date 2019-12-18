#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  iflib_dma_info_t ;
typedef  TYPE_1__* if_shared_ctx_t ;
typedef  TYPE_2__* if_ctx_t ;
struct TYPE_6__ {TYPE_1__* ifc_sctx; } ;
struct TYPE_5__ {scalar_t__ isc_q_align; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int iflib_dma_alloc_align (TYPE_2__*,int,scalar_t__,int /*<<< orphan*/ ,int) ; 

int
iflib_dma_alloc(if_ctx_t ctx, int size, iflib_dma_info_t dma, int mapflags)
{
	if_shared_ctx_t sctx = ctx->ifc_sctx;

	KASSERT(sctx->isc_q_align != 0, ("alignment value not initialized"));

	return (iflib_dma_alloc_align(ctx, size, sctx->isc_q_align, dma, mapflags));
}