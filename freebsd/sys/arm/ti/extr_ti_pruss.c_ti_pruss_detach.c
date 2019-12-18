#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ti_pruss_softc {scalar_t__ sc_pdev; scalar_t__ sc_mem_res; int /*<<< orphan*/  sc_mtx; TYPE_2__* sc_irq_devs; scalar_t__* sc_irq_res; scalar_t__* sc_intr; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {int /*<<< orphan*/  sc_mtx; TYPE_1__ sc_selinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int TI_PRUSS_HOST_IRQS ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  destroy_dev (scalar_t__) ; 
 struct ti_pruss_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  rman_get_rid (scalar_t__) ; 
 int /*<<< orphan*/  ti_pruss_interrupts_clear (struct ti_pruss_softc*) ; 
 int /*<<< orphan*/  ti_pruss_interrupts_enable (struct ti_pruss_softc*,int,int) ; 

__attribute__((used)) static int
ti_pruss_detach(device_t dev)
{
	struct ti_pruss_softc *sc = device_get_softc(dev);

	ti_pruss_interrupts_clear(sc);

	for (int i = 0; i < TI_PRUSS_HOST_IRQS; i++) {
		ti_pruss_interrupts_enable( sc, i, false );

		if (sc->sc_intr[i])
			bus_teardown_intr(dev, sc->sc_irq_res[i], sc->sc_intr[i]);
		if (sc->sc_irq_res[i])
			bus_release_resource(dev, SYS_RES_IRQ,
			    rman_get_rid(sc->sc_irq_res[i]),
			    sc->sc_irq_res[i]);
		knlist_clear(&sc->sc_irq_devs[i].sc_selinfo.si_note, 0);
		mtx_lock(&sc->sc_irq_devs[i].sc_mtx);
		if (!knlist_empty(&sc->sc_irq_devs[i].sc_selinfo.si_note))
			printf("IRQ %d KQueue not empty!\n", i );
		mtx_unlock(&sc->sc_irq_devs[i].sc_mtx);
		knlist_destroy(&sc->sc_irq_devs[i].sc_selinfo.si_note);
		mtx_destroy(&sc->sc_irq_devs[i].sc_mtx);
	}

	mtx_destroy(&sc->sc_mtx);
	if (sc->sc_mem_res)
		bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(sc->sc_mem_res),
		    sc->sc_mem_res);
	if (sc->sc_pdev)
		destroy_dev(sc->sc_pdev);

	return (0);
}