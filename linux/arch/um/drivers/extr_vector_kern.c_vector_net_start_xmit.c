#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tx_kicks; } ;
struct vector_private {scalar_t__ rx_irq; scalar_t__ tx_irq; int options; int /*<<< orphan*/  tx_poll; TYPE_3__* tx_queue; TYPE_2__ estats; int /*<<< orphan*/  coalesce; int /*<<< orphan*/  tl; int /*<<< orphan*/  dev; TYPE_1__* fds; scalar_t__ in_error; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {int max_depth; } ;
struct TYPE_5__ {scalar_t__ rx_fd; scalar_t__ tx_fd; } ;

/* Variables and functions */
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  TX_SMALL_PACKET ; 
 int VECTOR_TX ; 
 int /*<<< orphan*/  deactivate_fd (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vector_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_sent_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netdev_xmit_more () ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int vector_enqueue (TYPE_3__*,struct sk_buff*) ; 
 int /*<<< orphan*/  vector_send (TYPE_3__*) ; 
 int /*<<< orphan*/  writev_tx (struct vector_private*,struct sk_buff*) ; 

__attribute__((used)) static int vector_net_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct vector_private *vp = netdev_priv(dev);
	int queue_depth = 0;

	if (vp->in_error) {
		deactivate_fd(vp->fds->rx_fd, vp->rx_irq);
		if ((vp->fds->rx_fd != vp->fds->tx_fd) && (vp->tx_irq != 0))
			deactivate_fd(vp->fds->tx_fd, vp->tx_irq);
		return NETDEV_TX_BUSY;
	}

	if ((vp->options & VECTOR_TX) == 0) {
		writev_tx(vp, skb);
		return NETDEV_TX_OK;
	}

	/* We do BQL only in the vector path, no point doing it in
	 * packet at a time mode as there is no device queue
	 */

	netdev_sent_queue(vp->dev, skb->len);
	queue_depth = vector_enqueue(vp->tx_queue, skb);

	/* if the device queue is full, stop the upper layers and
	 * flush it.
	 */

	if (queue_depth >= vp->tx_queue->max_depth - 1) {
		vp->estats.tx_kicks++;
		netif_stop_queue(dev);
		vector_send(vp->tx_queue);
		return NETDEV_TX_OK;
	}
	if (netdev_xmit_more()) {
		mod_timer(&vp->tl, vp->coalesce);
		return NETDEV_TX_OK;
	}
	if (skb->len < TX_SMALL_PACKET) {
		vp->estats.tx_kicks++;
		vector_send(vp->tx_queue);
	} else
		tasklet_schedule(&vp->tx_poll);
	return NETDEV_TX_OK;
}