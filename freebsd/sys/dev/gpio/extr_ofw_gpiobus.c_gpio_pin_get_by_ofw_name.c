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
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  gpio_pin_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int gpio_pin_get_by_ofw_idx (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int ofw_bus_find_string_index (scalar_t__,char*,char*,int*) ; 

int
gpio_pin_get_by_ofw_name(device_t consumer, phandle_t node,
    char *name, gpio_pin_t *pin)
{
	int rv, idx;

	KASSERT(consumer != NULL && node > 0,
	    ("both consumer and node required"));

	rv = ofw_bus_find_string_index(node, "gpio-names", name, &idx);
	if (rv != 0)
		return (rv);
	return (gpio_pin_get_by_ofw_idx(consumer, node, idx, pin));
}