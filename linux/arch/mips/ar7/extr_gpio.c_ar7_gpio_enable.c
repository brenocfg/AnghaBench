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

/* Variables and functions */
 int ar7_gpio_enable_ar7 (unsigned int) ; 
 int ar7_gpio_enable_titan (unsigned int) ; 
 scalar_t__ ar7_is_titan () ; 

int ar7_gpio_enable(unsigned gpio)
{
	return ar7_is_titan() ? ar7_gpio_enable_titan(gpio) :
				ar7_gpio_enable_ar7(gpio);
}