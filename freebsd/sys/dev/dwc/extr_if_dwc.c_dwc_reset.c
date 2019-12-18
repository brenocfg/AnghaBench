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
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  gpio_prop ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  delay_prop ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 scalar_t__ GPIO_MAP_GPIOS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int*,int*,int*) ; 
 int GPIO_PIN_HIGH ; 
 int GPIO_PIN_LOW ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PIN_SET (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  GPIO_PIN_SETFLAGS (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OF_device_from_xref (int) ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OF_node_from_xref (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nitems (int*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dwc_reset(device_t dev)
{
	pcell_t gpio_prop[4];
	pcell_t delay_prop[3];
	phandle_t node, gpio_node;
	device_t gpio;
	uint32_t pin, flags;
	uint32_t pin_value;

	node = ofw_bus_get_node(dev);
	if (OF_getencprop(node, "snps,reset-gpio",
	    gpio_prop, sizeof(gpio_prop)) <= 0)
		return (0);

	if (OF_getencprop(node, "snps,reset-delays-us",
	    delay_prop, sizeof(delay_prop)) <= 0) {
		device_printf(dev,
		    "Wrong property for snps,reset-delays-us");
		return (ENXIO);
	}

	gpio_node = OF_node_from_xref(gpio_prop[0]);
	if ((gpio = OF_device_from_xref(gpio_prop[0])) == NULL) {
		device_printf(dev,
		    "Can't find gpio controller for phy reset\n");
		return (ENXIO);
	}

	if (GPIO_MAP_GPIOS(gpio, node, gpio_node,
	    nitems(gpio_prop) - 1,
	    gpio_prop + 1, &pin, &flags) != 0) {
		device_printf(dev, "Can't map gpio for phy reset\n");
		return (ENXIO);
	}

	pin_value = GPIO_PIN_LOW;
	if (OF_hasprop(node, "snps,reset-active-low"))
		pin_value = GPIO_PIN_HIGH;

	GPIO_PIN_SETFLAGS(gpio, pin, GPIO_PIN_OUTPUT);
	GPIO_PIN_SET(gpio, pin, pin_value);
	DELAY(delay_prop[0] * 5);
	GPIO_PIN_SET(gpio, pin, !pin_value);
	DELAY(delay_prop[1] * 5);
	GPIO_PIN_SET(gpio, pin, pin_value);
	DELAY(delay_prop[2] * 5);

	return (0);
}