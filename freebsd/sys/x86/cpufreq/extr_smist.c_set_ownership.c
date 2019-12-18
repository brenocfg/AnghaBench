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
struct smist_softc {int /*<<< orphan*/  command; int /*<<< orphan*/  smi_cmd; } ;
struct set_ownership_data {scalar_t__ result; int /*<<< orphan*/  buf; int /*<<< orphan*/  command; int /*<<< orphan*/  smi_cmd; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct set_ownership_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 struct smist_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_ownership_cb ; 

__attribute__((used)) static int
set_ownership(device_t dev)
{
	struct smist_softc *sc;
	struct set_ownership_data cb_data;
	bus_dma_tag_t tag;
	bus_dmamap_t map;

	/*
	 * Specify the region to store the magic string.  Since its address is
	 * passed to the BIOS in a 32-bit register, we have to make sure it is
	 * located in a physical page below 4 GB (i.e., for PAE.)
	 */
	sc = device_get_softc(dev);
	if (bus_dma_tag_create(/*parent*/ NULL,
	    /*alignment*/ PAGE_SIZE, /*no boundary*/ 0,
	    /*lowaddr*/ BUS_SPACE_MAXADDR_32BIT, /*highaddr*/ BUS_SPACE_MAXADDR,
	    NULL, NULL, /*maxsize*/ PAGE_SIZE, /*segments*/ 1,
	    /*maxsegsize*/ PAGE_SIZE, 0, busdma_lock_mutex, &Giant,
	    &tag) != 0) {
		device_printf(dev, "can't create mem tag\n");
		return (ENXIO);
	}
	if (bus_dmamem_alloc(tag, &cb_data.buf, BUS_DMA_NOWAIT, &map) != 0) {
		bus_dma_tag_destroy(tag);
		device_printf(dev, "can't alloc mapped mem\n");
		return (ENXIO);
	}

	/* Load the physical page map and take ownership in the callback. */
	cb_data.smi_cmd = sc->smi_cmd;
	cb_data.command = sc->command;
	if (bus_dmamap_load(tag, map, cb_data.buf, PAGE_SIZE, set_ownership_cb,
	    &cb_data, BUS_DMA_NOWAIT) != 0) {
		bus_dmamem_free(tag, cb_data.buf, map);
		bus_dma_tag_destroy(tag);
		device_printf(dev, "can't load mem\n");
		return (ENXIO);
	}
	DPRINT(dev, "taking ownership over BIOS return %d\n", cb_data.result);
	bus_dmamap_unload(tag, map);
	bus_dmamem_free(tag, cb_data.buf, map);
	bus_dma_tag_destroy(tag);
	return (cb_data.result ? ENXIO : 0);
}