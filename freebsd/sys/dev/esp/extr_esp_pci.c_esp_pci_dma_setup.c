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
struct ncr53c9x_softc {int dummy; } ;
struct esp_pci_softc {size_t sc_dmasize; void** sc_dmaaddr; size_t* sc_dmalen; int sc_datain; int /*<<< orphan*/  sc_xferdmam; int /*<<< orphan*/  sc_xferdmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 size_t DMACMD_DIR ; 
 size_t DMACMD_IDLE ; 
 int /*<<< orphan*/  DMA_CMD ; 
 int /*<<< orphan*/  DMA_STC ; 
 int /*<<< orphan*/  MDL_SEG_SIZE ; 
 int /*<<< orphan*/  WRITE_DMAREG (struct esp_pci_softc*,int /*<<< orphan*/ ,size_t) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_pci_xfermap ; 
 size_t ulmin (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
esp_pci_dma_setup(struct ncr53c9x_softc *sc, void **addr, size_t *len,
    int datain, size_t *dmasize)
{
	struct esp_pci_softc *esc = (struct esp_pci_softc *)sc;
	int error;

	WRITE_DMAREG(esc, DMA_CMD, DMACMD_IDLE | (datain != 0 ? DMACMD_DIR :
	    0));

	*dmasize = esc->sc_dmasize = ulmin(*dmasize, MDL_SEG_SIZE);
	esc->sc_dmaaddr = addr;
	esc->sc_dmalen = len;
	esc->sc_datain = datain;

	/*
	 * There's no need to set up DMA for a "Transfer Pad" operation.
	 */
	if (*dmasize == 0)
		return (0);

	/* Set the transfer length. */
	WRITE_DMAREG(esc, DMA_STC, *dmasize);

	/*
	 * Load the transfer buffer and program the DMA address.
	 * Note that the NCR53C9x core can't handle EINPROGRESS so we set
	 * BUS_DMA_NOWAIT.
	 */
	error = bus_dmamap_load(esc->sc_xferdmat, esc->sc_xferdmam,
	    *esc->sc_dmaaddr, *dmasize, esp_pci_xfermap, sc, BUS_DMA_NOWAIT);

	return (error);
}