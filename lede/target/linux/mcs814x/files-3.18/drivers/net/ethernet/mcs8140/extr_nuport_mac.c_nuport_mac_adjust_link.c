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
struct phy_device {scalar_t__ link; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct nuport_mac_priv {scalar_t__ old_link; int /*<<< orphan*/  old_duplex; struct phy_device* phydev; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CTRL_REG ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nuport_mac_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuport_mac_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void nuport_mac_adjust_link(struct net_device *dev)
{
	struct nuport_mac_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = priv->phydev;
	unsigned int status_changed = 0;
	u32 reg;

	BUG_ON(!phydev);

	if (priv->old_link != phydev->link) {
		status_changed = 1;
		priv->old_link = phydev->link;
	}

	if (phydev->link && (priv->old_duplex != phydev->duplex)) {
		reg = nuport_mac_readl(CTRL_REG);
		if (phydev->duplex == DUPLEX_FULL)
			reg |= DUPLEX_FULL;
		else
			reg &= ~DUPLEX_FULL;
		nuport_mac_writel(reg, CTRL_REG);

		status_changed = 1;
		priv->old_duplex = phydev->duplex;
	}

	if (!status_changed)
		return;

	pr_info("%s: link %s", dev->name, phydev->link ?
		"UP" : "DOWN");
	if (phydev->link) {
		pr_cont(" - %d/%s", phydev->speed,
		phydev->duplex == DUPLEX_FULL ? "full" : "half");
	}
	pr_cont("\n");
}