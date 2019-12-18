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
struct mpc85xx_gpio_softc {int /*<<< orphan*/ * in_res; int /*<<< orphan*/ * out_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_LOCK_DESTROY (struct mpc85xx_gpio_softc*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mpc85xx_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_detach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mpc85xx_gpio_detach(device_t dev)
{
	struct mpc85xx_gpio_softc *sc = device_get_softc(dev);

	gpiobus_detach_bus(dev);

	if (sc->out_res != NULL) {
		/* Release output port resource. */
		bus_release_resource(dev, SYS_RES_MEMORY,
				     rman_get_rid(sc->out_res), sc->out_res);
	}

	if (sc->in_res != NULL) {
		/* Release input port resource. */
		bus_release_resource(dev, SYS_RES_MEMORY,
				     rman_get_rid(sc->in_res), sc->in_res);
	}

	GPIO_LOCK_DESTROY(sc);

	return (0);
}