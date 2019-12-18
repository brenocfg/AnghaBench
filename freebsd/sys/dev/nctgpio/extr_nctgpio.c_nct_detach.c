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
struct nct_softc {int /*<<< orphan*/ * iores; int /*<<< orphan*/  iorid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_ASSERT_UNLOCKED (struct nct_softc*) ; 
 int /*<<< orphan*/  GPIO_LOCK_DESTROY (struct nct_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nct_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_detach_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nct_detach(device_t dev)
{
	struct nct_softc *sc;

	sc = device_get_softc(dev);
	gpiobus_detach_bus(dev);

	if (sc->iores != NULL)
		bus_release_resource(dev, SYS_RES_IOPORT, sc->iorid, sc->iores);
	GPIO_ASSERT_UNLOCKED(sc);
	GPIO_LOCK_DESTROY(sc);

	return (0);
}