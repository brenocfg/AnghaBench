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
struct nuport_mac_priv {int first_pkt; scalar_t__* valid_txskb; int /*<<< orphan*/ ** tx_skb; scalar_t__ tx_full; scalar_t__ dma_tx; scalar_t__ cur_tx; } ;

/* Variables and functions */
 int TX_RING_SIZE ; 

__attribute__((used)) static void nuport_mac_init_tx_ring(struct nuport_mac_priv *priv)
{
	int i;

	priv->cur_tx = priv->dma_tx = priv->tx_full = 0;
	for (i = 0; i < TX_RING_SIZE; i++) {
		priv->tx_skb[i] = NULL;
		priv->valid_txskb[i] = 0;
	}
	priv->first_pkt = 1;
}