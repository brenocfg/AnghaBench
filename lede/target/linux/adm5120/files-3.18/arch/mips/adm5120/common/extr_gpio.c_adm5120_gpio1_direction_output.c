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
 int /*<<< orphan*/  __adm5120_gpio1_set_value (unsigned int,int) ; 

__attribute__((used)) static int adm5120_gpio1_direction_output(struct gpio_chip *chip,
					  unsigned offset, int value)
{
	__adm5120_gpio1_set_value(offset, value);
	return 0;
}