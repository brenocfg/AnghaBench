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
struct quicc_softc {int /*<<< orphan*/  sc_rres; int /*<<< orphan*/  sc_rrid; int /*<<< orphan*/  sc_rtype; int /*<<< orphan*/  sc_ires; int /*<<< orphan*/  sc_irid; int /*<<< orphan*/  sc_icookie; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct quicc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
quicc_bfe_detach(device_t dev)
{
	struct quicc_softc *sc;

	sc = device_get_softc(dev);

	bus_teardown_intr(dev, sc->sc_ires, sc->sc_icookie);
	bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irid, sc->sc_ires);
	bus_release_resource(dev, sc->sc_rtype, sc->sc_rrid, sc->sc_rres);
	return (0);
}