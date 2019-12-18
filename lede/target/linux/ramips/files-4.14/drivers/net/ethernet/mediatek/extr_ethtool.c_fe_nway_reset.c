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
struct fe_priv {int /*<<< orphan*/  phy_dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int genphy_restart_aneg (int /*<<< orphan*/ ) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int fe_nway_reset(struct net_device *dev)
{
	struct fe_priv *priv = netdev_priv(dev);

	if (!priv->phy_dev)
		goto out_nway_reset;

	return genphy_restart_aneg(priv->phy_dev);

out_nway_reset:
	return -EOPNOTSUPP;
}