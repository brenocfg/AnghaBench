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
struct imx51_gpio_softc {int gpio_npins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct imx51_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imx51_gpio_pin_max(device_t dev, int *maxpin)
{
	struct imx51_gpio_softc *sc;

	sc = device_get_softc(dev);
	*maxpin = sc->gpio_npins - 1;

	return (0);
}