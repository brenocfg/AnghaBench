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
typedef  int u32 ;
struct tx_desc {unsigned int sdp; int pmap; int config0; } ;
struct sw {int /*<<< orphan*/  dev; } ;
struct _tx_ring {unsigned int* phys_tab; struct tx_desc* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int END_OF_RING ; 
 int LAST_SEGMENT ; 
 int TX_DESCS ; 
 unsigned int dma_map_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void eth_set_desc(struct sw *sw, struct _tx_ring *tx_ring, int index,
			 int index_last, void *data, int len, u32 config0,
			 u32 pmap)
{
	struct tx_desc *tx_desc = &(tx_ring)->desc[index];
	unsigned int phys;

	phys = dma_map_single(sw->dev, data, len, DMA_TO_DEVICE);
	tx_desc->sdp = phys;
	tx_desc->pmap = pmap;
	tx_ring->phys_tab[index] = phys;

	config0 |= len;

	if (index == TX_DESCS - 1)
		config0 |= END_OF_RING;

	if (index == index_last)
		config0 |= LAST_SEGMENT;

	wmb();
	tx_desc->config0 = config0;
}