#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy_device {int /*<<< orphan*/  addr; TYPE_2__* drv; int /*<<< orphan*/  supported; int /*<<< orphan*/  advertising; } ;
struct nuport_mac_priv {int old_link; int /*<<< orphan*/  ephy_clk; TYPE_1__* pdev; int /*<<< orphan*/  old_duplex; struct phy_device* phydev; int /*<<< orphan*/  phy_interface; int /*<<< orphan*/  phy_node; int /*<<< orphan*/  mii_bus; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  PHY_BASIC_FEATURES ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nuport_mac_adjust_link ; 
 struct phy_device* of_phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nuport_mac_mii_probe(struct net_device *dev)
{
	struct nuport_mac_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = NULL;
	int ret;

	ret = clk_enable(priv->ephy_clk);
	if (ret) {
		netdev_err(dev, "unable to enable ePHY clk\n");
		return ret;
	}

	phydev = phy_find_first(priv->mii_bus);
	if (!phydev) {
		netdev_err(dev, "no PHYs found\n");
		ret = -ENODEV;
		goto out;
	}

	phydev = of_phy_connect(dev, priv->phy_node,
			nuport_mac_adjust_link, 0,
			priv->phy_interface);
	if (IS_ERR(phydev)) {
		netdev_err(dev, "could not attach PHY\n");
		ret = PTR_ERR(phydev);
		goto out;
	}

	phydev->supported &= PHY_BASIC_FEATURES;
	phydev->advertising = phydev->supported;
	priv->phydev = phydev;
	priv->old_link = 1;
	priv->old_duplex = DUPLEX_FULL;

	dev_info(&priv->pdev->dev, "attached PHY driver [%s] "
		"(mii_bus:phy_addr=%d)\n",
		phydev->drv->name, phydev->addr);

	return 0;

out:
	/* disable the Ethernet PHY clock for the moment */
	clk_disable(priv->ephy_clk);

	return ret;
}