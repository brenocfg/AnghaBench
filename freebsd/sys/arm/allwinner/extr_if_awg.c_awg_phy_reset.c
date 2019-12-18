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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  gpio_prop ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  delay_prop ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int GPIO_ACTIVE_LOW ; 
 scalar_t__ GPIO_MAP_GPIOS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int*,int*) ; 
 int GPIO_PIN_HIGH ; 
 int GPIO_PIN_LOW ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PIN_SET (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  GPIO_PIN_SETFLAGS (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OF_node_from_xref (int /*<<< orphan*/ ) ; 
 scalar_t__ nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
awg_phy_reset(device_t dev)
{
	pcell_t gpio_prop[4], delay_prop[3];
	phandle_t node, gpio_node;
	device_t gpio;
	uint32_t pin, flags;
	uint32_t pin_value;

	node = ofw_bus_get_node(dev);
	if (OF_getencprop(node, "allwinner,reset-gpio", gpio_prop,
	    sizeof(gpio_prop)) <= 0)
		return (0);

	if (OF_getencprop(node, "allwinner,reset-delays-us", delay_prop,
	    sizeof(delay_prop)) <= 0)
		return (ENXIO);

	gpio_node = OF_node_from_xref(gpio_prop[0]);
	if ((gpio = OF_device_from_xref(gpio_prop[0])) == NULL)
		return (ENXIO);

	if (GPIO_MAP_GPIOS(gpio, node, gpio_node, nitems(gpio_prop) - 1,
	    gpio_prop + 1, &pin, &flags) != 0)
		return (ENXIO);

	pin_value = GPIO_PIN_LOW;
	if (OF_hasprop(node, "allwinner,reset-active-low"))
		pin_value = GPIO_PIN_HIGH;

	if (flags & GPIO_ACTIVE_LOW)
		pin_value = !pin_value;

	GPIO_PIN_SETFLAGS(gpio, pin, GPIO_PIN_OUTPUT);
	GPIO_PIN_SET(gpio, pin, pin_value);
	DELAY(delay_prop[0]);
	GPIO_PIN_SET(gpio, pin, !pin_value);
	DELAY(delay_prop[1]);
	GPIO_PIN_SET(gpio, pin, pin_value);
	DELAY(delay_prop[2]);

	return (0);
}