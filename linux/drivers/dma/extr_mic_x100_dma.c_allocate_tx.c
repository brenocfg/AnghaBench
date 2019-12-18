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
typedef  size_t u32 ;
struct mic_dma_chan {int /*<<< orphan*/  api_ch; struct dma_async_tx_descriptor* tx_array; int /*<<< orphan*/  head; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  tx_submit; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_tx_descriptor_init (struct dma_async_tx_descriptor*,int /*<<< orphan*/ *) ; 
 size_t mic_dma_hw_ring_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mic_dma_tx_submit_unlock ; 

__attribute__((used)) static inline struct dma_async_tx_descriptor *
allocate_tx(struct mic_dma_chan *ch)
{
	u32 idx = mic_dma_hw_ring_dec(ch->head);
	struct dma_async_tx_descriptor *tx = &ch->tx_array[idx];

	dma_async_tx_descriptor_init(tx, &ch->api_ch);
	tx->tx_submit = mic_dma_tx_submit_unlock;
	return tx;
}