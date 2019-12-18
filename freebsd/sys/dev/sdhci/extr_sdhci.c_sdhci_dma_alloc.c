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
struct sdhci_slot {int quirks; scalar_t__ paddr; int /*<<< orphan*/  dmatag; int /*<<< orphan*/  dmamap; scalar_t__ dmamem; int /*<<< orphan*/  sdma_bbufsz; int /*<<< orphan*/  bus; int /*<<< orphan*/  sdma_boundary; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int EFAULT ; 
 int MAXPHYS ; 
 int /*<<< orphan*/  SDHCI_BLKSZ_SDMA_BNDRY_128K ; 
 int /*<<< orphan*/  SDHCI_BLKSZ_SDMA_BNDRY_16K ; 
 int /*<<< orphan*/  SDHCI_BLKSZ_SDMA_BNDRY_256K ; 
 int /*<<< orphan*/  SDHCI_BLKSZ_SDMA_BNDRY_32K ; 
 int /*<<< orphan*/  SDHCI_BLKSZ_SDMA_BNDRY_4K ; 
 int /*<<< orphan*/  SDHCI_BLKSZ_SDMA_BNDRY_512K ; 
 int /*<<< orphan*/  SDHCI_BLKSZ_SDMA_BNDRY_64K ; 
 int /*<<< orphan*/  SDHCI_BLKSZ_SDMA_BNDRY_8K ; 
 int SDHCI_QUIRK_BROKEN_SDMA_BOUNDARY ; 
 int /*<<< orphan*/  SDHCI_SDMA_BNDRY_TO_BBUFSZ (int /*<<< orphan*/ ) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_getaddr ; 
 int /*<<< orphan*/  slot_printf (struct sdhci_slot*,char*) ; 

__attribute__((used)) static int
sdhci_dma_alloc(struct sdhci_slot *slot)
{
	int err;

	if (!(slot->quirks & SDHCI_QUIRK_BROKEN_SDMA_BOUNDARY)) {
		if (MAXPHYS <= 1024 * 4)
			slot->sdma_boundary = SDHCI_BLKSZ_SDMA_BNDRY_4K;
		else if (MAXPHYS <= 1024 * 8)
			slot->sdma_boundary = SDHCI_BLKSZ_SDMA_BNDRY_8K;
		else if (MAXPHYS <= 1024 * 16)
			slot->sdma_boundary = SDHCI_BLKSZ_SDMA_BNDRY_16K;
		else if (MAXPHYS <= 1024 * 32)
			slot->sdma_boundary = SDHCI_BLKSZ_SDMA_BNDRY_32K;
		else if (MAXPHYS <= 1024 * 64)
			slot->sdma_boundary = SDHCI_BLKSZ_SDMA_BNDRY_64K;
		else if (MAXPHYS <= 1024 * 128)
			slot->sdma_boundary = SDHCI_BLKSZ_SDMA_BNDRY_128K;
		else if (MAXPHYS <= 1024 * 256)
			slot->sdma_boundary = SDHCI_BLKSZ_SDMA_BNDRY_256K;
		else
			slot->sdma_boundary = SDHCI_BLKSZ_SDMA_BNDRY_512K;
	}
	slot->sdma_bbufsz = SDHCI_SDMA_BNDRY_TO_BBUFSZ(slot->sdma_boundary);

	/*
	 * Allocate the DMA tag for an SDMA bounce buffer.
	 * Note that the SDHCI specification doesn't state any alignment
	 * constraint for the SDMA system address.  However, controllers
	 * typically ignore the SDMA boundary bits in SDHCI_DMA_ADDRESS when
	 * forming the actual address of data, requiring the SDMA buffer to
	 * be aligned to the SDMA boundary.
	 */
	err = bus_dma_tag_create(bus_get_dma_tag(slot->bus), slot->sdma_bbufsz,
	    0, BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    slot->sdma_bbufsz, 1, slot->sdma_bbufsz, BUS_DMA_ALLOCNOW,
	    NULL, NULL, &slot->dmatag);
	if (err != 0) {
		slot_printf(slot, "Can't create DMA tag for SDMA\n");
		return (err);
	}
	/* Allocate DMA memory for the SDMA bounce buffer. */
	err = bus_dmamem_alloc(slot->dmatag, (void **)&slot->dmamem,
	    BUS_DMA_NOWAIT, &slot->dmamap);
	if (err != 0) {
		slot_printf(slot, "Can't alloc DMA memory for SDMA\n");
		bus_dma_tag_destroy(slot->dmatag);
		return (err);
	}
	/* Map the memory of the SDMA bounce buffer. */
	err = bus_dmamap_load(slot->dmatag, slot->dmamap,
	    (void *)slot->dmamem, slot->sdma_bbufsz, sdhci_getaddr,
	    &slot->paddr, 0);
	if (err != 0 || slot->paddr == 0) {
		slot_printf(slot, "Can't load DMA memory for SDMA\n");
		bus_dmamem_free(slot->dmatag, slot->dmamem, slot->dmamap);
		bus_dma_tag_destroy(slot->dmatag);
		if (err)
			return (err);
		else
			return (EFAULT);
	}

	return (0);
}