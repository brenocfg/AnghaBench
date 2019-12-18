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
struct fe_tx_ring {int tx_ring_size; int /*<<< orphan*/ * tx_dma; int /*<<< orphan*/  tx_phys; int /*<<< orphan*/ * tx_buf; } ;
struct fe_priv {TYPE_1__* netdev; struct fe_tx_ring tx_ring; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_txd_unmap (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_reset_queue (TYPE_1__*) ; 

__attribute__((used)) static void fe_clean_tx(struct fe_priv *priv)
{
	int i;
	struct device *dev = &priv->netdev->dev;
	struct fe_tx_ring *ring = &priv->tx_ring;

	if (ring->tx_buf) {
		for (i = 0; i < ring->tx_ring_size; i++)
			fe_txd_unmap(dev, &ring->tx_buf[i]);
		kfree(ring->tx_buf);
		ring->tx_buf = NULL;
	}

	if (ring->tx_dma) {
		dma_free_coherent(dev,
				  ring->tx_ring_size * sizeof(*ring->tx_dma),
				  ring->tx_dma,
				  ring->tx_phys);
		ring->tx_dma = NULL;
	}

	netdev_reset_queue(priv->netdev);
}