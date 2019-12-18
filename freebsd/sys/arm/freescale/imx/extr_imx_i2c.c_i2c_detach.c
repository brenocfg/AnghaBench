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
struct i2c_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/  rb_sdapin; int /*<<< orphan*/  rb_sclpin; int /*<<< orphan*/ * iicbus; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_pin_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i2c_detach(device_t dev)
{
	struct i2c_softc *sc;
	int error;

	sc = device_get_softc(dev);

	if ((error = bus_generic_detach(sc->dev)) != 0) {
		device_printf(sc->dev, "cannot detach child devices\n");
		return (error);
	}

	if (sc->iicbus != NULL)
		device_delete_child(dev, sc->iicbus);

	/* Release bus-recover pins; gpio_pin_release() handles NULL args. */
	gpio_pin_release(sc->rb_sclpin);
	gpio_pin_release(sc->rb_sdapin);

	if (sc->res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->res);

	return (0);
}