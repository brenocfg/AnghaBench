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
struct pvscsi_softc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * irq_handler; int /*<<< orphan*/  irq_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pvscsi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvscsi_adapter_reset (struct pvscsi_softc*) ; 
 int /*<<< orphan*/  pvscsi_free_all (struct pvscsi_softc*) ; 
 int /*<<< orphan*/  pvscsi_intr_disable (struct pvscsi_softc*) ; 

__attribute__((used)) static int
pvscsi_detach(device_t dev)
{
	struct pvscsi_softc *sc;

	sc = device_get_softc(dev);

	pvscsi_intr_disable(sc);
	pvscsi_adapter_reset(sc);

	if (sc->irq_handler != NULL) {
		bus_teardown_intr(dev, sc->irq_res, sc->irq_handler);
	}

	mtx_lock(&sc->lock);
	pvscsi_free_all(sc);
	mtx_unlock(&sc->lock);

	mtx_destroy(&sc->lock);

	return (0);
}