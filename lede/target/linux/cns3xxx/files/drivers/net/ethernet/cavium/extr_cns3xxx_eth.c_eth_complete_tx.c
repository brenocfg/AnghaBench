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
struct tx_desc {int /*<<< orphan*/  sdl; int /*<<< orphan*/  cown; } ;
struct _tx_ring {int num_used; int free_index; struct tx_desc* desc; int /*<<< orphan*/ * phys_tab; struct sk_buff** buff_tab; } ;
struct sw {int /*<<< orphan*/  dev; struct _tx_ring tx_ring; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int TX_DESCS ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_check_num_used (struct _tx_ring*) ; 

__attribute__((used)) static void eth_complete_tx(struct sw *sw)
{
	struct _tx_ring *tx_ring = &sw->tx_ring;
	struct tx_desc *desc;
	int i;
	int index;
	int num_used = tx_ring->num_used;
	struct sk_buff *skb;

	index = tx_ring->free_index;
	desc = &(tx_ring)->desc[index];

	for (i = 0; i < num_used; i++) {
		if (!desc->cown)
			break;

		skb = tx_ring->buff_tab[index];
		tx_ring->buff_tab[index] = 0;

		if (skb)
			dev_kfree_skb_any(skb);

		dma_unmap_single(sw->dev, tx_ring->phys_tab[index], desc->sdl, DMA_TO_DEVICE);

		if (index == TX_DESCS - 1) {
			index = 0;
			desc = &(tx_ring)->desc[index];
		} else {
			index++;
			desc++;
		}
	}

	tx_ring->free_index = index;
	tx_ring->num_used -= i;
	eth_check_num_used(tx_ring);
}