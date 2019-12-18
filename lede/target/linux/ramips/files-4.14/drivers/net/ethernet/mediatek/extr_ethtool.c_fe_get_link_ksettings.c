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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct fe_priv {scalar_t__ phy_flags; int /*<<< orphan*/  phy_dev; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ FE_PHY_FLAG_ATTACH ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_get (int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 
 scalar_t__ phy_read_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fe_get_link_ksettings(struct net_device *ndev,
			   struct ethtool_link_ksettings *cmd)
{
	struct fe_priv *priv = netdev_priv(ndev);

	if (!priv->phy_dev)
		return -ENODEV;

	if (priv->phy_flags == FE_PHY_FLAG_ATTACH) {
		if (phy_read_status(priv->phy_dev))
			return -ENODEV;
	}

	phy_ethtool_ksettings_get(ndev->phydev, cmd);

	return 0;
}