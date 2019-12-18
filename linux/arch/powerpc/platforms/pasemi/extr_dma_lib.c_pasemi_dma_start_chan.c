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
struct pasemi_dmachan {scalar_t__ chan_type; int /*<<< orphan*/  chno; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAS_DMA_RXCHAN_CCMDSTA (int /*<<< orphan*/ ) ; 
 int const PAS_DMA_RXCHAN_CCMDSTA_EN ; 
 int /*<<< orphan*/  PAS_DMA_TXCHAN_TCMDSTA (int /*<<< orphan*/ ) ; 
 int const PAS_DMA_TXCHAN_TCMDSTA_EN ; 
 scalar_t__ RXCHAN ; 
 int /*<<< orphan*/  pasemi_write_dma_reg (int /*<<< orphan*/ ,int const) ; 

void pasemi_dma_start_chan(const struct pasemi_dmachan *chan, const u32 cmdsta)
{
	if (chan->chan_type == RXCHAN)
		pasemi_write_dma_reg(PAS_DMA_RXCHAN_CCMDSTA(chan->chno),
				     cmdsta | PAS_DMA_RXCHAN_CCMDSTA_EN);
	else
		pasemi_write_dma_reg(PAS_DMA_TXCHAN_TCMDSTA(chan->chno),
				     cmdsta | PAS_DMA_TXCHAN_TCMDSTA_EN);
}