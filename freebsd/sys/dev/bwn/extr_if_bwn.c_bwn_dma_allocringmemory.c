#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_dma {int /*<<< orphan*/  parent_dtag; } ;
struct TYPE_2__ {struct bwn_dma dma; } ;
struct bwn_mac {struct bwn_softc* mac_sc; TYPE_1__ mac_method; } ;
struct bwn_dma_ring {int /*<<< orphan*/  dr_ring_dmabase; int /*<<< orphan*/  dr_ring_descbase; int /*<<< orphan*/  dr_ring_dmap; int /*<<< orphan*/  dr_ring_dtag; struct bwn_mac* dr_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  BWN_ALIGN ; 
 int /*<<< orphan*/  BWN_DMA_RINGMEMSIZE ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bwn_dma_ring_addr ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bwn_dma_allocringmemory(struct bwn_dma_ring *dr)
{
	struct bwn_mac *mac = dr->dr_mac;
	struct bwn_dma *dma = &mac->mac_method.dma;
	struct bwn_softc *sc = mac->mac_sc;
	int error;

	error = bus_dma_tag_create(dma->parent_dtag,
			    BWN_ALIGN, 0,
			    BUS_SPACE_MAXADDR,
			    BUS_SPACE_MAXADDR,
			    NULL, NULL,
			    BWN_DMA_RINGMEMSIZE,
			    1,
			    BUS_SPACE_MAXSIZE_32BIT,
			    0,
			    NULL, NULL,
			    &dr->dr_ring_dtag);
	if (error) {
		device_printf(sc->sc_dev,
		    "can't create TX ring DMA tag: TODO frees\n");
		return (-1);
	}

	error = bus_dmamem_alloc(dr->dr_ring_dtag,
	    &dr->dr_ring_descbase, BUS_DMA_WAITOK | BUS_DMA_ZERO,
	    &dr->dr_ring_dmap);
	if (error) {
		device_printf(sc->sc_dev,
		    "can't allocate DMA mem: TODO frees\n");
		return (-1);
	}
	error = bus_dmamap_load(dr->dr_ring_dtag, dr->dr_ring_dmap,
	    dr->dr_ring_descbase, BWN_DMA_RINGMEMSIZE,
	    bwn_dma_ring_addr, &dr->dr_ring_dmabase, BUS_DMA_NOWAIT);
	if (error) {
		device_printf(sc->sc_dev,
		    "can't load DMA mem: TODO free\n");
		return (-1);
	}

	return (0);
}