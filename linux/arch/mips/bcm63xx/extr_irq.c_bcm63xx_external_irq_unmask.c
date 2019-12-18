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
typedef  int /*<<< orphan*/  u32 ;
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 scalar_t__ BCMCPU_IS_6348 () ; 
 int /*<<< orphan*/  EXTIRQ_CFG_MASK (unsigned int) ; 
 int /*<<< orphan*/  EXTIRQ_CFG_MASK_6348 (unsigned int) ; 
 unsigned int IRQ_EXTERNAL_BASE ; 
 int /*<<< orphan*/  bcm_perf_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_perf_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epic_lock ; 
 scalar_t__ ext_irq_start ; 
 int /*<<< orphan*/  get_ext_irq_perf_reg (unsigned int) ; 
 int /*<<< orphan*/  internal_irq_unmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_get_irq_data (scalar_t__) ; 
 scalar_t__ is_ext_irq_cascaded ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm63xx_external_irq_unmask(struct irq_data *d)
{
	unsigned int irq = d->irq - IRQ_EXTERNAL_BASE;
	u32 reg, regaddr;
	unsigned long flags;

	regaddr = get_ext_irq_perf_reg(irq);
	spin_lock_irqsave(&epic_lock, flags);
	reg = bcm_perf_readl(regaddr);

	if (BCMCPU_IS_6348())
		reg |= EXTIRQ_CFG_MASK_6348(irq % 4);
	else
		reg |= EXTIRQ_CFG_MASK(irq % 4);

	bcm_perf_writel(reg, regaddr);
	spin_unlock_irqrestore(&epic_lock, flags);

	if (is_ext_irq_cascaded)
		internal_irq_unmask(irq_get_irq_data(irq + ext_irq_start),
				    NULL);
}