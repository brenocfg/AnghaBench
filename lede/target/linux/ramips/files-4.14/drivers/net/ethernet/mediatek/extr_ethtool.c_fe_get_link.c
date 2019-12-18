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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct fe_priv {scalar_t__ phy_flags; TYPE_1__* phy_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 scalar_t__ FE_PHY_FLAG_ATTACH ; 
 int /*<<< orphan*/  ethtool_op_get_link (struct net_device*) ; 
 int genphy_update_link (TYPE_1__*) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 fe_get_link(struct net_device *dev)
{
	struct fe_priv *priv = netdev_priv(dev);
	int err;

	if (!priv->phy_dev)
		goto out_get_link;

	if (priv->phy_flags == FE_PHY_FLAG_ATTACH) {
		err = genphy_update_link(priv->phy_dev);
		if (err)
			goto out_get_link;
	}

	return priv->phy_dev->link;

out_get_link:
	return ethtool_op_get_link(dev);
}