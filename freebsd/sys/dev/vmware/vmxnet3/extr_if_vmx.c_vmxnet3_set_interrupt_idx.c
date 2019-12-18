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
struct vmxnet3_txqueue {int vxtxq_intr_idx; struct vmxnet3_txq_shared* vxtxq_ts; } ;
struct vmxnet3_txq_shared {int intr_idx; } ;
struct vmxnet3_softc {int vmx_event_intr_idx; struct vmxnet3_txqueue* vmx_txq; struct vmxnet3_rxqueue* vmx_rxq; TYPE_1__* vmx_scctx; } ;
struct vmxnet3_rxqueue {int vxrxq_intr_idx; struct vmxnet3_rxq_shared* vxrxq_rs; } ;
struct vmxnet3_rxq_shared {int intr_idx; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
struct TYPE_2__ {int isc_vectors; int isc_nrxqsets; int isc_ntxqsets; } ;

/* Variables and functions */

__attribute__((used)) static void
vmxnet3_set_interrupt_idx(struct vmxnet3_softc *sc)
{
	if_softc_ctx_t scctx;
	struct vmxnet3_txqueue *txq;
	struct vmxnet3_txq_shared *txs;
	struct vmxnet3_rxqueue *rxq;
	struct vmxnet3_rxq_shared *rxs;
	int intr_idx;
	int i;

	scctx = sc->vmx_scctx;

	/*
	 * There is always one interrupt per receive queue, assigned
	 * starting with the first interrupt.  When there is only one
	 * interrupt available, the event interrupt shares the receive queue
	 * interrupt, otherwise it uses the interrupt following the last
	 * receive queue interrupt.  Transmit queues are not assigned
	 * interrupts, so they are given indexes beyond the indexes that
	 * correspond to the real interrupts.
	 */

	/* The event interrupt is always the last vector. */
	sc->vmx_event_intr_idx = scctx->isc_vectors - 1;

	intr_idx = 0;
	for (i = 0; i < scctx->isc_nrxqsets; i++, intr_idx++) {
		rxq = &sc->vmx_rxq[i];
		rxs = rxq->vxrxq_rs;
		rxq->vxrxq_intr_idx = intr_idx;
		rxs->intr_idx = rxq->vxrxq_intr_idx;
	}

	/*
	 * Assign the tx queues interrupt indexes above what we are actually
	 * using.  These interrupts will never be enabled.
	 */
	intr_idx = scctx->isc_vectors;
	for (i = 0; i < scctx->isc_ntxqsets; i++, intr_idx++) {
		txq = &sc->vmx_txq[i];
		txs = txq->vxtxq_ts;
		txq->vxtxq_intr_idx = intr_idx;
		txs->intr_idx = txq->vxtxq_intr_idx;
	}
}