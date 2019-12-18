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
struct vector_private {int /*<<< orphan*/  tx_poll; scalar_t__ in_write_poll; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 struct vector_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t vector_tx_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct vector_private *vp = netdev_priv(dev);

	if (!netif_running(dev))
		return IRQ_NONE;
	/* We need to pay attention to it only if we got
	 * -EAGAIN or -ENOBUFFS from sendmmsg. Otherwise
	 * we ignore it. In the future, it may be worth
	 * it to improve the IRQ controller a bit to make
	 * tweaking the IRQ mask less costly
	 */

	if (vp->in_write_poll)
		tasklet_schedule(&vp->tx_poll);
	return IRQ_HANDLED;

}