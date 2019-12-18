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
struct amr_softc {void* amr_ccb; void* amr_sgtable; int /*<<< orphan*/ * amr_reg; int /*<<< orphan*/  amr_dev; scalar_t__ amr_parent_dmat; int /*<<< orphan*/ * amr_irq; scalar_t__ amr_intr; scalar_t__ amr_mailbox_dmat; int /*<<< orphan*/  amr_mailbox_dmamap; scalar_t__ amr_mailbox; scalar_t__ amr_mailbox64; scalar_t__ amr_sg_dmat; int /*<<< orphan*/  amr_sg_dmamap; scalar_t__ amr_ccb_dmat; int /*<<< orphan*/  amr_ccb_dmamap; scalar_t__ amr_buffer64_dmat; scalar_t__ amr_buffer_dmat; } ;

/* Variables and functions */
 scalar_t__ AMR_IS_QUARTZ (struct amr_softc*) ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  amr_free (struct amr_softc*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
amr_pci_free(struct amr_softc *sc)
{
    void *p;

    debug_called(1);

    amr_free(sc);

    /* destroy data-transfer DMA tag */
    if (sc->amr_buffer_dmat)
	bus_dma_tag_destroy(sc->amr_buffer_dmat);
    if (sc->amr_buffer64_dmat)
	bus_dma_tag_destroy(sc->amr_buffer64_dmat);

    /* free and destroy DMA memory and tag for passthrough pool */
    if (sc->amr_ccb) {
	bus_dmamap_unload(sc->amr_ccb_dmat, sc->amr_ccb_dmamap);
	bus_dmamem_free(sc->amr_ccb_dmat, sc->amr_ccb, sc->amr_ccb_dmamap);
    }
    if (sc->amr_ccb_dmat)
	bus_dma_tag_destroy(sc->amr_ccb_dmat);

    /* free and destroy DMA memory and tag for s/g lists */
    if (sc->amr_sgtable) {
	bus_dmamap_unload(sc->amr_sg_dmat, sc->amr_sg_dmamap);
	bus_dmamem_free(sc->amr_sg_dmat, sc->amr_sgtable, sc->amr_sg_dmamap);
    }
    if (sc->amr_sg_dmat)
	bus_dma_tag_destroy(sc->amr_sg_dmat);

    /* free and destroy DMA memory and tag for mailbox */
    p = (void *)(uintptr_t)(volatile void *)sc->amr_mailbox64;
    if (sc->amr_mailbox) {
	bus_dmamap_unload(sc->amr_mailbox_dmat, sc->amr_mailbox_dmamap);
	bus_dmamem_free(sc->amr_mailbox_dmat, p, sc->amr_mailbox_dmamap);
    }
    if (sc->amr_mailbox_dmat)
	bus_dma_tag_destroy(sc->amr_mailbox_dmat);

    /* disconnect the interrupt handler */
    if (sc->amr_intr)
	bus_teardown_intr(sc->amr_dev, sc->amr_irq, sc->amr_intr);
    if (sc->amr_irq != NULL)
	bus_release_resource(sc->amr_dev, SYS_RES_IRQ, 0, sc->amr_irq);

    /* destroy the parent DMA tag */
    if (sc->amr_parent_dmat)
	bus_dma_tag_destroy(sc->amr_parent_dmat);

    /* release the register window mapping */
    if (sc->amr_reg != NULL)
	bus_release_resource(sc->amr_dev,
			     AMR_IS_QUARTZ(sc) ? SYS_RES_MEMORY : SYS_RES_IOPORT,
			     PCIR_BAR(0), sc->amr_reg);
}