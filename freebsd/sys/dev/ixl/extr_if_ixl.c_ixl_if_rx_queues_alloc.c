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
typedef  union i40e_rx_desc {int dummy; } i40e_rx_desc ;
typedef  int /*<<< orphan*/  uint64_t ;
struct rx_ring {int me; struct ixl_rx_queue* que; int /*<<< orphan*/  rx_paddr; union i40e_rx_desc* rx_base; int /*<<< orphan*/  tail; } ;
struct ixl_vsi {struct ixl_rx_queue* rx_queues; TYPE_1__* shared; } ;
struct ixl_rx_queue {struct ixl_vsi* vsi; struct rx_ring rxr; } ;
struct ixl_pf {struct ixl_vsi vsi; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int isc_nrxqsets; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  I40E_QRX_TAIL (int) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_IXL ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_if_queues_free (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ixl_if_rx_queues_alloc(if_ctx_t ctx, caddr_t *vaddrs, uint64_t *paddrs, int nrxqs, int nrxqsets)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &pf->vsi;
	struct ixl_rx_queue *que;
	int i, error = 0;

#ifdef INVARIANTS
	if_softc_ctx_t scctx = vsi->shared;
	MPASS(scctx->isc_nrxqsets > 0);
	MPASS(nrxqs == 1);
	MPASS(scctx->isc_nrxqsets == nrxqsets);
#endif

	/* Allocate queue structure memory */
	if (!(vsi->rx_queues =
	    (struct ixl_rx_queue *) malloc(sizeof(struct ixl_rx_queue) *
	    nrxqsets, M_IXL, M_NOWAIT | M_ZERO))) {
		device_printf(iflib_get_dev(ctx), "Unable to allocate RX ring memory\n");
		error = ENOMEM;
		goto fail;
	}

	for (i = 0, que = vsi->rx_queues; i < nrxqsets; i++, que++) {
		struct rx_ring *rxr = &que->rxr;

		rxr->me = i;
		que->vsi = vsi;

		/* get the virtual and physical address of the hardware queues */
		rxr->tail = I40E_QRX_TAIL(rxr->me);
		rxr->rx_base = (union i40e_rx_desc *)vaddrs[i * nrxqs];
		rxr->rx_paddr = paddrs[i * nrxqs];
		rxr->que = que;
	}

	return (0);
fail:
	ixl_if_queues_free(ctx);
	return (error);
}