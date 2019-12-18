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
typedef  int uint32_t ;

/* Variables and functions */
 int EINVAL ; 
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_OUTPUT ; 
 int GPIO_PIN_PULLDOWN ; 
 int GPIO_PIN_PULLUP ; 

int
gpio_check_flags(uint32_t caps, uint32_t flags)
{

	/* Filter unwanted flags. */
	flags &= caps;

	/* Cannot mix input/output together. */
	if (flags & GPIO_PIN_INPUT && flags & GPIO_PIN_OUTPUT)
		return (EINVAL);
	/* Cannot mix pull-up/pull-down together. */
	if (flags & GPIO_PIN_PULLUP && flags & GPIO_PIN_PULLDOWN)
		return (EINVAL);

	return (0);
}