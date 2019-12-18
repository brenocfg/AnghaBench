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
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  txx9_gpio_lock ; 
 TYPE_1__* txx9_pioptr ; 

__attribute__((used)) static int txx9_gpio_dir_in(struct gpio_chip *chip, unsigned int offset)
{
	unsigned long flags;
	spin_lock_irqsave(&txx9_gpio_lock, flags);
	__raw_writel(__raw_readl(&txx9_pioptr->dir) & ~(1 << offset),
		     &txx9_pioptr->dir);
	mmiowb();
	spin_unlock_irqrestore(&txx9_gpio_lock, flags);
	return 0;
}