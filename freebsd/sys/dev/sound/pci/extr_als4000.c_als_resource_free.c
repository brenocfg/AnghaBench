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
struct sc_info {int /*<<< orphan*/ * lock; scalar_t__ parent_dmat; int /*<<< orphan*/ * irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/ * ih; int /*<<< orphan*/ * reg; int /*<<< orphan*/  regid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
als_resource_free(device_t dev, struct sc_info *sc)
{
	if (sc->reg) {
		bus_release_resource(dev, SYS_RES_IOPORT, sc->regid, sc->reg);
		sc->reg = NULL;
	}
	if (sc->ih) {
		bus_teardown_intr(dev, sc->irq, sc->ih);
		sc->ih = NULL;
	}
	if (sc->irq) {
		bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
		sc->irq = NULL;
	}
	if (sc->parent_dmat) {
		bus_dma_tag_destroy(sc->parent_dmat);
		sc->parent_dmat = 0;
	}
	if (sc->lock) {
		snd_mtxfree(sc->lock);
		sc->lock = NULL;
	}
}