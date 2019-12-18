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
typedef  int u32 ;
struct mcs814x_gpio_chip {scalar_t__ regs; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ GPIO_PIN ; 
 int readl_relaxed (scalar_t__) ; 
 struct mcs814x_gpio_chip* to_mcs814x_gpio_chip (struct gpio_chip*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void mcs814x_gpio_set(struct gpio_chip *chip,
				unsigned offset, int value)
{
	struct mcs814x_gpio_chip *mcs814x = to_mcs814x_gpio_chip(chip);
	u32 mask;

	mask = readl_relaxed(mcs814x->regs + GPIO_PIN);
	if (value)
		mask |= (1 << offset);
	else
		mask &= ~(1 << offset);
	writel_relaxed(mask, mcs814x->regs + GPIO_PIN);
}