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
struct stm32_mdma_device {int dummy; } ;
struct stm32_mdma_chan {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32_MDMA_CBNDTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_MDMA_CBRUR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_MDMA_CCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_MDMA_CDAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_MDMA_CLAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_MDMA_CMAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_MDMA_CMDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_MDMA_CSAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_MDMA_CTBR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_MDMA_CTCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan2dev (struct stm32_mdma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct stm32_mdma_device* stm32_mdma_get_dev (struct stm32_mdma_chan*) ; 
 int /*<<< orphan*/  stm32_mdma_read (struct stm32_mdma_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_mdma_dump_reg(struct stm32_mdma_chan *chan)
{
	struct stm32_mdma_device *dmadev = stm32_mdma_get_dev(chan);

	dev_dbg(chan2dev(chan), "CCR:     0x%08x\n",
		stm32_mdma_read(dmadev, STM32_MDMA_CCR(chan->id)));
	dev_dbg(chan2dev(chan), "CTCR:    0x%08x\n",
		stm32_mdma_read(dmadev, STM32_MDMA_CTCR(chan->id)));
	dev_dbg(chan2dev(chan), "CBNDTR:  0x%08x\n",
		stm32_mdma_read(dmadev, STM32_MDMA_CBNDTR(chan->id)));
	dev_dbg(chan2dev(chan), "CSAR:    0x%08x\n",
		stm32_mdma_read(dmadev, STM32_MDMA_CSAR(chan->id)));
	dev_dbg(chan2dev(chan), "CDAR:    0x%08x\n",
		stm32_mdma_read(dmadev, STM32_MDMA_CDAR(chan->id)));
	dev_dbg(chan2dev(chan), "CBRUR:   0x%08x\n",
		stm32_mdma_read(dmadev, STM32_MDMA_CBRUR(chan->id)));
	dev_dbg(chan2dev(chan), "CLAR:    0x%08x\n",
		stm32_mdma_read(dmadev, STM32_MDMA_CLAR(chan->id)));
	dev_dbg(chan2dev(chan), "CTBR:    0x%08x\n",
		stm32_mdma_read(dmadev, STM32_MDMA_CTBR(chan->id)));
	dev_dbg(chan2dev(chan), "CMAR:    0x%08x\n",
		stm32_mdma_read(dmadev, STM32_MDMA_CMAR(chan->id)));
	dev_dbg(chan2dev(chan), "CMDR:    0x%08x\n",
		stm32_mdma_read(dmadev, STM32_MDMA_CMDR(chan->id)));
}