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
struct sc_info {int /*<<< orphan*/  ich_lock; int /*<<< orphan*/  dmat; int /*<<< orphan*/  chan_dmat; int /*<<< orphan*/  dtmap; int /*<<< orphan*/  dtbl; int /*<<< orphan*/  nabmbar; int /*<<< orphan*/  nabmbarid; int /*<<< orphan*/  regtype; int /*<<< orphan*/  nambar; int /*<<< orphan*/  nambarid; int /*<<< orphan*/  irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/  ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ich_pci_detach(device_t dev)
{
	struct sc_info *sc;
	int r;

	r = pcm_unregister(dev);
	if (r)
		return (r);
	sc = pcm_getdevinfo(dev);

	bus_teardown_intr(dev, sc->irq, sc->ih);
	bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
	bus_release_resource(dev, sc->regtype, sc->nambarid, sc->nambar);
	bus_release_resource(dev, sc->regtype, sc->nabmbarid, sc->nabmbar);
	bus_dmamap_unload(sc->dmat, sc->dtmap);
	bus_dmamem_free(sc->dmat, sc->dtbl, sc->dtmap);
	bus_dma_tag_destroy(sc->chan_dmat);
	bus_dma_tag_destroy(sc->dmat);
	snd_mtxfree(sc->ich_lock);
	free(sc, M_DEVBUF);
	return (0);
}