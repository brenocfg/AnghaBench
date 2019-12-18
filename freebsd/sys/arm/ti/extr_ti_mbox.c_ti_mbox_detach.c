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
struct ti_mbox_softc {scalar_t__ sc_mem_res; scalar_t__ sc_irq_res; scalar_t__ sc_intr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct ti_mbox_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (scalar_t__) ; 

__attribute__((used)) static int
ti_mbox_detach(device_t dev)
{
	struct ti_mbox_softc *sc;

	sc = device_get_softc(dev);
	if (sc->sc_intr)
		bus_teardown_intr(dev, sc->sc_irq_res, sc->sc_intr);
	if (sc->sc_irq_res)
		bus_release_resource(dev, SYS_RES_IRQ, rman_get_rid(sc->sc_irq_res),
		    sc->sc_irq_res);
	if (sc->sc_mem_res)
		bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(sc->sc_mem_res),
		    sc->sc_mem_res);

	return (0);
}