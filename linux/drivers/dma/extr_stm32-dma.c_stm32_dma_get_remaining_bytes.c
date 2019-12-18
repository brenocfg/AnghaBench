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
struct stm32_dma_chan {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32_DMA_SCR (int /*<<< orphan*/ ) ; 
 int STM32_DMA_SCR_PSIZE_GET (int) ; 
 int /*<<< orphan*/  STM32_DMA_SNDTR (int /*<<< orphan*/ ) ; 
 struct stm32_dma_device* stm32_dma_get_dev (struct stm32_dma_chan*) ; 
 int stm32_dma_read (struct stm32_dma_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 stm32_dma_get_remaining_bytes(struct stm32_dma_chan *chan)
{
	u32 dma_scr, width, ndtr;
	struct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);

	dma_scr = stm32_dma_read(dmadev, STM32_DMA_SCR(chan->id));
	width = STM32_DMA_SCR_PSIZE_GET(dma_scr);
	ndtr = stm32_dma_read(dmadev, STM32_DMA_SNDTR(chan->id));

	return ndtr << width;
}