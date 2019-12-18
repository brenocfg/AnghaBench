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
struct amdgpio_softc {int /*<<< orphan*/  sc_res; scalar_t__ sc_busdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPIO_LOCK_DESTROY (struct amdgpio_softc*) ; 
 int /*<<< orphan*/  amdgpio_spec ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amdgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_detach_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amdgpio_detach(device_t dev)
{
	struct amdgpio_softc *sc;
	sc = device_get_softc(dev);

	if (sc->sc_busdev)
		gpiobus_detach_bus(dev);

	bus_release_resources(dev, amdgpio_spec, sc->sc_res);

	AMDGPIO_LOCK_DESTROY(sc);

	return (0);
}