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
struct aac_softc {int /*<<< orphan*/ * aac_regs_res1; int /*<<< orphan*/  aac_regs_rid1; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/ * aac_regs_res0; int /*<<< orphan*/  aac_regs_rid0; scalar_t__ aac_parent_dmat; scalar_t__ aac_buffer_dmat; scalar_t__ msi_tupelo; scalar_t__ msi_enabled; int /*<<< orphan*/ ** aac_irq; int /*<<< orphan*/ * aac_irq_rid; scalar_t__* aac_intr; scalar_t__ aac_common_dmat; int /*<<< orphan*/  aac_common_dmamap; scalar_t__ aac_common; int /*<<< orphan*/  aac_commands; scalar_t__ aac_fib_dmat; int /*<<< orphan*/ * aac_dev_t; } ;

/* Variables and functions */
 int AAC_MAX_MSIX ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  M_AACRAIDBUF ; 
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

void
aacraid_free(struct aac_softc *sc)
{
	int i;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/* remove the control device */
	if (sc->aac_dev_t != NULL)
		destroy_dev(sc->aac_dev_t);

	/* throw away any FIB buffers, discard the FIB DMA tag */
	aac_free_commands(sc);
	if (sc->aac_fib_dmat)
		bus_dma_tag_destroy(sc->aac_fib_dmat);

	free(sc->aac_commands, M_AACRAIDBUF);

	/* destroy the common area */
	if (sc->aac_common) {
		bus_dmamap_unload(sc->aac_common_dmat, sc->aac_common_dmamap);
		bus_dmamem_free(sc->aac_common_dmat, sc->aac_common,
				sc->aac_common_dmamap);
	}
	if (sc->aac_common_dmat)
		bus_dma_tag_destroy(sc->aac_common_dmat);

	/* disconnect the interrupt handler */
	for (i = 0; i < AAC_MAX_MSIX; ++i) {	
		if (sc->aac_intr[i])
			bus_teardown_intr(sc->aac_dev, 
				sc->aac_irq[i], sc->aac_intr[i]);
		if (sc->aac_irq[i])
			bus_release_resource(sc->aac_dev, SYS_RES_IRQ, 
				sc->aac_irq_rid[i], sc->aac_irq[i]);
		else
			break;
	}
	if (sc->msi_enabled || sc->msi_tupelo)
		pci_release_msi(sc->aac_dev);

	/* destroy data-transfer DMA tag */
	if (sc->aac_buffer_dmat)
		bus_dma_tag_destroy(sc->aac_buffer_dmat);

	/* destroy the parent DMA tag */
	if (sc->aac_parent_dmat)
		bus_dma_tag_destroy(sc->aac_parent_dmat);

	/* release the register window mapping */
	if (sc->aac_regs_res0 != NULL)
		bus_release_resource(sc->aac_dev, SYS_RES_MEMORY,
				     sc->aac_regs_rid0, sc->aac_regs_res0);
	if (sc->aac_regs_res1 != NULL)
		bus_release_resource(sc->aac_dev, SYS_RES_MEMORY,
				     sc->aac_regs_rid1, sc->aac_regs_res1);
}