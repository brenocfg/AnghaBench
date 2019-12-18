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
struct atiixp_info {scalar_t__ registered_channels; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * sgd_dmat; int /*<<< orphan*/ * sgd_table; int /*<<< orphan*/  sgd_dmamap; scalar_t__ sgd_addr; int /*<<< orphan*/ * parent_dmat; int /*<<< orphan*/ * irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/  dev; int /*<<< orphan*/ * reg; int /*<<< orphan*/  regid; int /*<<< orphan*/  regtype; int /*<<< orphan*/ * ih; int /*<<< orphan*/ * codec; int /*<<< orphan*/  poll_timer; scalar_t__ polling; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  ac97_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atiixp_lock (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_unlock (struct atiixp_info*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct atiixp_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
atiixp_release_resource(struct atiixp_info *sc)
{
	if (sc == NULL)
		return;
	if (sc->registered_channels != 0) {
		atiixp_lock(sc);
		sc->polling = 0;
		callout_stop(&sc->poll_timer);
		atiixp_unlock(sc);
		callout_drain(&sc->poll_timer);
	}
	if (sc->codec) {
		ac97_destroy(sc->codec);
		sc->codec = NULL;
	}
	if (sc->ih) {
		bus_teardown_intr(sc->dev, sc->irq, sc->ih);
		sc->ih = NULL;
	}
	if (sc->reg) {
		bus_release_resource(sc->dev, sc->regtype, sc->regid, sc->reg);
		sc->reg = NULL;
	}
	if (sc->irq) {
		bus_release_resource(sc->dev, SYS_RES_IRQ, sc->irqid, sc->irq);
		sc->irq = NULL;
	}
	if (sc->parent_dmat) {
		bus_dma_tag_destroy(sc->parent_dmat);
		sc->parent_dmat = NULL;
	}
	if (sc->sgd_addr) {
		bus_dmamap_unload(sc->sgd_dmat, sc->sgd_dmamap);
		sc->sgd_addr = 0;
	}
	if (sc->sgd_table) {
		bus_dmamem_free(sc->sgd_dmat, sc->sgd_table, sc->sgd_dmamap);
		sc->sgd_table = NULL;
	}
	if (sc->sgd_dmat) {
		bus_dma_tag_destroy(sc->sgd_dmat);
		sc->sgd_dmat = NULL;
	}
	if (sc->lock) {
		snd_mtxfree(sc->lock);
		sc->lock = NULL;
	}
	free(sc, M_DEVBUF);
}