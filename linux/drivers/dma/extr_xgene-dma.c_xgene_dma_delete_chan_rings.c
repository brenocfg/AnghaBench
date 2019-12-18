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
struct xgene_dma_chan {int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgene_dma_delete_ring_one (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgene_dma_delete_chan_rings(struct xgene_dma_chan *chan)
{
	xgene_dma_delete_ring_one(&chan->rx_ring);
	xgene_dma_delete_ring_one(&chan->tx_ring);
}