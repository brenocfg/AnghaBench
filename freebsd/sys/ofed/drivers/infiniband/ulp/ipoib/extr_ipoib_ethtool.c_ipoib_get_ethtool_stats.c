#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_4__ {int aggregated; int flushed; int no_desc; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;
struct TYPE_6__ {TYPE_2__ lro_mgr; } ;
struct ipoib_dev_priv {TYPE_3__ lro; } ;
struct ifnet {struct ipoib_dev_priv* if_softc; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void ipoib_get_ethtool_stats(struct ifnet *dev,
				struct ethtool_stats *stats, uint64_t *data)
{
	struct ipoib_dev_priv *priv = dev->if_softc;
	int index = 0;

	/* Get LRO statistics */
	data[index++] = priv->lro.lro_mgr.stats.aggregated;
	data[index++] = priv->lro.lro_mgr.stats.flushed;
	if (priv->lro.lro_mgr.stats.flushed)
		data[index++] = priv->lro.lro_mgr.stats.aggregated /
				priv->lro.lro_mgr.stats.flushed;
	else
		data[index++] = 0;
	data[index++] = priv->lro.lro_mgr.stats.no_desc;
}