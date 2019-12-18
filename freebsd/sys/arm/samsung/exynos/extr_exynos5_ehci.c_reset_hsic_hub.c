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
struct exynos_ehci_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  pin ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  GPIO_PIN_HIGH ; 
 int /*<<< orphan*/  GPIO_PIN_LOW ; 
 int /*<<< orphan*/  GPIO_PIN_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
reset_hsic_hub(struct exynos_ehci_softc *esc, phandle_t hub)
{
	device_t gpio_dev;
	pcell_t pin;

	/* TODO: check that hub is compatible with "smsc,usb3503" */
	if (!OF_hasprop(hub, "freebsd,reset-gpio")) {
		return (1);
	}

	if (OF_getencprop(hub, "freebsd,reset-gpio", &pin, sizeof(pin)) < 0) {
		device_printf(esc->dev,
		    "failed to decode reset GPIO pin number for HSIC hub\n");
		return (1);
	}

	/* Get the GPIO device, we need this to give power to USB */
	gpio_dev = devclass_get_device(devclass_find("gpio"), 0);
	if (gpio_dev == NULL) {
		device_printf(esc->dev, "Cant find gpio device\n");
		return (1);
	}

	GPIO_PIN_SET(gpio_dev, pin, GPIO_PIN_LOW);
	DELAY(100);
	GPIO_PIN_SET(gpio_dev, pin, GPIO_PIN_HIGH);

	return (0);
}