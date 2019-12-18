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
struct bcm_kona_gpio {int /*<<< orphan*/  lock; scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int GPIO_BANK (unsigned int) ; 
 scalar_t__ GPIO_PWD_STATUS (int) ; 
 int /*<<< orphan*/  bcm_kona_gpio_write_lock_regs (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void bcm_kona_gpio_lock_gpio(struct bcm_kona_gpio *kona_gpio,
					unsigned gpio)
{
	u32 val;
	unsigned long flags;
	int bank_id = GPIO_BANK(gpio);

	raw_spin_lock_irqsave(&kona_gpio->lock, flags);

	val = readl(kona_gpio->reg_base + GPIO_PWD_STATUS(bank_id));
	val |= BIT(gpio);
	bcm_kona_gpio_write_lock_regs(kona_gpio->reg_base, bank_id, val);

	raw_spin_unlock_irqrestore(&kona_gpio->lock, flags);
}