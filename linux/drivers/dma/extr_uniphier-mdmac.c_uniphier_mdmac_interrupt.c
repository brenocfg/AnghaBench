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
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_mdmac_desc {scalar_t__ sg_cur; scalar_t__ sg_len; int /*<<< orphan*/  vd; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct uniphier_mdmac_chan {TYPE_1__ vc; struct uniphier_mdmac_desc* md; scalar_t__ reg_ch_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ UNIPHIER_MDMAC_CH_IRQ_DET ; 
 scalar_t__ UNIPHIER_MDMAC_CH_IRQ_REQ ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uniphier_mdmac_handle (struct uniphier_mdmac_chan*,struct uniphier_mdmac_desc*) ; 
 struct uniphier_mdmac_desc* uniphier_mdmac_next_desc (struct uniphier_mdmac_chan*) ; 
 int /*<<< orphan*/  vchan_cookie_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t uniphier_mdmac_interrupt(int irq, void *dev_id)
{
	struct uniphier_mdmac_chan *mc = dev_id;
	struct uniphier_mdmac_desc *md;
	irqreturn_t ret = IRQ_HANDLED;
	u32 irq_stat;

	spin_lock(&mc->vc.lock);

	irq_stat = readl(mc->reg_ch_base + UNIPHIER_MDMAC_CH_IRQ_DET);

	/*
	 * Some channels share a single interrupt line. If the IRQ status is 0,
	 * this is probably triggered by a different channel.
	 */
	if (!irq_stat) {
		ret = IRQ_NONE;
		goto out;
	}

	/* write 1 to clear */
	writel(irq_stat, mc->reg_ch_base + UNIPHIER_MDMAC_CH_IRQ_REQ);

	/*
	 * UNIPHIER_MDMAC_CH_IRQ__DONE interrupt is asserted even when the DMA
	 * is aborted. To distinguish the normal completion and the abort,
	 * check mc->md. If it is NULL, we are aborting.
	 */
	md = mc->md;
	if (!md)
		goto out;

	md->sg_cur++;

	if (md->sg_cur >= md->sg_len) {
		vchan_cookie_complete(&md->vd);
		md = uniphier_mdmac_next_desc(mc);
		if (!md)
			goto out;
	}

	uniphier_mdmac_handle(mc, md);

out:
	spin_unlock(&mc->vc.lock);

	return ret;
}