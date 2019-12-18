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
typedef  int /*<<< orphan*/  uint8_t ;
struct macgpio_softc {int /*<<< orphan*/  sc_gpios; } ;
struct macgpio_devinfo {scalar_t__ gpio_num; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_read_1 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct macgpio_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct macgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

uint8_t
macgpio_read(device_t dev)
{
	struct macgpio_softc *sc;
	struct macgpio_devinfo *dinfo;

	sc = device_get_softc(device_get_parent(dev));
	dinfo = device_get_ivars(dev);

	if (dinfo->gpio_num < 0)
		return (0);

	return (bus_read_1(sc->sc_gpios,dinfo->gpio_num));
}