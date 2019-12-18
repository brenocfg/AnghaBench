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
struct gpio_req {scalar_t__ gp_value; int /*<<< orphan*/  gp_pin; } ;
typedef  int /*<<< orphan*/  gpreq ;
typedef  scalar_t__ gpio_value_t ;
typedef  int /*<<< orphan*/  gpio_pin_t ;
typedef  int /*<<< orphan*/  gpio_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOSET ; 
 scalar_t__ GPIO_VALUE_INVALID ; 
 int /*<<< orphan*/  bzero (struct gpio_req*,int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gpio_req*) ; 

int
gpio_pin_set(gpio_handle_t handle, gpio_pin_t pin, gpio_value_t value)
{
	struct gpio_req gpreq;

	if (value == GPIO_VALUE_INVALID)
		return (-1);
	bzero(&gpreq, sizeof(gpreq));
	gpreq.gp_pin = pin;
	gpreq.gp_value = value;
	if (ioctl(handle, GPIOSET, &gpreq) < 0)
		return (-1);

	return (0);
}