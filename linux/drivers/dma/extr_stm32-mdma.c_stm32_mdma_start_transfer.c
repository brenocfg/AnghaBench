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
typedef  scalar_t__ u32 ;
struct virt_dma_desc {int dummy; } ;
struct stm32_mdma_hwdesc {int ctcr; int cbndtr; int csar; int cdar; int cbrur; int clar; int ctbr; int cmar; int cmdr; } ;
struct stm32_mdma_device {int dummy; } ;
struct stm32_mdma_chan {int busy; int /*<<< orphan*/  vchan; TYPE_2__* desc; scalar_t__ curr_hwdesc; scalar_t__ id; } ;
struct TYPE_4__ {int ccr; TYPE_1__* node; } ;
struct TYPE_3__ {struct stm32_mdma_hwdesc* hwdesc; } ;

/* Variables and functions */
 scalar_t__ STM32_MDMA_CBNDTR (scalar_t__) ; 
 scalar_t__ STM32_MDMA_CBRUR (scalar_t__) ; 
 scalar_t__ STM32_MDMA_CCR (scalar_t__) ; 
 scalar_t__ STM32_MDMA_CCR_EN ; 
 scalar_t__ STM32_MDMA_CCR_SWRQ ; 
 scalar_t__ STM32_MDMA_CDAR (scalar_t__) ; 
 scalar_t__ STM32_MDMA_CIFCR (scalar_t__) ; 
 int /*<<< orphan*/  STM32_MDMA_CISR (scalar_t__) ; 
 scalar_t__ STM32_MDMA_CLAR (scalar_t__) ; 
 scalar_t__ STM32_MDMA_CMAR (scalar_t__) ; 
 scalar_t__ STM32_MDMA_CMDR (scalar_t__) ; 
 scalar_t__ STM32_MDMA_CSAR (scalar_t__) ; 
 scalar_t__ STM32_MDMA_CTBR (scalar_t__) ; 
 scalar_t__ STM32_MDMA_CTCR (scalar_t__) ; 
 int STM32_MDMA_CTCR_SWRM ; 
 int /*<<< orphan*/  chan2dev (struct stm32_mdma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_mdma_dump_reg (struct stm32_mdma_chan*) ; 
 struct stm32_mdma_device* stm32_mdma_get_dev (struct stm32_mdma_chan*) ; 
 scalar_t__ stm32_mdma_read (struct stm32_mdma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_mdma_set_bits (struct stm32_mdma_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stm32_mdma_write (struct stm32_mdma_device*,scalar_t__,int) ; 
 TYPE_2__* to_stm32_mdma_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stm32_mdma_start_transfer(struct stm32_mdma_chan *chan)
{
	struct stm32_mdma_device *dmadev = stm32_mdma_get_dev(chan);
	struct virt_dma_desc *vdesc;
	struct stm32_mdma_hwdesc *hwdesc;
	u32 id = chan->id;
	u32 status, reg;

	vdesc = vchan_next_desc(&chan->vchan);
	if (!vdesc) {
		chan->desc = NULL;
		return;
	}

	chan->desc = to_stm32_mdma_desc(vdesc);
	hwdesc = chan->desc->node[0].hwdesc;
	chan->curr_hwdesc = 0;

	stm32_mdma_write(dmadev, STM32_MDMA_CCR(id), chan->desc->ccr);
	stm32_mdma_write(dmadev, STM32_MDMA_CTCR(id), hwdesc->ctcr);
	stm32_mdma_write(dmadev, STM32_MDMA_CBNDTR(id), hwdesc->cbndtr);
	stm32_mdma_write(dmadev, STM32_MDMA_CSAR(id), hwdesc->csar);
	stm32_mdma_write(dmadev, STM32_MDMA_CDAR(id), hwdesc->cdar);
	stm32_mdma_write(dmadev, STM32_MDMA_CBRUR(id), hwdesc->cbrur);
	stm32_mdma_write(dmadev, STM32_MDMA_CLAR(id), hwdesc->clar);
	stm32_mdma_write(dmadev, STM32_MDMA_CTBR(id), hwdesc->ctbr);
	stm32_mdma_write(dmadev, STM32_MDMA_CMAR(id), hwdesc->cmar);
	stm32_mdma_write(dmadev, STM32_MDMA_CMDR(id), hwdesc->cmdr);

	/* Clear interrupt status if it is there */
	status = stm32_mdma_read(dmadev, STM32_MDMA_CISR(id));
	if (status)
		stm32_mdma_set_bits(dmadev, STM32_MDMA_CIFCR(id), status);

	stm32_mdma_dump_reg(chan);

	/* Start DMA */
	stm32_mdma_set_bits(dmadev, STM32_MDMA_CCR(id), STM32_MDMA_CCR_EN);

	/* Set SW request in case of MEM2MEM transfer */
	if (hwdesc->ctcr & STM32_MDMA_CTCR_SWRM) {
		reg = STM32_MDMA_CCR(id);
		stm32_mdma_set_bits(dmadev, reg, STM32_MDMA_CCR_SWRQ);
	}

	chan->busy = true;

	dev_dbg(chan2dev(chan), "vchan %pK: started\n", &chan->vchan);
}