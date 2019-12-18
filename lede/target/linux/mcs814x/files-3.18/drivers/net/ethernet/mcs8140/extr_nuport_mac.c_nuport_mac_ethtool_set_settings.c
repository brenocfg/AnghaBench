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
struct nuport_mac_priv {scalar_t__ phydev; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 int phy_ethtool_sset (scalar_t__,struct ethtool_cmd*) ; 

__attribute__((used)) static int nuport_mac_ethtool_set_settings(struct net_device *dev,
					struct ethtool_cmd *cmd)
{
	struct nuport_mac_priv *priv = netdev_priv(dev);

	if (priv->phydev)
		return phy_ethtool_sset(priv->phydev, cmd);

	return -EINVAL;
}