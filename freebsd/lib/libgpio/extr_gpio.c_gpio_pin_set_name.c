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
struct gpio_pin {int /*<<< orphan*/  gp_name; int /*<<< orphan*/  gp_pin; } ;
typedef  int /*<<< orphan*/  gppin ;
typedef  int /*<<< orphan*/  gpio_pin_t ;
typedef  int /*<<< orphan*/  gpio_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOMAXNAME ; 
 int /*<<< orphan*/  GPIOSETNAME ; 
 int /*<<< orphan*/  bzero (struct gpio_pin*,int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gpio_pin*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
gpio_pin_set_name(gpio_handle_t handle, gpio_pin_t pin, char *name)
{
	struct gpio_pin gppin;

	if (name == NULL)
		return (-1);
	bzero(&gppin, sizeof(gppin));
	gppin.gp_pin = pin;
	strlcpy(gppin.gp_name, name, GPIOMAXNAME);
	if (ioctl(handle, GPIOSETNAME, &gppin) < 0)
		return (-1);

	return (0);
}