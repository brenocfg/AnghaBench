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
struct aac_softc {scalar_t__ aac_hwif; int /*<<< orphan*/ * aac_regs_res1; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/ * aac_regs_res0; scalar_t__ aac_parent_dmat; scalar_t__ aac_buffer_dmat; int /*<<< orphan*/ * aac_irq; scalar_t__ aac_intr; scalar_t__ aac_common_dmat; int /*<<< orphan*/  aac_common_dmamap; scalar_t__ aac_common; int /*<<< orphan*/  aac_commands; scalar_t__ aac_fib_dmat; int /*<<< orphan*/ * aac_dev_t; } ;

/* Variables and functions */
 scalar_t__ AAC_HWIF_NARK ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  M_AACBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  aac_free_commands (struct aac_softc*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

void
aac_free(struct aac_softc *sc)
{

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/* remove the control device */
	if (sc->aac_dev_t != NULL)
		destroy_dev(sc->aac_dev_t);

	/* throw away any FIB buffers, discard the FIB DMA tag */
	aac_free_commands(sc);
	if (sc->aac_fib_dmat)
		bus_dma_tag_destroy(sc->aac_fib_dmat);

	free(sc->aac_commands, M_AACBUF);

	/* destroy the common area */
	if (sc->aac_common) {
		bus_dmamap_unload(sc->aac_common_dmat, sc->aac_common_dmamap);
		bus_dmamem_free(sc->aac_common_dmat, sc->aac_common,
				sc->aac_common_dmamap);
	}
	if (sc->aac_common_dmat)
		bus_dma_tag_destroy(sc->aac_common_dmat);

	/* disconnect the interrupt handler */
	if (sc->aac_intr)
		bus_teardown_intr(sc->aac_dev, sc->aac_irq, sc->aac_intr);
	if (sc->aac_irq != NULL) {
		bus_release_resource(sc->aac_dev, SYS_RES_IRQ,
		    rman_get_rid(sc->aac_irq), sc->aac_irq);
		pci_release_msi(sc->aac_dev);
	}

	/* destroy data-transfer DMA tag */
	if (sc->aac_buffer_dmat)
		bus_dma_tag_destroy(sc->aac_buffer_dmat);

	/* destroy the parent DMA tag */
	if (sc->aac_parent_dmat)
		bus_dma_tag_destroy(sc->aac_parent_dmat);

	/* release the register window mapping */
	if (sc->aac_regs_res0 != NULL)
		bus_release_resource(sc->aac_dev, SYS_RES_MEMORY,
		    rman_get_rid(sc->aac_regs_res0), sc->aac_regs_res0);
	if (sc->aac_hwif == AAC_HWIF_NARK && sc->aac_regs_res1 != NULL)
		bus_release_resource(sc->aac_dev, SYS_RES_MEMORY,
		    rman_get_rid(sc->aac_regs_res1), sc->aac_regs_res1);
}