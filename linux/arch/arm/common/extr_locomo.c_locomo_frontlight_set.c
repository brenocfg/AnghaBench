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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct locomo_dev {TYPE_1__ dev; } ;
struct locomo {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 int LOCOMO_ALC_EN ; 
 scalar_t__ LOCOMO_ALD ; 
 scalar_t__ LOCOMO_ALS ; 
 scalar_t__ LOCOMO_FRONTLIGHT ; 
 int /*<<< orphan*/  LOCOMO_GPIO_FL_VR ; 
 struct locomo* locomo_chip_driver (struct locomo_dev*) ; 
 int /*<<< orphan*/  locomo_gpio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  locomo_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

void locomo_frontlight_set(struct locomo_dev *dev, int duty, int vr, int bpwf)
{
	unsigned long flags;
	struct locomo *lchip = locomo_chip_driver(dev);

	if (vr)
		locomo_gpio_write(dev->dev.parent, LOCOMO_GPIO_FL_VR, 1);
	else
		locomo_gpio_write(dev->dev.parent, LOCOMO_GPIO_FL_VR, 0);

	spin_lock_irqsave(&lchip->lock, flags);
	locomo_writel(bpwf, lchip->base + LOCOMO_FRONTLIGHT + LOCOMO_ALS);
	udelay(100);
	locomo_writel(duty, lchip->base + LOCOMO_FRONTLIGHT + LOCOMO_ALD);
	locomo_writel(bpwf | LOCOMO_ALC_EN, lchip->base + LOCOMO_FRONTLIGHT + LOCOMO_ALS);
	spin_unlock_irqrestore(&lchip->lock, flags);
}