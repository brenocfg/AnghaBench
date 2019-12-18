#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct TYPE_4__ {TYPE_3__* ifp; int /*<<< orphan*/ * tx_free_queue; scalar_t__ fau; int /*<<< orphan*/  link_task; scalar_t__ need_link_update; } ;
typedef  TYPE_1__ cvm_oct_private_t ;
struct TYPE_6__ {int /*<<< orphan*/  if_drv_flags; } ;
struct TYPE_5__ {scalar_t__ if_softc; } ;

/* Variables and functions */
 int CVMX_PIP_NUM_INPUT_PORTS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ _IF_QLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvm_oct_common_poll (TYPE_3__*) ; 
 TYPE_2__** cvm_oct_device ; 
 int /*<<< orphan*/  cvm_oct_link_taskq ; 
 int /*<<< orphan*/  cvm_oct_poll_timer ; 
 scalar_t__ cvmx_fau_fetch_and_add32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int cvmx_pko_get_num_queues (int) ; 
 int hz ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cvm_do_timer(void *arg)
{
	static int port;
	static int updated;
	if (port < CVMX_PIP_NUM_INPUT_PORTS) {
		if (cvm_oct_device[port]) {
			int queues_per_port;
			int qos;
			cvm_oct_private_t *priv = (cvm_oct_private_t *)cvm_oct_device[port]->if_softc;

			cvm_oct_common_poll(priv->ifp);
			if (priv->need_link_update) {
				updated++;
				taskqueue_enqueue(cvm_oct_link_taskq, &priv->link_task);
			}

			queues_per_port = cvmx_pko_get_num_queues(port);
			/* Drain any pending packets in the free list */
			for (qos = 0; qos < queues_per_port; qos++) {
				if (_IF_QLEN(&priv->tx_free_queue[qos]) > 0) {
					IF_LOCK(&priv->tx_free_queue[qos]);
					while (_IF_QLEN(&priv->tx_free_queue[qos]) > cvmx_fau_fetch_and_add32(priv->fau+qos*4, 0)) {
						struct mbuf *m;

						_IF_DEQUEUE(&priv->tx_free_queue[qos], m);
						m_freem(m);
					}
					IF_UNLOCK(&priv->tx_free_queue[qos]);

					/*
					 * XXX locking!
					 */
					priv->ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
				}
			}
		}
		port++;
		/* Poll the next port in a 50th of a second.
		   This spreads the polling of ports out a little bit */
		callout_reset(&cvm_oct_poll_timer, hz / 50, cvm_do_timer, NULL);
	} else {
		port = 0;
		/* If any updates were made in this run, continue iterating at
		 * 1/50th of a second, so that if a link has merely gone down
		 * temporarily (e.g. because of interface reinitialization) it
		 * will not be forced to stay down for an entire second.
		 */
		if (updated > 0) {
			updated = 0;
			callout_reset(&cvm_oct_poll_timer, hz / 50, cvm_do_timer, NULL);
		} else {
			/* All ports have been polled. Start the next iteration through
			   the ports in one second */
			callout_reset(&cvm_oct_poll_timer, hz, cvm_do_timer, NULL);
		}
	}
}