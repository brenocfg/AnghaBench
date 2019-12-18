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
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
typedef  int /*<<< orphan*/  uint64_t ;
struct rx_ring {struct ix_rx_queue* que; scalar_t__ bytes; int /*<<< orphan*/  rx_paddr; union ixgbe_adv_rx_desc* rx_base; int /*<<< orphan*/  me; int /*<<< orphan*/  tail; struct adapter* adapter; } ;
struct ix_rx_queue {struct adapter* adapter; struct rx_ring rxr; } ;
struct adapter {int num_rx_queues; int /*<<< orphan*/  pool; int /*<<< orphan*/  iov_mode; struct ix_rx_queue* rx_queues; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IXGBE_RDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_IXGBE ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_vf_que_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ixgbe_if_rx_queues_alloc(if_ctx_t ctx, caddr_t *vaddrs, uint64_t *paddrs,
                         int nrxqs, int nrxqsets)
{
	struct adapter     *adapter = iflib_get_softc(ctx);
	struct ix_rx_queue *que;
	int                i;

	MPASS(adapter->num_rx_queues > 0);
	MPASS(adapter->num_rx_queues == nrxqsets);
	MPASS(nrxqs == 1);

	/* Allocate queue structure memory */
	adapter->rx_queues =
	    (struct ix_rx_queue *)malloc(sizeof(struct ix_rx_queue)*nrxqsets,
	                                 M_IXGBE, M_NOWAIT | M_ZERO);
	if (!adapter->rx_queues) {
		device_printf(iflib_get_dev(ctx),
		    "Unable to allocate TX ring memory\n");
		return (ENOMEM);
	}

	for (i = 0, que = adapter->rx_queues; i < nrxqsets; i++, que++) {
		struct rx_ring *rxr = &que->rxr;

		/* In case SR-IOV is enabled, align the index properly */
		rxr->me = ixgbe_vf_que_index(adapter->iov_mode, adapter->pool,
		    i);

		rxr->adapter = que->adapter = adapter;

		/* get the virtual and physical address of the hw queues */
		rxr->tail = IXGBE_RDT(rxr->me);
		rxr->rx_base = (union ixgbe_adv_rx_desc *)vaddrs[i];
		rxr->rx_paddr = paddrs[i];
		rxr->bytes = 0;
		rxr->que = que;
	}

	device_printf(iflib_get_dev(ctx), "allocated for %d rx queues\n",
	    adapter->num_rx_queues);

	return (0);
}