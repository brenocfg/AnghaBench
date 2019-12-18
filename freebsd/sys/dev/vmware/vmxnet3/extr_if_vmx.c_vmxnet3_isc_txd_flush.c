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
typedef  size_t uint16_t ;
struct vmxnet3_txqueue {int /*<<< orphan*/  vxtxq_id; int /*<<< orphan*/  vxtxq_last_flush; } ;
struct vmxnet3_softc {struct vmxnet3_txqueue* vmx_txq; } ;
typedef  int /*<<< orphan*/  qidx_t ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_BAR0_TXH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_write_bar0 (struct vmxnet3_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_isc_txd_flush(void *vsc, uint16_t txqid, qidx_t pidx)
{
	struct vmxnet3_softc *sc;
	struct vmxnet3_txqueue *txq;

	sc = vsc;
	txq = &sc->vmx_txq[txqid];

	/*
	 * pidx is what we last set ipi_new_pidx to in
	 * vmxnet3_isc_txd_encap()
	 */

	/*
	 * Avoid expensive register updates if the flush request is
	 * redundant.
	 */
	if (txq->vxtxq_last_flush == pidx)
		return;
	txq->vxtxq_last_flush = pidx;
	vmxnet3_write_bar0(sc, VMXNET3_BAR0_TXH(txq->vxtxq_id), pidx);
}