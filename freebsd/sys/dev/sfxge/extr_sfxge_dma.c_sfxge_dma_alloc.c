#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sfxge_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  parent_dma_tag; } ;
struct TYPE_3__ {scalar_t__ esm_addr; int /*<<< orphan*/  esm_tag; int /*<<< orphan*/  esm_map; int /*<<< orphan*/  esm_size; void* esm_base; } ;
typedef  TYPE_1__ efsys_mem_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sfxge_dma_cb ; 

int
sfxge_dma_alloc(struct sfxge_softc *sc, bus_size_t len, efsys_mem_t *esmp)
{
	void *vaddr;

	/* Create the child DMA tag. */
	if (bus_dma_tag_create(sc->parent_dma_tag, PAGE_SIZE, 0,
	    MIN(0x3FFFFFFFFFFFUL, BUS_SPACE_MAXADDR), BUS_SPACE_MAXADDR, NULL,
	    NULL, len, 1, len, 0, NULL, NULL, &esmp->esm_tag) != 0) {
		device_printf(sc->dev, "Couldn't allocate txq DMA tag\n");
		goto fail_tag_create;
	}

	/* Allocate kernel memory. */
	if (bus_dmamem_alloc(esmp->esm_tag, (void **)&vaddr,
	    BUS_DMA_WAITOK | BUS_DMA_COHERENT | BUS_DMA_ZERO,
	    &esmp->esm_map) != 0) {
		device_printf(sc->dev, "Couldn't allocate DMA memory\n");
		goto fail_alloc;
	}

	/* Load map into device memory. */
	if (bus_dmamap_load(esmp->esm_tag, esmp->esm_map, vaddr, len,
	    sfxge_dma_cb, &esmp->esm_addr, 0) != 0) {
		device_printf(sc->dev, "Couldn't load DMA mapping\n");
		goto fail_load;
	}

	/*
	 * The callback gets error information about the mapping
	 * and will have set esm_addr to 0 if something went
	 * wrong.
	 */
	if (esmp->esm_addr == 0)
		goto fail_load_check;

	esmp->esm_base = vaddr;
	esmp->esm_size = len;

	return (0);

fail_load_check:
fail_load:
	bus_dmamem_free(esmp->esm_tag, vaddr, esmp->esm_map);
fail_alloc:
	bus_dma_tag_destroy(esmp->esm_tag);
fail_tag_create:
	return (ENOMEM);
}