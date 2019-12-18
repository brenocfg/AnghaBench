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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct tegra_adma_chan {TYPE_2__ vc; TYPE_1__* desc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long tegra_adma_irq_clear (struct tegra_adma_chan*) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t tegra_adma_isr(int irq, void *dev_id)
{
	struct tegra_adma_chan *tdc = dev_id;
	unsigned long status;
	unsigned long flags;

	spin_lock_irqsave(&tdc->vc.lock, flags);

	status = tegra_adma_irq_clear(tdc);
	if (status == 0 || !tdc->desc) {
		spin_unlock_irqrestore(&tdc->vc.lock, flags);
		return IRQ_NONE;
	}

	vchan_cyclic_callback(&tdc->desc->vd);

	spin_unlock_irqrestore(&tdc->vc.lock, flags);

	return IRQ_HANDLED;
}