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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_FN_INTC_IRQ0 ; 
 int /*<<< orphan*/  GPIO_PTZ0 ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ts_get_pendown_state(struct device *dev)
{
	int val = 0;
	gpio_free(GPIO_FN_INTC_IRQ0);
	gpio_request(GPIO_PTZ0, NULL);
	gpio_direction_input(GPIO_PTZ0);

	val = gpio_get_value(GPIO_PTZ0);

	gpio_free(GPIO_PTZ0);
	gpio_request(GPIO_FN_INTC_IRQ0, NULL);

	return val ? 0 : 1;
}