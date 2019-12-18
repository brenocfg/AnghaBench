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
struct locomo {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ LOCOMO_GPO ; 
 struct locomo* dev_get_drvdata (struct device*) ; 
 unsigned int locomo_readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int locomo_gpio_read_output(struct device *dev, unsigned int bits)
{
	struct locomo *lchip = dev_get_drvdata(dev);
	unsigned long flags;
	unsigned int ret;

	if (!lchip)
		return -ENODEV;

	spin_lock_irqsave(&lchip->lock, flags);
	ret = locomo_readl(lchip->base + LOCOMO_GPO);
	spin_unlock_irqrestore(&lchip->lock, flags);

	ret &= bits;
	return ret;
}