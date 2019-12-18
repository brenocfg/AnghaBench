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
struct bytgpio_softc {int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_mem_rid; scalar_t__ sc_pad_funcs; scalar_t__ sc_busdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BYTGPIO_LOCK_DESTROY (struct bytgpio_softc*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bytgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_detach_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bytgpio_detach(device_t dev)
{
	struct bytgpio_softc	*sc;

	sc = device_get_softc(dev);

	if (sc->sc_busdev)
		gpiobus_detach_bus(dev);

	BYTGPIO_LOCK_DESTROY(sc);

	if (sc->sc_pad_funcs)
		free(sc->sc_pad_funcs, M_DEVBUF);

	if (sc->sc_mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    sc->sc_mem_rid, sc->sc_mem_res);

	return (0);
}