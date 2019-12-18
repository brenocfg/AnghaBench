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
struct net_device {int dummy; } ;
struct ag71xx {int /*<<< orphan*/  lock; scalar_t__ link; int /*<<< orphan*/  phy_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ag71xx_hw_disable (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_link_adjust (struct ag71xx*) ; 
 struct ag71xx* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ag71xx_stop(struct net_device *dev)
{
	unsigned long flags;
	struct ag71xx *ag = netdev_priv(dev);

	netif_carrier_off(dev);
	phy_stop(ag->phy_dev);

	spin_lock_irqsave(&ag->lock, flags);
	if (ag->link) {
		ag->link = 0;
		ag71xx_link_adjust(ag);
	}
	spin_unlock_irqrestore(&ag->lock, flags);

	ag71xx_hw_disable(ag);

	return 0;
}