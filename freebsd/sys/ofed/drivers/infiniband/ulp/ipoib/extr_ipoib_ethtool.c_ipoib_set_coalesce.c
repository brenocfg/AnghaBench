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
struct TYPE_2__ {int coalesce_usecs; int max_coalesced_frames; } ;
struct ipoib_dev_priv {TYPE_1__ ethtool; int /*<<< orphan*/  recv_cq; } ;
struct ifnet {struct ipoib_dev_priv* if_softc; } ;
struct ethtool_coalesce {int rx_coalesce_usecs; int rx_max_coalesced_frames; int tx_coalesce_usecs; int tx_max_coalesced_frames; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int ib_modify_cq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 

__attribute__((used)) static int ipoib_set_coalesce(struct ifnet *dev,
			      struct ethtool_coalesce *coal)
{
	struct ipoib_dev_priv *priv = dev->if_softc;
	int ret;

	/*
	 * Since IPoIB uses a single CQ for both rx and tx, we assume
	 * that rx params dictate the configuration.  These values are
	 * saved in the private data and returned when ipoib_get_coalesce()
	 * is called.
	 */
	if (coal->rx_coalesce_usecs       > 0xffff ||
	    coal->rx_max_coalesced_frames > 0xffff)
		return -EINVAL;

	if (coal->rx_max_coalesced_frames | coal->rx_coalesce_usecs) {
		if (!coal->rx_max_coalesced_frames)
			coal->rx_max_coalesced_frames = 0xffff;
		else if (!coal->rx_coalesce_usecs)
			coal->rx_coalesce_usecs = 0xffff;
	}

	ret = ib_modify_cq(priv->recv_cq, coal->rx_max_coalesced_frames,
			   coal->rx_coalesce_usecs);
	if (ret && ret != -ENOSYS) {
		ipoib_warn(priv, "failed modifying CQ (%d)\n", ret);
		return ret;
	}

	coal->tx_coalesce_usecs       = coal->rx_coalesce_usecs;
	coal->tx_max_coalesced_frames = coal->rx_max_coalesced_frames;
	priv->ethtool.coalesce_usecs       = coal->rx_coalesce_usecs;
	priv->ethtool.max_coalesced_frames = coal->rx_max_coalesced_frames;

	return 0;
}