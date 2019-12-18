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
struct gpiobus_pin {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ofw_gpiobus_parse_gpios_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct gpiobus_pin**) ; 

int
ofw_gpiobus_parse_gpios(device_t consumer, char *pname,
	struct gpiobus_pin **pins)
{

	return (ofw_gpiobus_parse_gpios_impl(consumer,
	    ofw_bus_get_node(consumer), pname, NULL, pins));
}