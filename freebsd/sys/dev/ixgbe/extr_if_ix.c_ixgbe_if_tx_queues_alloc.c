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
typedef  union ixgbe_adv_tx_desc {int dummy; } ixgbe_adv_tx_desc ;
typedef  int /*<<< orphan*/  uint64_t ;
struct tx_ring {int /*<<< orphan*/  atr_sample; scalar_t__ total_packets; scalar_t__ bytes; int /*<<< orphan*/  tx_paddr; union ixgbe_adv_tx_desc* tx_base; int /*<<< orphan*/  me; int /*<<< orphan*/  tail; int /*<<< orphan*/ * tx_rsq; struct adapter* adapter; } ;
struct ix_tx_queue {struct adapter* adapter; struct tx_ring txr; } ;
struct adapter {int num_tx_queues; int feat_en; int /*<<< orphan*/  pool; int /*<<< orphan*/  iov_mode; struct ix_tx_queue* tx_queues; TYPE_1__* shared; } ;
typedef  int /*<<< orphan*/  qidx_t ;
typedef  TYPE_1__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int* isc_ntxd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IXGBE_FEATURE_FDIR ; 
 int /*<<< orphan*/  IXGBE_TDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_IXGBE ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  QIDX_INVALID ; 
 int /*<<< orphan*/  atr_sample_rate ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_if_queues_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_vf_que_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ixgbe_if_tx_queues_alloc(if_ctx_t ctx, caddr_t *vaddrs, uint64_t *paddrs,
                         int ntxqs, int ntxqsets)
{
	struct adapter     *adapter = iflib_get_softc(ctx);
	if_softc_ctx_t     scctx = adapter->shared;
	struct ix_tx_queue *que;
	int                i, j, error;

	MPASS(adapter->num_tx_queues > 0);
	MPASS(adapter->num_tx_queues == ntxqsets);
	MPASS(ntxqs == 1);

	/* Allocate queue structure memory */
	adapter->tx_queues =
	    (struct ix_tx_queue *)malloc(sizeof(struct ix_tx_queue) * ntxqsets,
	                                 M_IXGBE, M_NOWAIT | M_ZERO);
	if (!adapter->tx_queues) {
		device_printf(iflib_get_dev(ctx),
		    "Unable to allocate TX ring memory\n");
		return (ENOMEM);
	}

	for (i = 0, que = adapter->tx_queues; i < ntxqsets; i++, que++) {
		struct tx_ring *txr = &que->txr;

		/* In case SR-IOV is enabled, align the index properly */
		txr->me = ixgbe_vf_que_index(adapter->iov_mode, adapter->pool,
		    i);

		txr->adapter = que->adapter = adapter;

		/* Allocate report status array */
		txr->tx_rsq = (qidx_t *)malloc(sizeof(qidx_t) * scctx->isc_ntxd[0], M_IXGBE, M_NOWAIT | M_ZERO);
		if (txr->tx_rsq == NULL) {
			error = ENOMEM;
			goto fail;
		}
		for (j = 0; j < scctx->isc_ntxd[0]; j++)
			txr->tx_rsq[j] = QIDX_INVALID;
		/* get the virtual and physical address of the hardware queues */
		txr->tail = IXGBE_TDT(txr->me);
		txr->tx_base = (union ixgbe_adv_tx_desc *)vaddrs[i];
		txr->tx_paddr = paddrs[i];

		txr->bytes = 0;
		txr->total_packets = 0;

		/* Set the rate at which we sample packets */
		if (adapter->feat_en & IXGBE_FEATURE_FDIR)
			txr->atr_sample = atr_sample_rate;

	}

	device_printf(iflib_get_dev(ctx), "allocated for %d queues\n",
	    adapter->num_tx_queues);

	return (0);

fail:
	ixgbe_if_queues_free(ctx);

	return (error);
}