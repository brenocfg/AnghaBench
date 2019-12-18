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
 int simpad_get_cs3_ro () ; 
 int simpad_get_cs3_shadow () ; 

__attribute__((used)) static int cs3_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	if (offset > 15)
		return !!(simpad_get_cs3_ro() & (1 << (offset - 16)));
	return !!(simpad_get_cs3_shadow() & (1 << offset));
}