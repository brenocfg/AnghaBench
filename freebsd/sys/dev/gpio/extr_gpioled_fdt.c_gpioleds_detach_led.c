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
struct gpioled {scalar_t__ pin; int /*<<< orphan*/ * leddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_pin_release (scalar_t__) ; 
 int /*<<< orphan*/  led_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gpioleds_detach_led(struct gpioled *led)
{

	if (led->leddev != NULL)
		led_destroy(led->leddev);

	if (led->pin)
		gpio_pin_release(led->pin);
}