#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* if_softc_ctx_t ;
typedef  TYPE_2__* if_ctx_t ;
struct TYPE_4__ {scalar_t__ isc_max_frame_size; } ;
struct TYPE_5__ {scalar_t__ ifc_rx_mbuf_sz; TYPE_1__ ifc_softc_ctx; } ;

/* Variables and functions */
 scalar_t__ MCLBYTES ; 
 scalar_t__ MJUMPAGESIZE ; 

__attribute__((used)) static void
iflib_calc_rx_mbuf_sz(if_ctx_t ctx)
{
	if_softc_ctx_t sctx = &ctx->ifc_softc_ctx;

	/*
	 * XXX don't set the max_frame_size to larger
	 * than the hardware can handle
	 */
	if (sctx->isc_max_frame_size <= MCLBYTES)
		ctx->ifc_rx_mbuf_sz = MCLBYTES;
	else
		ctx->ifc_rx_mbuf_sz = MJUMPAGESIZE;
}