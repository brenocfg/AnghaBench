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
struct stm32_mdma_device {scalar_t__ base; struct stm32_mdma_chan* chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct stm32_mdma_chan {int id; TYPE_2__ vchan; TYPE_1__* desc; int /*<<< orphan*/  curr_hwdesc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  vdesc; int /*<<< orphan*/  count; int /*<<< orphan*/  cyclic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  STM32_MDMA_CCR (int) ; 
 int STM32_MDMA_CCR_IRQ_MASK ; 
 scalar_t__ STM32_MDMA_CESR (int) ; 
 int STM32_MDMA_CIFCR (int) ; 
 int /*<<< orphan*/  STM32_MDMA_CIFCR_CBRTIF ; 
 int /*<<< orphan*/  STM32_MDMA_CIFCR_CBTIF ; 
 int /*<<< orphan*/  STM32_MDMA_CIFCR_CCTCIF ; 
 int /*<<< orphan*/  STM32_MDMA_CIFCR_CLTCIF ; 
 int /*<<< orphan*/  STM32_MDMA_CIFCR_CTEIF ; 
 int /*<<< orphan*/  STM32_MDMA_CISR (int) ; 
#define  STM32_MDMA_CISR_BRTIF 132 
#define  STM32_MDMA_CISR_BTIF 131 
#define  STM32_MDMA_CISR_CTCIF 130 
#define  STM32_MDMA_CISR_TCIF 129 
#define  STM32_MDMA_CISR_TEIF 128 
 scalar_t__ STM32_MDMA_GISR0 ; 
 scalar_t__ STM32_MDMA_GISR1 ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  chan2dev (struct stm32_mdma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mdma2dev (struct stm32_mdma_device*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stm32_mdma_read (struct stm32_mdma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_mdma_set_bits (struct stm32_mdma_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_mdma_xfer_end (struct stm32_mdma_chan*) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t stm32_mdma_irq_handler(int irq, void *devid)
{
	struct stm32_mdma_device *dmadev = devid;
	struct stm32_mdma_chan *chan = devid;
	u32 reg, id, ien, status, flag;

	/* Find out which channel generates the interrupt */
	status = readl_relaxed(dmadev->base + STM32_MDMA_GISR0);
	if (status) {
		id = __ffs(status);
	} else {
		status = readl_relaxed(dmadev->base + STM32_MDMA_GISR1);
		if (!status) {
			dev_dbg(mdma2dev(dmadev), "spurious it\n");
			return IRQ_NONE;
		}
		id = __ffs(status);
		/*
		 * As GISR0 provides status for channel id from 0 to 31,
		 * so GISR1 provides status for channel id from 32 to 62
		 */
		id += 32;
	}

	chan = &dmadev->chan[id];
	if (!chan) {
		dev_dbg(mdma2dev(dmadev), "MDMA channel not initialized\n");
		goto exit;
	}

	/* Handle interrupt for the channel */
	spin_lock(&chan->vchan.lock);
	status = stm32_mdma_read(dmadev, STM32_MDMA_CISR(chan->id));
	ien = stm32_mdma_read(dmadev, STM32_MDMA_CCR(chan->id));
	ien &= STM32_MDMA_CCR_IRQ_MASK;
	ien >>= 1;

	if (!(status & ien)) {
		spin_unlock(&chan->vchan.lock);
		dev_dbg(chan2dev(chan),
			"spurious it (status=0x%04x, ien=0x%04x)\n",
			status, ien);
		return IRQ_NONE;
	}

	flag = __ffs(status & ien);
	reg = STM32_MDMA_CIFCR(chan->id);

	switch (1 << flag) {
	case STM32_MDMA_CISR_TEIF:
		id = chan->id;
		status = readl_relaxed(dmadev->base + STM32_MDMA_CESR(id));
		dev_err(chan2dev(chan), "Transfer Err: stat=0x%08x\n", status);
		stm32_mdma_set_bits(dmadev, reg, STM32_MDMA_CIFCR_CTEIF);
		break;

	case STM32_MDMA_CISR_CTCIF:
		stm32_mdma_set_bits(dmadev, reg, STM32_MDMA_CIFCR_CCTCIF);
		stm32_mdma_xfer_end(chan);
		break;

	case STM32_MDMA_CISR_BRTIF:
		stm32_mdma_set_bits(dmadev, reg, STM32_MDMA_CIFCR_CBRTIF);
		break;

	case STM32_MDMA_CISR_BTIF:
		stm32_mdma_set_bits(dmadev, reg, STM32_MDMA_CIFCR_CBTIF);
		chan->curr_hwdesc++;
		if (chan->desc && chan->desc->cyclic) {
			if (chan->curr_hwdesc == chan->desc->count)
				chan->curr_hwdesc = 0;
			vchan_cyclic_callback(&chan->desc->vdesc);
		}
		break;

	case STM32_MDMA_CISR_TCIF:
		stm32_mdma_set_bits(dmadev, reg, STM32_MDMA_CIFCR_CLTCIF);
		break;

	default:
		dev_err(chan2dev(chan), "it %d unhandled (status=0x%04x)\n",
			1 << flag, status);
	}

	spin_unlock(&chan->vchan.lock);

exit:
	return IRQ_HANDLED;
}