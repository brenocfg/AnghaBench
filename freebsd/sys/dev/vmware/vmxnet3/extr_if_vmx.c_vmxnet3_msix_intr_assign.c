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
struct vmxnet3_softc {int /*<<< orphan*/  vmx_event_intr_irq; int /*<<< orphan*/  vxrxq_irq; struct vmxnet3_softc* vmx_rxq; TYPE_1__* vmx_scctx; } ;
struct vmxnet3_rxqueue {int /*<<< orphan*/  vmx_event_intr_irq; int /*<<< orphan*/  vxrxq_irq; struct vmxnet3_rxqueue* vmx_rxq; TYPE_1__* vmx_scctx; } ;
typedef  int /*<<< orphan*/  irq_name ;
typedef  TYPE_1__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_2__ {int isc_nrxqsets; int isc_ntxqsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFLIB_INTR_ADMIN ; 
 int /*<<< orphan*/  IFLIB_INTR_RX ; 
 int /*<<< orphan*/  IFLIB_INTR_TX ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct vmxnet3_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int iflib_irq_alloc_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmxnet3_softc*,int,char*) ; 
 int /*<<< orphan*/  iflib_softirq_alloc_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  vmxnet3_event_intr ; 
 int /*<<< orphan*/  vmxnet3_rxq_intr ; 

__attribute__((used)) static int
vmxnet3_msix_intr_assign(if_ctx_t ctx, int msix)
{
	struct vmxnet3_softc *sc;
	if_softc_ctx_t scctx;
	struct vmxnet3_rxqueue *rxq;
	int error;
	int i;
	char irq_name[16];

	sc = iflib_get_softc(ctx);
	scctx = sc->vmx_scctx;
	
	for (i = 0; i < scctx->isc_nrxqsets; i++) {
		snprintf(irq_name, sizeof(irq_name), "rxq%d", i);

		rxq = &sc->vmx_rxq[i];
		error = iflib_irq_alloc_generic(ctx, &rxq->vxrxq_irq, i + 1,
		    IFLIB_INTR_RX, vmxnet3_rxq_intr, rxq, i, irq_name);
		if (error) {
			device_printf(iflib_get_dev(ctx),
			    "Failed to register rxq %d interrupt handler\n", i);
			return (error);
		}
	}

	for (i = 0; i < scctx->isc_ntxqsets; i++) {
		snprintf(irq_name, sizeof(irq_name), "txq%d", i);

		/*
		 * Don't provide the corresponding rxq irq for reference -
		 * we want the transmit task to be attached to a task queue
		 * that is different from the one used by the corresponding
		 * rxq irq.  That is because the TX doorbell writes are very
		 * expensive as virtualized MMIO operations, so we want to
		 * be able to defer them to another core when possible so
		 * that they don't steal receive processing cycles during
		 * stack turnarounds like TCP ACK generation.  The other
		 * piece to this approach is enabling the iflib abdicate
		 * option (currently via an interface-specific
		 * tunable/sysctl).
		 */
		iflib_softirq_alloc_generic(ctx, NULL, IFLIB_INTR_TX, NULL, i,
		    irq_name);
	}

	error = iflib_irq_alloc_generic(ctx, &sc->vmx_event_intr_irq,
	    scctx->isc_nrxqsets + 1, IFLIB_INTR_ADMIN, vmxnet3_event_intr, sc, 0,
	    "event");
	if (error) {
		device_printf(iflib_get_dev(ctx),
		    "Failed to register event interrupt handler\n");
		return (error);
	}

	return (0);
}