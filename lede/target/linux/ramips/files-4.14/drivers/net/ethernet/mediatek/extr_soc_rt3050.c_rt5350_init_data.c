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
struct net_device {int hw_features; } ;
struct fe_soc_data {int dummy; } ;
struct fe_priv {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_FLAG_HAS_SWITCH ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void rt5350_init_data(struct fe_soc_data *data,
			     struct net_device *netdev)
{
	struct fe_priv *priv = netdev_priv(netdev);

	priv->flags = FE_FLAG_HAS_SWITCH;
	netdev->hw_features = NETIF_F_SG | NETIF_F_RXCSUM;
}