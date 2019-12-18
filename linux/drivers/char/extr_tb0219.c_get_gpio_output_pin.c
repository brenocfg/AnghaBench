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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  TB0219_GPIO_OUTPUT ; 
 int tb0219_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char get_gpio_output_pin(unsigned int pin)
{
	uint16_t values;

	values = tb0219_read(TB0219_GPIO_OUTPUT);
	if (values & (1 << pin))
		return '1';

	return '0';
}