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
struct gpio_req {int /*<<< orphan*/  gp_pin; } ;
typedef  int /*<<< orphan*/  gpreq ;
typedef  int /*<<< orphan*/  gpio_pin_t ;
typedef  int /*<<< orphan*/  gpio_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOTOGGLE ; 
 int /*<<< orphan*/  bzero (struct gpio_req*,int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gpio_req*) ; 

int
gpio_pin_toggle(gpio_handle_t handle, gpio_pin_t pin)
{
	struct gpio_req gpreq;

	bzero(&gpreq, sizeof(gpreq));
	gpreq.gp_pin = pin;
	if (ioctl(handle, GPIOTOGGLE, &gpreq) < 0)
		return (-1);

	return (0);
}