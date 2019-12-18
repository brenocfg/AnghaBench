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
struct vmxnet3_txring {void* vxtxr_gen; scalar_t__ vxtxr_next; } ;
struct vmxnet3_comp_ring {void* vxcr_gen; scalar_t__ vxcr_next; } ;
struct vmxnet3_txqueue {int vxtxq_last_flush; struct vmxnet3_comp_ring vxtxq_comp_ring; struct vmxnet3_txring vxtxq_cmd_ring; } ;
struct vmxnet3_softc {int dummy; } ;

/* Variables and functions */
 void* VMXNET3_INIT_GEN ; 

__attribute__((used)) static void
vmxnet3_txinit(struct vmxnet3_softc *sc, struct vmxnet3_txqueue *txq)
{
	struct vmxnet3_txring *txr;
	struct vmxnet3_comp_ring *txc;

	txq->vxtxq_last_flush = -1;
	
	txr = &txq->vxtxq_cmd_ring;
	txr->vxtxr_next = 0;
	txr->vxtxr_gen = VMXNET3_INIT_GEN;
	/*
	 * iflib has zeroed out the descriptor array during the prior attach
	 * or stop
	 */

	txc = &txq->vxtxq_comp_ring;
	txc->vxcr_next = 0;
	txc->vxcr_gen = VMXNET3_INIT_GEN;
	/*
	 * iflib has zeroed out the descriptor array during the prior attach
	 * or stop
	 */
}