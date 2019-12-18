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
struct hsu_dma_chip {TYPE_2__* hsu; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct hsu_dma_chan {TYPE_1__ vchan; } ;
struct TYPE_4__ {unsigned short nr_channels; struct hsu_dma_chan* chan; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  HSU_CH_SR ; 
 int HSU_CH_SR_CDESC_ANY ; 
 int HSU_CH_SR_DESCE_ANY ; 
 int HSU_CH_SR_DESCTO_ANY ; 
 int hsu_chan_readl (struct hsu_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

int hsu_dma_get_status(struct hsu_dma_chip *chip, unsigned short nr,
		       u32 *status)
{
	struct hsu_dma_chan *hsuc;
	unsigned long flags;
	u32 sr;

	/* Sanity check */
	if (nr >= chip->hsu->nr_channels)
		return -EINVAL;

	hsuc = &chip->hsu->chan[nr];

	/*
	 * No matter what situation, need read clear the IRQ status
	 * There is a bug, see Errata 5, HSD 2900918
	 */
	spin_lock_irqsave(&hsuc->vchan.lock, flags);
	sr = hsu_chan_readl(hsuc, HSU_CH_SR);
	spin_unlock_irqrestore(&hsuc->vchan.lock, flags);

	/* Check if any interrupt is pending */
	sr &= ~(HSU_CH_SR_DESCE_ANY | HSU_CH_SR_CDESC_ANY);
	if (!sr)
		return -EIO;

	/* Timeout IRQ, need wait some time, see Errata 2 */
	if (sr & HSU_CH_SR_DESCTO_ANY)
		udelay(2);

	/*
	 * At this point, at least one of Descriptor Time Out, Channel Error
	 * or Descriptor Done bits must be set. Clear the Descriptor Time Out
	 * bits and if sr is still non-zero, it must be channel error or
	 * descriptor done which are higher priority than timeout and handled
	 * in hsu_dma_do_irq(). Else, it must be a timeout.
	 */
	sr &= ~HSU_CH_SR_DESCTO_ANY;

	*status = sr;

	return sr ? 0 : 1;
}