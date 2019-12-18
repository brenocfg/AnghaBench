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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct gpio_desc {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct aspeed_gpio_bank {int /*<<< orphan*/  rdata_reg; int /*<<< orphan*/  val_regs; } ;
struct TYPE_2__ {int ngpio; } ;
struct aspeed_gpio {int* cf_copro_bankmap; int /*<<< orphan*/  lock; TYPE_1__ chip; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIO_CMDSRC_COLDFIRE ; 
 int /*<<< orphan*/  GPIO_OFFSET (int) ; 
 int /*<<< orphan*/  aspeed_gpio_change_cmd_source (struct aspeed_gpio*,struct aspeed_gpio_bank const*,int,int /*<<< orphan*/ ) ; 
 int gpio_chip_hwgpio (struct gpio_desc*) ; 
 struct aspeed_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* gpiod_to_chip (struct gpio_desc*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct aspeed_gpio_bank* to_bank (int) ; 

int aspeed_gpio_copro_grab_gpio(struct gpio_desc *desc,
				u16 *vreg_offset, u16 *dreg_offset, u8 *bit)
{
	struct gpio_chip *chip = gpiod_to_chip(desc);
	struct aspeed_gpio *gpio = gpiochip_get_data(chip);
	int rc = 0, bindex, offset = gpio_chip_hwgpio(desc);
	const struct aspeed_gpio_bank *bank = to_bank(offset);
	unsigned long flags;

	if (!gpio->cf_copro_bankmap)
		gpio->cf_copro_bankmap = kzalloc(gpio->chip.ngpio >> 3, GFP_KERNEL);
	if (!gpio->cf_copro_bankmap)
		return -ENOMEM;
	if (offset < 0 || offset > gpio->chip.ngpio)
		return -EINVAL;
	bindex = offset >> 3;

	spin_lock_irqsave(&gpio->lock, flags);

	/* Sanity check, this shouldn't happen */
	if (gpio->cf_copro_bankmap[bindex] == 0xff) {
		rc = -EIO;
		goto bail;
	}
	gpio->cf_copro_bankmap[bindex]++;

	/* Switch command source */
	if (gpio->cf_copro_bankmap[bindex] == 1)
		aspeed_gpio_change_cmd_source(gpio, bank, bindex,
					      GPIO_CMDSRC_COLDFIRE);

	if (vreg_offset)
		*vreg_offset = bank->val_regs;
	if (dreg_offset)
		*dreg_offset = bank->rdata_reg;
	if (bit)
		*bit = GPIO_OFFSET(offset);
 bail:
	spin_unlock_irqrestore(&gpio->lock, flags);
	return rc;
}