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
struct versatile_sic_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * mem_res; scalar_t__ intrh; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 struct versatile_sic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
versatile_sic_detach(device_t dev)
{
	struct		versatile_sic_softc *sc;

	sc = device_get_softc(dev);

	if (sc->intrh)
		bus_teardown_intr(dev, sc->irq_res, sc->intrh);

	if (sc->mem_res == NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
			rman_get_rid(sc->mem_res), sc->mem_res);

	if (sc->irq_res == NULL)
		bus_release_resource(dev, SYS_RES_IRQ,
			rman_get_rid(sc->irq_res), sc->irq_res);

	mtx_destroy(&sc->mtx);

	return (0);

}