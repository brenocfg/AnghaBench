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
struct ntb_net_queue {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_tq; int /*<<< orphan*/  queue_full; int /*<<< orphan*/  br; int /*<<< orphan*/  qp; } ;
struct ntb_net_ctx {int num_queues; struct ntb_net_queue* queues; int /*<<< orphan*/  media; int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  buf_ring_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct ntb_net_ctx* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ntb_net_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_transport_free_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_transport_link_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain_all (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ntb_net_detach(device_t dev)
{
	struct ntb_net_ctx *sc = device_get_softc(dev);
	struct ntb_net_queue *q;
	int i;

	for (i = 0; i < sc->num_queues; i++)
		ntb_transport_link_down(sc->queues[i].qp);
	ether_ifdetach(sc->ifp);
	if_free(sc->ifp);
	ifmedia_removeall(&sc->media);
	for (i = 0; i < sc->num_queues; i++) {
		q = &sc->queues[i];
		ntb_transport_free_queue(q->qp);
		buf_ring_free(q->br, M_DEVBUF);
		callout_drain(&q->queue_full);
		taskqueue_drain_all(q->tx_tq);
		mtx_destroy(&q->tx_lock);
	}
	free(sc->queues, M_DEVBUF);
	return (0);
}