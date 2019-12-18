#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_ring_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_ring_size; } ;
struct fe_priv {TYPE_2__ tx_ring; TYPE_1__ rx_ring; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; void* tx_max_pending; void* rx_max_pending; } ;

/* Variables and functions */
 void* MAX_DMA_DESC ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void fe_get_ringparam(struct net_device *dev,
			     struct ethtool_ringparam *ring)
{
	struct fe_priv *priv = netdev_priv(dev);

	ring->rx_max_pending = MAX_DMA_DESC;
	ring->tx_max_pending = MAX_DMA_DESC;
	ring->rx_pending = priv->rx_ring.rx_ring_size;
	ring->tx_pending = priv->tx_ring.tx_ring_size;
}