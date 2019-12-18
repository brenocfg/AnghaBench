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
struct imx51_gpio_softc {int /*<<< orphan*/  sc_busdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct imx51_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static device_t
imx51_gpio_get_bus(device_t dev)
{
	struct imx51_gpio_softc *sc;

	sc = device_get_softc(dev);

	return (sc->sc_busdev);
}