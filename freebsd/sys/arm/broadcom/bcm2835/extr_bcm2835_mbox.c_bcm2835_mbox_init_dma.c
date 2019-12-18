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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  bcm2835_mbox_dma_cb ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void *
bcm2835_mbox_init_dma(device_t dev, size_t len, bus_dma_tag_t *tag,
    bus_dmamap_t *map, bus_addr_t *phys)
{
	void *buf;
	int err;

	err = bus_dma_tag_create(bus_get_dma_tag(dev), 16, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    len, 1, len, 0, NULL, NULL, tag);
	if (err != 0) {
		device_printf(dev, "can't create DMA tag\n");
		return (NULL);
	}

	err = bus_dmamem_alloc(*tag, &buf, 0, map);
	if (err != 0) {
		bus_dma_tag_destroy(*tag);
		device_printf(dev, "can't allocate dmamem\n");
		return (NULL);
	}

	err = bus_dmamap_load(*tag, *map, buf, len, bcm2835_mbox_dma_cb,
	    phys, 0);
	if (err != 0) {
		bus_dmamem_free(*tag, buf, *map);
		bus_dma_tag_destroy(*tag);
		device_printf(dev, "can't load DMA map\n");
		return (NULL);
	}

	return (buf);
}