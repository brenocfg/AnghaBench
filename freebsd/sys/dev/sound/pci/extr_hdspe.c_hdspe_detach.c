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
struct sc_info {scalar_t__ lock; scalar_t__ cs; scalar_t__ irq; scalar_t__ dmat; scalar_t__ ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 
 struct sc_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hdspe_dmafree (struct sc_info*) ; 
 int /*<<< orphan*/  snd_mtxfree (scalar_t__) ; 

__attribute__((used)) static int
hdspe_detach(device_t dev)
{
	struct sc_info *sc;
	int err;

	sc = device_get_softc(dev);
	if (sc == NULL) {
		device_printf(dev,"Can't detach: softc is null.\n");
		return (0);
	}

	err = device_delete_children(dev);
	if (err)
		return (err);

	hdspe_dmafree(sc);

	if (sc->ih)
		bus_teardown_intr(dev, sc->irq, sc->ih);
	if (sc->dmat)
		bus_dma_tag_destroy(sc->dmat);
	if (sc->irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq);
	if (sc->cs)
		bus_release_resource(dev, SYS_RES_MEMORY, PCIR_BAR(0), sc->cs);
	if (sc->lock)
		snd_mtxfree(sc->lock);

	return (0);
}