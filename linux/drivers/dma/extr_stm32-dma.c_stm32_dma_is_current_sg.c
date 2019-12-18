#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int dma_sm0ar; int dma_sm1ar; } ;
struct stm32_dma_sg_req {TYPE_2__ chan_reg; } ;
struct stm32_dma_device {int dummy; } ;
struct stm32_dma_chan {int id; size_t next_sg; TYPE_1__* desc; } ;
struct TYPE_3__ {struct stm32_dma_sg_req* sg_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32_DMA_SCR (int) ; 
 int STM32_DMA_SCR_CT ; 
 int STM32_DMA_SCR_DBM ; 
 int /*<<< orphan*/  STM32_DMA_SM0AR (int) ; 
 int /*<<< orphan*/  STM32_DMA_SM1AR (int) ; 
 struct stm32_dma_device* stm32_dma_get_dev (struct stm32_dma_chan*) ; 
 int stm32_dma_read (struct stm32_dma_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool stm32_dma_is_current_sg(struct stm32_dma_chan *chan)
{
	struct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	struct stm32_dma_sg_req *sg_req;
	u32 dma_scr, dma_smar, id;

	id = chan->id;
	dma_scr = stm32_dma_read(dmadev, STM32_DMA_SCR(id));

	if (!(dma_scr & STM32_DMA_SCR_DBM))
		return true;

	sg_req = &chan->desc->sg_req[chan->next_sg];

	if (dma_scr & STM32_DMA_SCR_CT) {
		dma_smar = stm32_dma_read(dmadev, STM32_DMA_SM0AR(id));
		return (dma_smar == sg_req->chan_reg.dma_sm0ar);
	}

	dma_smar = stm32_dma_read(dmadev, STM32_DMA_SM1AR(id));

	return (dma_smar == sg_req->chan_reg.dma_sm1ar);
}