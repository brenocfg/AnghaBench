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
typedef  scalar_t__ u_long ;
struct TYPE_2__ {struct netfront_txq* sring; } ;
struct netfront_txq {int id; TYPE_1__ ring; int /*<<< orphan*/  gref_head; void* ring_ref; int /*<<< orphan*/  tq; int /*<<< orphan*/  br; int /*<<< orphan*/  xen_intr_handle; int /*<<< orphan*/  name; int /*<<< orphan*/  defrtask; int /*<<< orphan*/  lock; void** mbufs; void** grant_ref; struct netfront_info* info; } ;
struct netfront_info {struct netfront_txq* txq; } ;
typedef  int /*<<< orphan*/  netif_tx_sring_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FRONT_RING_INIT (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 void* GRANT_REF_INVALID ; 
 int INTR_ENTROPY ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NET_TX_RING_SIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  SHARED_RING_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netfront_txq*) ; 
 int /*<<< orphan*/  XN_QUEUE_NAME_LEN ; 
 int /*<<< orphan*/  buf_ring_alloc (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_ring_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_txq (struct netfront_txq*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  disconnect_txq (struct netfront_txq*) ; 
 int /*<<< orphan*/  free (struct netfront_txq*,int /*<<< orphan*/ ) ; 
 scalar_t__ gnttab_alloc_grant_references (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_free_grant_references (int /*<<< orphan*/ ) ; 
 struct netfront_txq* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  taskqueue_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 
 int taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int /*<<< orphan*/  virt_to_mfn (int /*<<< orphan*/ *) ; 
 int xen_intr_alloc_and_bind_local_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netfront_txq*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_get_otherend_id (int /*<<< orphan*/ ) ; 
 int xenbus_grant_ring (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  xn_intr ; 
 int /*<<< orphan*/  xn_txq_tq_deferred ; 

__attribute__((used)) static int
setup_txqs(device_t dev, struct netfront_info *info,
	   unsigned long num_queues)
{
	int q, i;
	int error;
	netif_tx_sring_t *txs;
	struct netfront_txq *txq;

	info->txq = malloc(sizeof(struct netfront_txq) * num_queues,
	    M_DEVBUF, M_WAITOK|M_ZERO);

	for (q = 0; q < num_queues; q++) {
		txq = &info->txq[q];

		txq->id = q;
		txq->info = info;

		txq->ring_ref = GRANT_REF_INVALID;
		txq->ring.sring = NULL;

		snprintf(txq->name, XN_QUEUE_NAME_LEN, "xntx_%u", q);

		mtx_init(&txq->lock, txq->name, "netfront transmit lock",
		    MTX_DEF);

		for (i = 0; i <= NET_TX_RING_SIZE; i++) {
			txq->mbufs[i] = (void *) ((u_long) i+1);
			txq->grant_ref[i] = GRANT_REF_INVALID;
		}
		txq->mbufs[NET_TX_RING_SIZE] = (void *)0;

		/* Start resources allocation. */

		if (gnttab_alloc_grant_references(NET_TX_RING_SIZE,
		    &txq->gref_head) != 0) {
			device_printf(dev, "failed to allocate tx grant refs\n");
			error = ENOMEM;
			goto fail;
		}

		txs = (netif_tx_sring_t *)malloc(PAGE_SIZE, M_DEVBUF,
		    M_WAITOK|M_ZERO);
		SHARED_RING_INIT(txs);
		FRONT_RING_INIT(&txq->ring, txs, PAGE_SIZE);

		error = xenbus_grant_ring(dev, virt_to_mfn(txs),
		    &txq->ring_ref);
		if (error != 0) {
			device_printf(dev, "failed to grant tx ring\n");
			goto fail_grant_ring;
		}

		txq->br = buf_ring_alloc(NET_TX_RING_SIZE, M_DEVBUF,
		    M_WAITOK, &txq->lock);
		TASK_INIT(&txq->defrtask, 0, xn_txq_tq_deferred, txq);

		txq->tq = taskqueue_create(txq->name, M_WAITOK,
		    taskqueue_thread_enqueue, &txq->tq);

		error = taskqueue_start_threads(&txq->tq, 1, PI_NET,
		    "%s txq %d", device_get_nameunit(dev), txq->id);
		if (error != 0) {
			device_printf(dev, "failed to start tx taskq %d\n",
			    txq->id);
			goto fail_start_thread;
		}

		error = xen_intr_alloc_and_bind_local_port(dev,
		    xenbus_get_otherend_id(dev), /* filter */ NULL, xn_intr,
		    &info->txq[q], INTR_TYPE_NET | INTR_MPSAFE | INTR_ENTROPY,
		    &txq->xen_intr_handle);

		if (error != 0) {
			device_printf(dev, "xen_intr_alloc_and_bind_local_port failed\n");
			goto fail_bind_port;
		}
	}

	return (0);

fail_bind_port:
	taskqueue_drain_all(txq->tq);
fail_start_thread:
	buf_ring_free(txq->br, M_DEVBUF);
	taskqueue_free(txq->tq);
	gnttab_end_foreign_access(txq->ring_ref, NULL);
fail_grant_ring:
	gnttab_free_grant_references(txq->gref_head);
	free(txq->ring.sring, M_DEVBUF);
fail:
	for (; q >= 0; q--) {
		disconnect_txq(&info->txq[q]);
		destroy_txq(&info->txq[q]);
	}

	free(info->txq, M_DEVBUF);
	return (error);
}