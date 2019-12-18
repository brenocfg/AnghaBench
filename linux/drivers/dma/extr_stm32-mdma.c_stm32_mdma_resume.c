#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct stm32_mdma_hwdesc {int ctcr; } ;
struct stm32_mdma_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct stm32_mdma_chan {size_t curr_hwdesc; TYPE_3__ vchan; int /*<<< orphan*/  id; TYPE_2__* desc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ccr; TYPE_1__* node; } ;
struct TYPE_4__ {struct stm32_mdma_hwdesc* hwdesc; } ;

/* Variables and functions */
 scalar_t__ STM32_MDMA_CCR (int /*<<< orphan*/ ) ; 
 scalar_t__ STM32_MDMA_CCR_EN ; 
 scalar_t__ STM32_MDMA_CCR_SWRQ ; 
 scalar_t__ STM32_MDMA_CIFCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_MDMA_CISR (int /*<<< orphan*/ ) ; 
 int STM32_MDMA_CTCR_SWRM ; 
 int /*<<< orphan*/  chan2dev (struct stm32_mdma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stm32_mdma_dump_reg (struct stm32_mdma_chan*) ; 
 struct stm32_mdma_device* stm32_mdma_get_dev (struct stm32_mdma_chan*) ; 
 scalar_t__ stm32_mdma_read (struct stm32_mdma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_mdma_set_bits (struct stm32_mdma_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stm32_mdma_write (struct stm32_mdma_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct stm32_mdma_chan* to_stm32_mdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int stm32_mdma_resume(struct dma_chan *c)
{
	struct stm32_mdma_chan *chan = to_stm32_mdma_chan(c);
	struct stm32_mdma_device *dmadev = stm32_mdma_get_dev(chan);
	struct stm32_mdma_hwdesc *hwdesc;
	unsigned long flags;
	u32 status, reg;

	hwdesc = chan->desc->node[chan->curr_hwdesc].hwdesc;

	spin_lock_irqsave(&chan->vchan.lock, flags);

	/* Re-configure control register */
	stm32_mdma_write(dmadev, STM32_MDMA_CCR(chan->id), chan->desc->ccr);

	/* Clear interrupt status if it is there */
	status = stm32_mdma_read(dmadev, STM32_MDMA_CISR(chan->id));
	if (status)
		stm32_mdma_set_bits(dmadev, STM32_MDMA_CIFCR(chan->id), status);

	stm32_mdma_dump_reg(chan);

	/* Re-start DMA */
	reg = STM32_MDMA_CCR(chan->id);
	stm32_mdma_set_bits(dmadev, reg, STM32_MDMA_CCR_EN);

	/* Set SW request in case of MEM2MEM transfer */
	if (hwdesc->ctcr & STM32_MDMA_CTCR_SWRM)
		stm32_mdma_set_bits(dmadev, reg, STM32_MDMA_CCR_SWRQ);

	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	dev_dbg(chan2dev(chan), "vchan %pK: resume\n", &chan->vchan);

	return 0;
}