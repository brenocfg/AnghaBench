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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  gpio_pin_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int gpio_pin_get_by_ofw_propidx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

int
gpio_pin_get_by_ofw_idx(device_t consumer, phandle_t node,
    int idx, gpio_pin_t *pin)
{

	return (gpio_pin_get_by_ofw_propidx(consumer, node, "gpios", idx, pin));
}