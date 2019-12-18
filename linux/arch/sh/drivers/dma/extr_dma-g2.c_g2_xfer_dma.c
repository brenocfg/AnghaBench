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
struct dma_channel {unsigned int chan; int sar; int dar; int count; int mode; } ;
struct TYPE_4__ {TYPE_1__* channel; } ;
struct TYPE_3__ {int g2_addr; int root_addr; int size; int direction; int ctrl; int /*<<< orphan*/  xfer_enable; int /*<<< orphan*/  chan_enable; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  flush_icache_range (unsigned long,int) ; 
 int /*<<< orphan*/  g2_disable_dma (struct dma_channel*) ; 
 TYPE_2__* g2_dma ; 
 int /*<<< orphan*/  g2_enable_dma (struct dma_channel*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static int g2_xfer_dma(struct dma_channel *chan)
{
	unsigned int chan_nr = chan->chan;

	if (chan->sar & 31) {
		printk("g2dma: unaligned source 0x%lx\n", chan->sar);
		return -EINVAL;
	}

	if (chan->dar & 31) {
		printk("g2dma: unaligned dest 0x%lx\n", chan->dar);
		return -EINVAL;
	}

	/* Align the count */
	if (chan->count & 31)
		chan->count = (chan->count + (32 - 1)) & ~(32 - 1);

	/* Fixup destination */
	chan->dar += 0xa0800000;

	/* Fixup direction */
	chan->mode = !chan->mode;

	flush_icache_range((unsigned long)chan->sar, chan->count);

	g2_disable_dma(chan);

	g2_dma->channel[chan_nr].g2_addr   = chan->dar & 0x1fffffe0;
	g2_dma->channel[chan_nr].root_addr = chan->sar & 0x1fffffe0;
	g2_dma->channel[chan_nr].size	   = (chan->count & ~31) | 0x80000000;
	g2_dma->channel[chan_nr].direction = chan->mode;

	/*
	 * bit 0 - ???
	 * bit 1 - if set, generate a hardware event on transfer completion
	 * bit 2 - ??? something to do with suspend?
	 */
	g2_dma->channel[chan_nr].ctrl	= 5; /* ?? */

	g2_enable_dma(chan);

	/* debug cruft */
	pr_debug("count, sar, dar, mode, ctrl, chan, xfer: %ld, 0x%08lx, "
		 "0x%08lx, %ld, %ld, %ld, %ld\n",
		 g2_dma->channel[chan_nr].size,
		 g2_dma->channel[chan_nr].root_addr,
		 g2_dma->channel[chan_nr].g2_addr,
		 g2_dma->channel[chan_nr].direction,
		 g2_dma->channel[chan_nr].ctrl,
		 g2_dma->channel[chan_nr].chan_enable,
		 g2_dma->channel[chan_nr].xfer_enable);

	return 0;
}