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
struct TYPE_2__ {struct netfront_rxq* sring; } ;
struct netfront_rxq {int id; TYPE_1__ ring; int /*<<< orphan*/  gref_head; int /*<<< orphan*/  rx_refill; void* ring_ref; void** grant_ref; int /*<<< orphan*/ ** mbufs; int /*<<< orphan*/  name; int /*<<< orphan*/  lock; struct netfront_info* info; } ;
struct netfront_info {struct netfront_rxq* rxq; } ;
typedef  int /*<<< orphan*/  netif_rx_sring_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FRONT_RING_INIT (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 void* GRANT_REF_INVALID ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NET_RX_RING_SIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SHARED_RING_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XN_QUEUE_NAME_LEN ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  destroy_rxq (struct netfront_rxq*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disconnect_rxq (struct netfront_rxq*) ; 
 int /*<<< orphan*/  free (struct netfront_rxq*,int /*<<< orphan*/ ) ; 
 scalar_t__ gnttab_alloc_grant_references (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_free_grant_references (int /*<<< orphan*/ ) ; 
 struct netfront_rxq* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  virt_to_mfn (int /*<<< orphan*/ *) ; 
 int xenbus_grant_ring (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static int
setup_rxqs(device_t dev, struct netfront_info *info,
	   unsigned long num_queues)
{
	int q, i;
	int error;
	netif_rx_sring_t *rxs;
	struct netfront_rxq *rxq;

	info->rxq = malloc(sizeof(struct netfront_rxq) * num_queues,
	    M_DEVBUF, M_WAITOK|M_ZERO);

	for (q = 0; q < num_queues; q++) {
		rxq = &info->rxq[q];

		rxq->id = q;
		rxq->info = info;
		rxq->ring_ref = GRANT_REF_INVALID;
		rxq->ring.sring = NULL;
		snprintf(rxq->name, XN_QUEUE_NAME_LEN, "xnrx_%u", q);
		mtx_init(&rxq->lock, rxq->name, "netfront receive lock",
		    MTX_DEF);

		for (i = 0; i <= NET_RX_RING_SIZE; i++) {
			rxq->mbufs[i] = NULL;
			rxq->grant_ref[i] = GRANT_REF_INVALID;
		}

		/* Start resources allocation */

		if (gnttab_alloc_grant_references(NET_RX_RING_SIZE,
		    &rxq->gref_head) != 0) {
			device_printf(dev, "allocating rx gref");
			error = ENOMEM;
			goto fail;
		}

		rxs = (netif_rx_sring_t *)malloc(PAGE_SIZE, M_DEVBUF,
		    M_WAITOK|M_ZERO);
		SHARED_RING_INIT(rxs);
		FRONT_RING_INIT(&rxq->ring, rxs, PAGE_SIZE);

		error = xenbus_grant_ring(dev, virt_to_mfn(rxs),
		    &rxq->ring_ref);
		if (error != 0) {
			device_printf(dev, "granting rx ring page");
			goto fail_grant_ring;
		}

		callout_init(&rxq->rx_refill, 1);
	}

	return (0);

fail_grant_ring:
	gnttab_free_grant_references(rxq->gref_head);
	free(rxq->ring.sring, M_DEVBUF);
fail:
	for (; q >= 0; q--) {
		disconnect_rxq(&info->rxq[q]);
		destroy_rxq(&info->rxq[q]);
	}

	free(info->rxq, M_DEVBUF);
	return (error);
}