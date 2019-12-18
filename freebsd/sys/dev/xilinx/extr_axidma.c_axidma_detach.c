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
struct axidma_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/ * ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  axidma_spec ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axidma_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
axidma_detach(device_t dev)
{
	struct axidma_softc *sc;

	sc = device_get_softc(dev);

	bus_teardown_intr(dev, sc->res[1], sc->ih[0]);
	bus_teardown_intr(dev, sc->res[2], sc->ih[1]);
	bus_release_resources(dev, axidma_spec, sc->res);

	return (0);
}