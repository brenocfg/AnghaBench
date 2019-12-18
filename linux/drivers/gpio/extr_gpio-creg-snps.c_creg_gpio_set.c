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
struct gpio_chip {int dummy; } ;
struct creg_layout {int* on; int* off; int* shift; int* bit_per_gpio; } ;
struct creg_gpio {int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; struct creg_layout* layout; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 struct creg_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void creg_gpio_set(struct gpio_chip *gc, unsigned int offset, int val)
{
	struct creg_gpio *hcg = gpiochip_get_data(gc);
	const struct creg_layout *layout = hcg->layout;
	u32 reg, reg_shift, value;
	unsigned long flags;
	int i;

	value = val ? hcg->layout->on[offset] : hcg->layout->off[offset];

	reg_shift = layout->shift[offset];
	for (i = 0; i < offset; i++)
		reg_shift += layout->bit_per_gpio[i] + layout->shift[i];

	spin_lock_irqsave(&hcg->lock, flags);
	reg = readl(hcg->regs);
	reg &= ~(GENMASK(layout->bit_per_gpio[i] - 1, 0) << reg_shift);
	reg |=  (value << reg_shift);
	writel(reg, hcg->regs);
	spin_unlock_irqrestore(&hcg->lock, flags);
}