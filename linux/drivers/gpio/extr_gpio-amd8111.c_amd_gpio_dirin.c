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
typedef  int u8 ;
struct gpio_chip {int dummy; } ;
struct amd_gpio {TYPE_1__* pdev; int /*<<< orphan*/  lock; scalar_t__ pm; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AMD_GPIO_DEBOUNCE ; 
 int AMD_GPIO_MODE_IN ; 
 scalar_t__ AMD_REG_GPIO (unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 struct amd_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int amd_gpio_dirin(struct gpio_chip *chip, unsigned offset)
{
	struct amd_gpio *agp = gpiochip_get_data(chip);
	u8 temp;
	unsigned long flags;

	spin_lock_irqsave(&agp->lock, flags);
	temp = ioread8(agp->pm + AMD_REG_GPIO(offset));
	temp = (temp & AMD_GPIO_DEBOUNCE) | AMD_GPIO_MODE_IN;
	iowrite8(temp, agp->pm + AMD_REG_GPIO(offset));
	spin_unlock_irqrestore(&agp->lock, flags);

	dev_dbg(&agp->pdev->dev, "Dirin gpio %d, reg=%02x\n", offset, temp);

	return 0;
}