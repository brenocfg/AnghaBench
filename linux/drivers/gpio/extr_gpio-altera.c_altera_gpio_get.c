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
struct of_mm_gpio_chip {scalar_t__ regs; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALTERA_GPIO_DATA ; 
 int BIT (unsigned int) ; 
 int readl (scalar_t__) ; 
 struct of_mm_gpio_chip* to_of_mm_gpio_chip (struct gpio_chip*) ; 

__attribute__((used)) static int altera_gpio_get(struct gpio_chip *gc, unsigned offset)
{
	struct of_mm_gpio_chip *mm_gc;

	mm_gc = to_of_mm_gpio_chip(gc);

	return !!(readl(mm_gc->regs + ALTERA_GPIO_DATA) & BIT(offset));
}