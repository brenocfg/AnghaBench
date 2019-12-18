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
struct TYPE_2__ {int /*<<< orphan*/  bgpio_lock; } ;
struct brcmstb_gpio_bank {TYPE_1__ gc; } ;

/* Variables and functions */
 unsigned long __brcmstb_gpio_get_active_irqs (struct brcmstb_gpio_bank*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned long
brcmstb_gpio_get_active_irqs(struct brcmstb_gpio_bank *bank)
{
	unsigned long status;
	unsigned long flags;

	spin_lock_irqsave(&bank->gc.bgpio_lock, flags);
	status = __brcmstb_gpio_get_active_irqs(bank);
	spin_unlock_irqrestore(&bank->gc.bgpio_lock, flags);

	return status;
}