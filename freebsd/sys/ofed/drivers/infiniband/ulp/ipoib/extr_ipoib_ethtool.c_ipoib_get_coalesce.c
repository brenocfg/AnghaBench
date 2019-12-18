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
struct TYPE_2__ {int /*<<< orphan*/  max_coalesced_frames; int /*<<< orphan*/  coalesce_usecs; } ;
struct ipoib_dev_priv {TYPE_1__ ethtool; } ;
struct ifnet {struct ipoib_dev_priv* if_softc; } ;
struct ethtool_coalesce {int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  rx_coalesce_usecs; } ;

/* Variables and functions */

__attribute__((used)) static int ipoib_get_coalesce(struct ifnet *dev,
			      struct ethtool_coalesce *coal)
{
	struct ipoib_dev_priv *priv = dev->if_softc;

	coal->rx_coalesce_usecs = priv->ethtool.coalesce_usecs;
	coal->tx_coalesce_usecs = priv->ethtool.coalesce_usecs;
	coal->rx_max_coalesced_frames = priv->ethtool.max_coalesced_frames;
	coal->tx_max_coalesced_frames = priv->ethtool.max_coalesced_frames;

	return 0;
}