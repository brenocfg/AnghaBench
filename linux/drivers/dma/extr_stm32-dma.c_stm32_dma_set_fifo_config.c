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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dma_sfcr; int /*<<< orphan*/  dma_scr; } ;
struct stm32_dma_chan {TYPE_1__ chan_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32_DMA_SCR_DMEIE ; 
 int /*<<< orphan*/  STM32_DMA_SFCR_MASK ; 

__attribute__((used)) static void stm32_dma_set_fifo_config(struct stm32_dma_chan *chan,
				      u32 src_burst, u32 dst_burst)
{
	chan->chan_reg.dma_sfcr &= ~STM32_DMA_SFCR_MASK;
	chan->chan_reg.dma_scr &= ~STM32_DMA_SCR_DMEIE;

	if (!src_burst && !dst_burst) {
		/* Using direct mode */
		chan->chan_reg.dma_scr |= STM32_DMA_SCR_DMEIE;
	} else {
		/* Using FIFO mode */
		chan->chan_reg.dma_sfcr |= STM32_DMA_SFCR_MASK;
	}
}