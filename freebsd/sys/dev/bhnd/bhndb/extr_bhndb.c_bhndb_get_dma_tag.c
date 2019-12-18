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
struct bhndb_softc {int /*<<< orphan*/  parent_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bus_dma_tag_t
bhndb_get_dma_tag(device_t dev, device_t child)
{
	struct bhndb_softc *sc = device_get_softc(dev);

	/*
	 * A bridge may have multiple DMA translation descriptors, each with
	 * their own incompatible restrictions; drivers should in general call
	 * BHND_BUS_GET_DMA_TRANSLATION() to fetch both the best available DMA
	 * translation, and its corresponding DMA tag.
	 *
	 * Child drivers that do not use BHND_BUS_GET_DMA_TRANSLATION() are
	 * responsible for creating their own restricted DMA tag; since we
	 * cannot do this for them in BUS_GET_DMA_TAG(), we simply return the
	 * bridge parent's DMA tag directly; 
	 */
	return (bus_get_dma_tag(sc->parent_dev));
}