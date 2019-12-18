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
typedef  union e1000_rx_desc_extended {int dummy; } e1000_rx_desc_extended ;
typedef  int /*<<< orphan*/  uint64_t ;
struct rx_ring {int me; int /*<<< orphan*/  rx_paddr; union e1000_rx_desc_extended* rx_base; struct em_rx_queue* que; struct adapter* adapter; } ;
struct em_rx_queue {int me; struct adapter* adapter; struct rx_ring rxr; } ;
struct adapter {int rx_num_queues; struct em_rx_queue* rx_queues; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int E1000_SUCCESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  em_if_queues_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
em_if_rx_queues_alloc(if_ctx_t ctx, caddr_t *vaddrs, uint64_t *paddrs, int nrxqs, int nrxqsets)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	int error = E1000_SUCCESS;
	struct em_rx_queue *que;
	int i;

	MPASS(adapter->rx_num_queues > 0);
	MPASS(adapter->rx_num_queues == nrxqsets);

	/* First allocate the top level queue structs */
	if (!(adapter->rx_queues =
	    (struct em_rx_queue *) malloc(sizeof(struct em_rx_queue) *
	    adapter->rx_num_queues, M_DEVBUF, M_NOWAIT | M_ZERO))) {
		device_printf(iflib_get_dev(ctx), "Unable to allocate queue memory\n");
		error = ENOMEM;
		goto fail;
	}

	for (i = 0, que = adapter->rx_queues; i < nrxqsets; i++, que++) {
		/* Set up some basics */
		struct rx_ring *rxr = &que->rxr;
		rxr->adapter = que->adapter = adapter;
		rxr->que = que;
		que->me = rxr->me =  i;

		/* get the virtual and physical address of the hardware queues */
		rxr->rx_base = (union e1000_rx_desc_extended *)vaddrs[i*nrxqs];
		rxr->rx_paddr = paddrs[i*nrxqs];
	}
 
	if (bootverbose)
		device_printf(iflib_get_dev(ctx),
		    "allocated for %d rx_queues\n", adapter->rx_num_queues);

	return (0);
fail:
	em_if_queues_free(ctx);
	return (error);
}