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
struct nuport_mac_priv {TYPE_1__* pdev; } ;
struct net_device {void** dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MAC_ADDR_HIGH_REG ; 
 scalar_t__ MAC_ADDR_LOW_REG ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (void**) ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 void* nuport_mac_readb (scalar_t__) ; 
 int /*<<< orphan*/  random_ether_addr (void**) ; 

__attribute__((used)) static void nuport_mac_read_mac_address(struct net_device *dev)
{
	struct nuport_mac_priv *priv = netdev_priv(dev);
	int i;

	for (i = 0; i < 4; i++)
		dev->dev_addr[i] = nuport_mac_readb(MAC_ADDR_LOW_REG + i);
	dev->dev_addr[4] = nuport_mac_readb(MAC_ADDR_HIGH_REG);
	dev->dev_addr[5] = nuport_mac_readb(MAC_ADDR_HIGH_REG + 1);

	if (!is_valid_ether_addr(dev->dev_addr)) {
		dev_info(&priv->pdev->dev, "using random address\n");
		random_ether_addr(dev->dev_addr);
	}
}