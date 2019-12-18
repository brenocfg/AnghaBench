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
 int MAX_RETRIES ; 
 int PAS_DMA_RXCHAN_CCMDSTA (int /*<<< orphan*/ ) ; 
 int PAS_DMA_RXCHAN_CCMDSTA_ACT ; 
 int /*<<< orphan*/  PAS_DMA_RXCHAN_CCMDSTA_ST ; 
 int PAS_DMA_TXCHAN_TCMDSTA (int /*<<< orphan*/ ) ; 
 int PAS_DMA_TXCHAN_TCMDSTA_ACT ; 
 int /*<<< orphan*/  PAS_DMA_TXCHAN_TCMDSTA_ST ; 
 scalar_t__ RXCHAN ; 
 int /*<<< orphan*/  cond_resched () ; 
 int pasemi_read_dma_reg (int) ; 
 int /*<<< orphan*/  pasemi_write_dma_reg (int,int /*<<< orphan*/ ) ; 

int pasemi_dma_stop_chan(const struct pasemi_dmachan *chan)
{
	int reg, retries;
	u32 sta;

	if (chan->chan_type == RXCHAN) {
		reg = PAS_DMA_RXCHAN_CCMDSTA(chan->chno);
		pasemi_write_dma_reg(reg, PAS_DMA_RXCHAN_CCMDSTA_ST);
		for (retries = 0; retries < MAX_RETRIES; retries++) {
			sta = pasemi_read_dma_reg(reg);
			if (!(sta & PAS_DMA_RXCHAN_CCMDSTA_ACT)) {
				pasemi_write_dma_reg(reg, 0);
				return 1;
			}
			cond_resched();
		}
	} else {
		reg = PAS_DMA_TXCHAN_TCMDSTA(chan->chno);
		pasemi_write_dma_reg(reg, PAS_DMA_TXCHAN_TCMDSTA_ST);
		for (retries = 0; retries < MAX_RETRIES; retries++) {
			sta = pasemi_read_dma_reg(reg);
			if (!(sta & PAS_DMA_TXCHAN_TCMDSTA_ACT)) {
				pasemi_write_dma_reg(reg, 0);
				return 1;
			}
			cond_resched();
		}
	}

	return 0;
}