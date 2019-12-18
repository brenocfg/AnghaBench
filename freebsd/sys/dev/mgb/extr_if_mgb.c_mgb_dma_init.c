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
struct mgb_softc {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
struct TYPE_3__ {int isc_nrxqsets; } ;

/* Variables and functions */
 TYPE_1__* iflib_get_softc_ctx (int /*<<< orphan*/ ) ; 
 int mgb_dma_rx_ring_init (struct mgb_softc*,int) ; 
 int mgb_dma_tx_ring_init (struct mgb_softc*,int) ; 

__attribute__((used)) static int
mgb_dma_init(struct mgb_softc *sc)
{
	if_softc_ctx_t scctx;
	int ch, error = 0;

	scctx = iflib_get_softc_ctx(sc->ctx);

	for (ch = 0; ch < scctx->isc_nrxqsets; ch++)
		if ((error = mgb_dma_rx_ring_init(sc, ch)))
			goto fail;

	for (ch = 0; ch < scctx->isc_nrxqsets; ch++)
		if ((error = mgb_dma_tx_ring_init(sc, ch)))
			goto fail;

fail:
	return error;
}