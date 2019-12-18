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
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
 int DMA_SLAVE_BUSWIDTH_UNDEFINED ; 
 int STM32_DMA_FIFO_SIZE ; 

__attribute__((used)) static bool stm32_dma_fifo_threshold_is_allowed(u32 burst, u32 threshold,
						enum dma_slave_buswidth width)
{
	u32 remaining;

	if (width != DMA_SLAVE_BUSWIDTH_UNDEFINED) {
		if (burst != 0) {
			/*
			 * If number of beats fit in several whole bursts
			 * this configuration is allowed.
			 */
			remaining = ((STM32_DMA_FIFO_SIZE / width) *
				     (threshold + 1) / 4) % burst;

			if (remaining == 0)
				return true;
		} else {
			return true;
		}
	}

	return false;
}