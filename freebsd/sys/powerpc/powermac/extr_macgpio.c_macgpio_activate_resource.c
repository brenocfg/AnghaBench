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
typedef  int u_char ;
struct resource {int dummy; } ;
struct macgpio_softc {int /*<<< orphan*/  sc_gpios; } ;
struct macgpio_devinfo {scalar_t__ gpio_num; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int SYS_RES_IRQ ; 
 int bus_activate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int bus_read_1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct macgpio_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct macgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
macgpio_activate_resource(device_t bus, device_t child, int type, int rid,
			   struct resource *res)
{
	struct macgpio_softc *sc;
	struct macgpio_devinfo *dinfo;
	u_char val;

	sc = device_get_softc(bus);
	dinfo = device_get_ivars(child);

	if (type != SYS_RES_IRQ)
		return ENXIO;

	if (dinfo->gpio_num >= 0) {
		val = bus_read_1(sc->sc_gpios,dinfo->gpio_num);
		val |= 0x80;
		bus_write_1(sc->sc_gpios,dinfo->gpio_num,val);
	}

	return (bus_activate_resource(bus, type, rid, res));
}