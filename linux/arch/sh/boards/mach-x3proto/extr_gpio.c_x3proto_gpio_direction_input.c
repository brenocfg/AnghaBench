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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYCTLR ; 
 unsigned int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  x3proto_gpio_lock ; 

__attribute__((used)) static int x3proto_gpio_direction_input(struct gpio_chip *chip, unsigned gpio)
{
	unsigned long flags;
	unsigned int data;

	spin_lock_irqsave(&x3proto_gpio_lock, flags);
	data = __raw_readw(KEYCTLR);
	data |= (1 << gpio);
	__raw_writew(data, KEYCTLR);
	spin_unlock_irqrestore(&x3proto_gpio_lock, flags);

	return 0;
}