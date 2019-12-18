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
typedef  int /*<<< orphan*/  u32 ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct nuport_mac_priv {int /*<<< orphan*/  lock; } ;
struct net_device {scalar_t__ dev_addr; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MAC_ADDR_HIGH_REG ; 
 int /*<<< orphan*/  MAC_ADDR_LOW_REG ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  nuport_mac_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuport_mac_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nuport_mac_change_mac_address(struct net_device *dev, void *mac_addr)
{
	struct sockaddr *addr = mac_addr;
	struct nuport_mac_priv *priv = netdev_priv(dev);
	unsigned long *temp = (unsigned long *)dev->dev_addr;
	u32 high, low;

	if (netif_running(dev))
		return -EBUSY;

	memcpy(dev->dev_addr, addr->sa_data, ETH_ALEN);

	spin_lock_irq(&priv->lock);

	nuport_mac_writel(*temp, MAC_ADDR_LOW_REG);
	temp = (unsigned long *)(dev->dev_addr + 4);
	nuport_mac_writel(*temp, MAC_ADDR_HIGH_REG);

	low = nuport_mac_readl(MAC_ADDR_LOW_REG);
	high = nuport_mac_readl(MAC_ADDR_HIGH_REG);

	spin_unlock_irq(&priv->lock);

	return 0;
}