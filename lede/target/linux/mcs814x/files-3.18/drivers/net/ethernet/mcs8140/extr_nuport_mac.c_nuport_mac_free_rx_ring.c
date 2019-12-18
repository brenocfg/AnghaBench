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
struct nuport_mac_priv {scalar_t__ rx_addr; TYPE_1__* pdev; int /*<<< orphan*/ ** rx_skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  RX_ALLOC_SIZE ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nuport_mac_free_rx_ring(struct nuport_mac_priv *priv)
{
	int i;

	for (i = 0; i < RX_RING_SIZE; i++) {
		if (!priv->rx_skb[i])
			continue;

		dev_kfree_skb(priv->rx_skb[i]);
		priv->rx_skb[i] = NULL;
	}

	if (priv->rx_addr)
		dma_unmap_single(&priv->pdev->dev, priv->rx_addr, RX_ALLOC_SIZE,
				DMA_TO_DEVICE);
}