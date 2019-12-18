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
struct vmxnet3_txq_shared {int dummy; } ;
struct vmxnet3_softc {int /*<<< orphan*/  vmx_dev; int /*<<< orphan*/  vmx_qs_dma; int /*<<< orphan*/  vmx_ctx; TYPE_1__* vmx_scctx; } ;
struct vmxnet3_rxq_shared {int dummy; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
struct TYPE_2__ {int isc_ntxqsets; int isc_nrxqsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int iflib_dma_alloc_align (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmxnet3_queues_shared_alloc(struct vmxnet3_softc *sc)
{
	if_softc_ctx_t scctx;
	int size;
	int error;
	
	scctx = sc->vmx_scctx;

	/*
	 * The txq and rxq shared data areas must be allocated contiguously
	 * as vmxnet3_driver_shared contains only a single address member
	 * for the shared queue data area.
	 */
	size = scctx->isc_ntxqsets * sizeof(struct vmxnet3_txq_shared) +
	    scctx->isc_nrxqsets * sizeof(struct vmxnet3_rxq_shared);
	error = iflib_dma_alloc_align(sc->vmx_ctx, size, 128, &sc->vmx_qs_dma, 0);
	if (error) {
		device_printf(sc->vmx_dev, "cannot alloc queue shared memory\n");
		return (error);
	}

	return (0);
}