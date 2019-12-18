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
struct stm32_dma_device {int dummy; } ;
struct stm32_dma_chan {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32_DMA_HIFCR ; 
 int /*<<< orphan*/  STM32_DMA_LIFCR ; 
 int STM32_DMA_MASKI ; 
 struct stm32_dma_device* stm32_dma_get_dev (struct stm32_dma_chan*) ; 
 int /*<<< orphan*/  stm32_dma_write (struct stm32_dma_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stm32_dma_irq_clear(struct stm32_dma_chan *chan, u32 flags)
{
	struct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	u32 dma_ifcr;

	/*
	 * Write "flags" to the DMA_xIFCR register corresponding to the selected
	 * DMA channel at the correct bit offset inside that register.
	 *
	 * If (ch % 4) is 2 or 3, left shift the mask by 16 bits.
	 * If (ch % 4) is 1 or 3, additionally left shift the mask by 6 bits.
	 */
	flags &= STM32_DMA_MASKI;
	dma_ifcr = flags << (((chan->id & 2) << 3) | ((chan->id & 1) * 6));

	if (chan->id & 4)
		stm32_dma_write(dmadev, STM32_DMA_HIFCR, dma_ifcr);
	else
		stm32_dma_write(dmadev, STM32_DMA_LIFCR, dma_ifcr);
}