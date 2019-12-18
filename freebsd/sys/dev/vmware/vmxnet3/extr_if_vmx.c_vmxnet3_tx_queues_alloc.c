#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct vmxnet3_txring {void* vxtxr_paddr; struct vmxnet3_txdesc* vxtxr_txd; } ;
struct TYPE_4__ {struct vmxnet3_txcompdesc* txcd; } ;
struct vmxnet3_comp_ring {void* vxcr_paddr; TYPE_2__ vxcr_u; } ;
struct vmxnet3_txqueue {struct vmxnet3_txring vxtxq_cmd_ring; struct vmxnet3_comp_ring vxtxq_comp_ring; struct vmxnet3_txq_shared* vxtxq_ts; } ;
struct vmxnet3_txq_shared {int dummy; } ;
struct vmxnet3_txdesc {int dummy; } ;
struct vmxnet3_txcompdesc {int dummy; } ;
struct TYPE_3__ {scalar_t__ idi_size; scalar_t__ idi_vaddr; } ;
struct vmxnet3_softc {struct vmxnet3_txqueue* vmx_txq; TYPE_1__ vmx_qs_dma; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct vmxnet3_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 struct vmxnet3_txqueue* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmxnet3_init_txq (struct vmxnet3_softc*,int) ; 
 int vmxnet3_queues_shared_alloc (struct vmxnet3_softc*) ; 

__attribute__((used)) static int
vmxnet3_tx_queues_alloc(if_ctx_t ctx, caddr_t *vaddrs, uint64_t *paddrs,
    int ntxqs, int ntxqsets)
{
	struct vmxnet3_softc *sc;
	int q;
	int error;
	caddr_t kva;
	
	sc = iflib_get_softc(ctx);

	/* Allocate the array of transmit queues */
	sc->vmx_txq = malloc(sizeof(struct vmxnet3_txqueue) *
	    ntxqsets, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (sc->vmx_txq == NULL)
		return (ENOMEM);

	/* Initialize driver state for each transmit queue */
	for (q = 0; q < ntxqsets; q++)
		vmxnet3_init_txq(sc, q);

	/*
	 * Allocate queue state that is shared with the device.  This check
	 * and call is performed in both vmxnet3_tx_queues_alloc() and
	 * vmxnet3_rx_queues_alloc() so that we don't have to care which
	 * order iflib invokes those routines in.
	 */
	if (sc->vmx_qs_dma.idi_size == 0) {
		error = vmxnet3_queues_shared_alloc(sc);
		if (error)
			return (error);
	}

	kva = sc->vmx_qs_dma.idi_vaddr;
	for (q = 0; q < ntxqsets; q++) {
		sc->vmx_txq[q].vxtxq_ts = (struct vmxnet3_txq_shared *) kva;
		kva += sizeof(struct vmxnet3_txq_shared);
	}

	/* Record descriptor ring vaddrs and paddrs */
	for (q = 0; q < ntxqsets; q++) {
		struct vmxnet3_txqueue *txq;
		struct vmxnet3_txring *txr;
		struct vmxnet3_comp_ring *txc;

		txq = &sc->vmx_txq[q];
		txc = &txq->vxtxq_comp_ring;
		txr = &txq->vxtxq_cmd_ring;

		/* Completion ring */
		txc->vxcr_u.txcd =
		    (struct vmxnet3_txcompdesc *) vaddrs[q * ntxqs + 0];
		txc->vxcr_paddr = paddrs[q * ntxqs + 0];

		/* Command ring */
		txr->vxtxr_txd =
		    (struct vmxnet3_txdesc *) vaddrs[q * ntxqs + 1];
		txr->vxtxr_paddr = paddrs[q * ntxqs + 1];
	}

	return (0);
}