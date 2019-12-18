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
struct net_device {TYPE_1__* ethtool_ops; } ;
struct fe_soc_data {scalar_t__* reg_table; } ;
struct fe_priv {struct fe_soc_data* soc; } ;
struct TYPE_2__ {int /*<<< orphan*/  get_ethtool_stats; int /*<<< orphan*/  get_sset_count; int /*<<< orphan*/  get_strings; } ;

/* Variables and functions */
 size_t FE_REG_FE_COUNTER_BASE ; 
 TYPE_1__ fe_ethtool_ops ; 
 int /*<<< orphan*/  fe_get_ethtool_stats ; 
 int /*<<< orphan*/  fe_get_sset_count ; 
 int /*<<< orphan*/  fe_get_strings ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 

void fe_set_ethtool_ops(struct net_device *netdev)
{
	struct fe_priv *priv = netdev_priv(netdev);
	struct fe_soc_data *soc = priv->soc;

	if (soc->reg_table[FE_REG_FE_COUNTER_BASE]) {
		fe_ethtool_ops.get_strings = fe_get_strings;
		fe_ethtool_ops.get_sset_count = fe_get_sset_count;
		fe_ethtool_ops.get_ethtool_stats = fe_get_ethtool_stats;
	}

	netdev->ethtool_ops = &fe_ethtool_ops;
}