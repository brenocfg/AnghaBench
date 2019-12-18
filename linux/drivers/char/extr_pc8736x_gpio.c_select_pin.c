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
 int /*<<< orphan*/  SIO_GPIO_PIN_SELECT ; 
 int /*<<< orphan*/  SIO_GPIO_UNIT ; 
 int /*<<< orphan*/  device_select (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_outb (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void select_pin(unsigned iminor)
{
	/* select GPIO port/pin from device minor number */
	device_select(SIO_GPIO_UNIT);
	superio_outb(SIO_GPIO_PIN_SELECT,
		     ((iminor << 1) & 0xF0) | (iminor & 0x7));
}