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
typedef  int u32 ;
struct sw {TYPE_1__* regs; } ;
struct port {int id; struct sw* sw; } ;
struct net_device {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_glob_cfg; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int PROMISC_OFFSET ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 
 struct port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void eth_rx_mode(struct net_device *dev)
{
	struct port *port = netdev_priv(dev);
	struct sw *sw = port->sw;
	u32 temp;

	temp = __raw_readl(&sw->regs->mac_glob_cfg);

	if (dev->flags & IFF_PROMISC) {
		if (port->id == 3)
			temp |= ((1 << 2) << PROMISC_OFFSET);
		else
			temp |= ((1 << port->id) << PROMISC_OFFSET);
	} else {
		if (port->id == 3)
			temp &= ~((1 << 2) << PROMISC_OFFSET);
		else
			temp &= ~((1 << port->id) << PROMISC_OFFSET);
	}
	__raw_writel(temp, &sw->regs->mac_glob_cfg);
}