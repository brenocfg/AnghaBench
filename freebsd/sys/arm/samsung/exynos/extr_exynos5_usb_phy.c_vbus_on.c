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
struct usb_phy_softc {int /*<<< orphan*/  dev; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PIN_HIGH ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PIN_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_PIN_SETFLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_getencprop (int,char*,int /*<<< orphan*/ *,int) ; 
 int OF_getproplen (int,char*) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vbus_on(struct usb_phy_softc *sc)
{
	pcell_t dts_value[3];
	device_t gpio_dev;
	phandle_t node;
	pcell_t pin;
	int len;

	if ((node = ofw_bus_get_node(sc->dev)) == -1)
		return (-1);

	/* Power pin */
	if ((len = OF_getproplen(node, "vbus-supply")) <= 0)
		return (-1);
	OF_getencprop(node, "vbus-supply", dts_value, len);
	pin = dts_value[0];

	gpio_dev = devclass_get_device(devclass_find("gpio"), 0);
	if (gpio_dev == NULL) {
		device_printf(sc->dev, "can't find gpio_dev\n");
		return (1);
	}

	GPIO_PIN_SETFLAGS(gpio_dev, pin, GPIO_PIN_OUTPUT);
	GPIO_PIN_SET(gpio_dev, pin, GPIO_PIN_HIGH);

	return (0);
}