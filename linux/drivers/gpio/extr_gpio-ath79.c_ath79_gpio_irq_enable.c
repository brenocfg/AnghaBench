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
struct irq_data {int dummy; } ;
struct ath79_gpio_ctrl {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_GPIO_REG_INT_ENABLE ; 
 int /*<<< orphan*/  AR71XX_GPIO_REG_INT_MASK ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath79_gpio_update_bits (struct ath79_gpio_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath79_gpio_ctrl* irq_data_to_ath79_gpio (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ath79_gpio_irq_enable(struct irq_data *data)
{
	struct ath79_gpio_ctrl *ctrl = irq_data_to_ath79_gpio(data);
	u32 mask = BIT(irqd_to_hwirq(data));
	unsigned long flags;

	raw_spin_lock_irqsave(&ctrl->lock, flags);
	ath79_gpio_update_bits(ctrl, AR71XX_GPIO_REG_INT_ENABLE, mask, mask);
	ath79_gpio_update_bits(ctrl, AR71XX_GPIO_REG_INT_MASK, mask, mask);
	raw_spin_unlock_irqrestore(&ctrl->lock, flags);
}