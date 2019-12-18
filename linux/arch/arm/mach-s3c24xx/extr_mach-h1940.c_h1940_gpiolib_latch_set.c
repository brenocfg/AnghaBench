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
 int h1940_gpiolib_to_latch (unsigned int) ; 
 int /*<<< orphan*/  h1940_latch_control (int,int) ; 

__attribute__((used)) static void h1940_gpiolib_latch_set(struct gpio_chip *chip,
					unsigned offset, int value)
{
	int latch_bit = h1940_gpiolib_to_latch(offset);

	h1940_latch_control(value ? 0 : latch_bit,
		value ? latch_bit : 0);
}