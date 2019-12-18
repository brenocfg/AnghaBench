#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sdma_engine {struct sdma_channel* channel; scalar_t__ regs; } ;
struct sdma_desc {int /*<<< orphan*/  vd; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct sdma_channel {int flags; TYPE_1__ vc; struct sdma_desc* desc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int IMX_DMA_SG_LOOP ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SDMA_H_INTR ; 
 int /*<<< orphan*/  __clear_bit (int,unsigned long*) ; 
 int fls (unsigned long) ; 
 int /*<<< orphan*/  mxc_sdma_handle_channel_normal (struct sdma_channel*) ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  sdma_start_desc (struct sdma_channel*) ; 
 int /*<<< orphan*/  sdma_update_channel_loop (struct sdma_channel*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cookie_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sdma_int_handler(int irq, void *dev_id)
{
	struct sdma_engine *sdma = dev_id;
	unsigned long stat;

	stat = readl_relaxed(sdma->regs + SDMA_H_INTR);
	writel_relaxed(stat, sdma->regs + SDMA_H_INTR);
	/* channel 0 is special and not handled here, see run_channel0() */
	stat &= ~1;

	while (stat) {
		int channel = fls(stat) - 1;
		struct sdma_channel *sdmac = &sdma->channel[channel];
		struct sdma_desc *desc;

		spin_lock(&sdmac->vc.lock);
		desc = sdmac->desc;
		if (desc) {
			if (sdmac->flags & IMX_DMA_SG_LOOP) {
				sdma_update_channel_loop(sdmac);
			} else {
				mxc_sdma_handle_channel_normal(sdmac);
				vchan_cookie_complete(&desc->vd);
				sdma_start_desc(sdmac);
			}
		}

		spin_unlock(&sdmac->vc.lock);
		__clear_bit(channel, &stat);
	}

	return IRQ_HANDLED;
}