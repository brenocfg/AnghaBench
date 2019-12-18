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
 int /*<<< orphan*/  simpad_clear_cs3_bit (int) ; 
 int /*<<< orphan*/  simpad_set_cs3_bit (int) ; 

__attribute__((used)) static void cs3_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	if (offset > 15)
		return;
	if (value)
		simpad_set_cs3_bit(1 << offset);
	else
		simpad_clear_cs3_bit(1 << offset);
}