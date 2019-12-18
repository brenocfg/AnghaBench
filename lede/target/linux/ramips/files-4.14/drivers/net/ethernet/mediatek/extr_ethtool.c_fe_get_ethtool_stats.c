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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct fe_priv {struct fe_hw_stats* hw_stats; } ;
struct fe_hw_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  stats_lock; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_gdma_str ; 
 int /*<<< orphan*/  fe_stats_update (struct fe_priv*) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_device_present (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void fe_get_ethtool_stats(struct net_device *dev,
				 struct ethtool_stats *stats, u64 *data)
{
	struct fe_priv *priv = netdev_priv(dev);
	struct fe_hw_stats *hwstats = priv->hw_stats;
	u64 *data_src, *data_dst;
	unsigned int start;
	int i;

	if (netif_running(dev) && netif_device_present(dev)) {
		if (spin_trylock(&hwstats->stats_lock)) {
			fe_stats_update(priv);
			spin_unlock(&hwstats->stats_lock);
		}
	}

	do {
		data_src = &hwstats->tx_bytes;
		data_dst = data;
		start = u64_stats_fetch_begin_irq(&hwstats->syncp);

		for (i = 0; i < ARRAY_SIZE(fe_gdma_str); i++)
			*data_dst++ = *data_src++;

	} while (u64_stats_fetch_retry_irq(&hwstats->syncp, start));
}