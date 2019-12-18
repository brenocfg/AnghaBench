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
struct fsldma_device {int feature; int /*<<< orphan*/  dev; struct fsldma_chan** chan; int /*<<< orphan*/  regs; } ;
struct fsldma_chan {int id; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int FSL_DMA_BIG_ENDIAN ; 
 int FSL_DMA_MAX_CHANS_PER_DEVICE ; 
 int /*<<< orphan*/  IRQ_RETVAL (unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fsldma_chan_irq (int,struct fsldma_chan*) ; 
 int in_be32 (int /*<<< orphan*/ ) ; 
 int in_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t fsldma_ctrl_irq(int irq, void *data)
{
	struct fsldma_device *fdev = data;
	struct fsldma_chan *chan;
	unsigned int handled = 0;
	u32 gsr, mask;
	int i;

	gsr = (fdev->feature & FSL_DMA_BIG_ENDIAN) ? in_be32(fdev->regs)
						   : in_le32(fdev->regs);
	mask = 0xff000000;
	dev_dbg(fdev->dev, "IRQ: gsr 0x%.8x\n", gsr);

	for (i = 0; i < FSL_DMA_MAX_CHANS_PER_DEVICE; i++) {
		chan = fdev->chan[i];
		if (!chan)
			continue;

		if (gsr & mask) {
			dev_dbg(fdev->dev, "IRQ: chan %d\n", chan->id);
			fsldma_chan_irq(irq, chan);
			handled++;
		}

		gsr &= ~mask;
		mask >>= 8;
	}

	return IRQ_RETVAL(handled);
}