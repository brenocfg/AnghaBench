#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ idi_size; } ;
struct vmxnet3_softc {int /*<<< orphan*/ * vmx_txq; int /*<<< orphan*/ * vmx_rxq; TYPE_1__ vmx_qs_dma; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_dma_free (TYPE_1__*) ; 
 struct vmxnet3_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_queues_free(if_ctx_t ctx)
{
	struct vmxnet3_softc *sc;

	sc = iflib_get_softc(ctx);

	/* Free queue state area that is shared with the device */
	if (sc->vmx_qs_dma.idi_size != 0) {
		iflib_dma_free(&sc->vmx_qs_dma);
		sc->vmx_qs_dma.idi_size = 0;
	}

	/* Free array of receive queues */
	if (sc->vmx_rxq != NULL) {
		free(sc->vmx_rxq, M_DEVBUF);
		sc->vmx_rxq = NULL;
	}

	/* Free array of transmit queues */
	if (sc->vmx_txq != NULL) {
		free(sc->vmx_txq, M_DEVBUF);
		sc->vmx_txq = NULL;
	}
}