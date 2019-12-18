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
struct vmxnet3_softc {TYPE_1__* vmx_sctx; } ;
struct vmxnet3_rxring {int vxrxr_ndesc; int /*<<< orphan*/  vxrxr_rxd; void* vxrxr_gen; } ;
struct vmxnet3_comp_ring {void* vxcr_gen; scalar_t__ vxcr_next; } ;
struct vmxnet3_rxqueue {struct vmxnet3_comp_ring vxrxq_comp_ring; struct vmxnet3_rxring* vxrxq_cmd_ring; } ;
struct vmxnet3_rxdesc {int dummy; } ;
struct TYPE_2__ {int isc_nrxqs; } ;

/* Variables and functions */
 void* VMXNET3_INIT_GEN ; 
 int VMXNET3_RXRINGS_PERQ ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmxnet3_rxinit(struct vmxnet3_softc *sc, struct vmxnet3_rxqueue *rxq)
{
	struct vmxnet3_rxring *rxr;
	struct vmxnet3_comp_ring *rxc;
	int i;

	/*
	 * The descriptors will be populated with buffers during a
	 * subsequent invocation of vmxnet3_isc_rxd_refill()
	 */
	for (i = 0; i < sc->vmx_sctx->isc_nrxqs - 1; i++) {
		rxr = &rxq->vxrxq_cmd_ring[i];
		rxr->vxrxr_gen = VMXNET3_INIT_GEN;
		/*
		 * iflib has zeroed out the descriptor array during the
		 * prior attach or stop
		 */
	}

	for (/**/; i < VMXNET3_RXRINGS_PERQ; i++) {
		rxr = &rxq->vxrxq_cmd_ring[i];
		rxr->vxrxr_gen = 0;
		bzero(rxr->vxrxr_rxd,
		    rxr->vxrxr_ndesc * sizeof(struct vmxnet3_rxdesc));
	}

	rxc = &rxq->vxrxq_comp_ring;
	rxc->vxcr_next = 0;
	rxc->vxcr_gen = VMXNET3_INIT_GEN;
	/*
	 * iflib has zeroed out the descriptor array during the prior attach
	 * or stop
	 */
}