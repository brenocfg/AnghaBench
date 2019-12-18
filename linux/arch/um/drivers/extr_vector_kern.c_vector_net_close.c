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
struct vector_private {scalar_t__ rx_irq; scalar_t__ tx_irq; int opened; int in_error; int /*<<< orphan*/  lock; TYPE_1__* fds; int /*<<< orphan*/ * tx_queue; int /*<<< orphan*/ * rx_queue; TYPE_1__* header_txbuffer; TYPE_1__* header_rxbuffer; TYPE_1__* transport_data; TYPE_1__* bpf; int /*<<< orphan*/  tx_poll; int /*<<< orphan*/  tl; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int rx_fd; int tx_fd; struct TYPE_2__* remote_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 struct vector_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  os_close_file (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  um_free_irq (scalar_t__,struct net_device*) ; 

__attribute__((used)) static int vector_net_close(struct net_device *dev)
{
	struct vector_private *vp = netdev_priv(dev);
	unsigned long flags;

	netif_stop_queue(dev);
	del_timer(&vp->tl);

	if (vp->fds == NULL)
		return 0;

	/* Disable and free all IRQS */
	if (vp->rx_irq > 0) {
		um_free_irq(vp->rx_irq, dev);
		vp->rx_irq = 0;
	}
	if (vp->tx_irq > 0) {
		um_free_irq(vp->tx_irq, dev);
		vp->tx_irq = 0;
	}
	tasklet_kill(&vp->tx_poll);
	if (vp->fds->rx_fd > 0) {
		os_close_file(vp->fds->rx_fd);
		vp->fds->rx_fd = -1;
	}
	if (vp->fds->tx_fd > 0) {
		os_close_file(vp->fds->tx_fd);
		vp->fds->tx_fd = -1;
	}
	kfree(vp->bpf);
	kfree(vp->fds->remote_addr);
	kfree(vp->transport_data);
	kfree(vp->header_rxbuffer);
	kfree(vp->header_txbuffer);
	if (vp->rx_queue != NULL)
		destroy_queue(vp->rx_queue);
	if (vp->tx_queue != NULL)
		destroy_queue(vp->tx_queue);
	kfree(vp->fds);
	vp->fds = NULL;
	spin_lock_irqsave(&vp->lock, flags);
	vp->opened = false;
	vp->in_error = false;
	spin_unlock_irqrestore(&vp->lock, flags);
	return 0;
}