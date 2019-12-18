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
struct mly_softc {int /*<<< orphan*/  mly_lock; int /*<<< orphan*/ * mly_regs_resource; int /*<<< orphan*/  mly_regs_rid; int /*<<< orphan*/  mly_dev; scalar_t__ mly_parent_dmat; int /*<<< orphan*/ * mly_irq; int /*<<< orphan*/  mly_irq_rid; scalar_t__ mly_mmbox_dmat; int /*<<< orphan*/  mly_mmbox_dmamap; scalar_t__ mly_mmbox; scalar_t__ mly_sg_dmat; int /*<<< orphan*/  mly_sg_dmamap; scalar_t__ mly_sg_table; scalar_t__ mly_buffer_dmat; int /*<<< orphan*/ * mly_controllerparam; int /*<<< orphan*/ * mly_controllerinfo; int /*<<< orphan*/  mly_timeout; int /*<<< orphan*/  mly_periodic; scalar_t__ mly_intr; int /*<<< orphan*/  mly_dev_t; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mly_cam_detach (struct mly_softc*) ; 
 int /*<<< orphan*/  mly_release_commands (struct mly_softc*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mly_free(struct mly_softc *sc)
{
    
    debug_called(1);

    /* Remove the management device */
    destroy_dev(sc->mly_dev_t);

    if (sc->mly_intr)
	bus_teardown_intr(sc->mly_dev, sc->mly_irq, sc->mly_intr);
    callout_drain(&sc->mly_periodic);
#ifdef MLY_DEBUG
    callout_drain(&sc->mly_timeout);
#endif

    /* detach from CAM */
    mly_cam_detach(sc);

    /* release command memory */
    mly_release_commands(sc);
    
    /* throw away the controllerinfo structure */
    if (sc->mly_controllerinfo != NULL)
	free(sc->mly_controllerinfo, M_DEVBUF);

    /* throw away the controllerparam structure */
    if (sc->mly_controllerparam != NULL)
	free(sc->mly_controllerparam, M_DEVBUF);

    /* destroy data-transfer DMA tag */
    if (sc->mly_buffer_dmat)
	bus_dma_tag_destroy(sc->mly_buffer_dmat);

    /* free and destroy DMA memory and tag for s/g lists */
    if (sc->mly_sg_table) {
	bus_dmamap_unload(sc->mly_sg_dmat, sc->mly_sg_dmamap);
	bus_dmamem_free(sc->mly_sg_dmat, sc->mly_sg_table, sc->mly_sg_dmamap);
    }
    if (sc->mly_sg_dmat)
	bus_dma_tag_destroy(sc->mly_sg_dmat);

    /* free and destroy DMA memory and tag for memory mailbox */
    if (sc->mly_mmbox) {
	bus_dmamap_unload(sc->mly_mmbox_dmat, sc->mly_mmbox_dmamap);
	bus_dmamem_free(sc->mly_mmbox_dmat, sc->mly_mmbox, sc->mly_mmbox_dmamap);
    }
    if (sc->mly_mmbox_dmat)
	bus_dma_tag_destroy(sc->mly_mmbox_dmat);

    /* disconnect the interrupt handler */
    if (sc->mly_irq != NULL)
	bus_release_resource(sc->mly_dev, SYS_RES_IRQ, sc->mly_irq_rid, sc->mly_irq);

    /* destroy the parent DMA tag */
    if (sc->mly_parent_dmat)
	bus_dma_tag_destroy(sc->mly_parent_dmat);

    /* release the register window mapping */
    if (sc->mly_regs_resource != NULL)
	bus_release_resource(sc->mly_dev, SYS_RES_MEMORY, sc->mly_regs_rid, sc->mly_regs_resource);

    mtx_destroy(&sc->mly_lock);
}