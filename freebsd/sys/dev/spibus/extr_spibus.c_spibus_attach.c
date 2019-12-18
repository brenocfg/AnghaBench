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
struct spibus_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct spibus_softc* SPIBUS_SOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spibus_attach(device_t dev)
{
	struct spibus_softc *sc = SPIBUS_SOFTC(dev);

	sc->dev = dev;
	bus_enumerate_hinted_children(dev);
	return (bus_generic_attach(dev));
}