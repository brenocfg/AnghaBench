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
struct xdmatest_softc {int /*<<< orphan*/  dst_dma_tag; int /*<<< orphan*/  dst_dma_map; int /*<<< orphan*/  dst; int /*<<< orphan*/  src_dma_tag; int /*<<< orphan*/  src_dma_map; int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xdmatest_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xdmatest_detach(device_t dev)
{
	struct xdmatest_softc *sc;

	sc = device_get_softc(dev);

	bus_dmamap_unload(sc->src_dma_tag, sc->src_dma_map);
	bus_dmamem_free(sc->src_dma_tag, sc->src, sc->src_dma_map);
	bus_dma_tag_destroy(sc->src_dma_tag);

	bus_dmamap_unload(sc->dst_dma_tag, sc->dst_dma_map);
	bus_dmamem_free(sc->dst_dma_tag, sc->dst, sc->dst_dma_map);
	bus_dma_tag_destroy(sc->dst_dma_tag);

	return (0);
}