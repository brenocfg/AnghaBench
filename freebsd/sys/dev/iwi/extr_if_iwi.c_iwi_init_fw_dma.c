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
struct iwi_softc {int fw_dma_size; int /*<<< orphan*/  fw_flags; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  fw_physaddr; int /*<<< orphan*/  fw_virtaddr; int /*<<< orphan*/  fw_map; int /*<<< orphan*/  fw_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  IWI_FW_HAVE_DMAT ; 
 int /*<<< orphan*/  IWI_FW_HAVE_MAP ; 
 int /*<<< orphan*/  IWI_FW_HAVE_PHY ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iwi_dma_map_addr ; 
 int /*<<< orphan*/  iwi_release_fw_dma (struct iwi_softc*) ; 

__attribute__((used)) static int
iwi_init_fw_dma(struct iwi_softc *sc, int size)
{
	if (sc->fw_dma_size >= size)
		return 0;
	if (bus_dma_tag_create(bus_get_dma_tag(sc->sc_dev), 4, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    size, 1, size, 0, NULL, NULL, &sc->fw_dmat) != 0) {
		device_printf(sc->sc_dev,
		    "could not create firmware DMA tag\n");
		goto error;
	}
	sc->fw_flags |= IWI_FW_HAVE_DMAT;
	if (bus_dmamem_alloc(sc->fw_dmat, &sc->fw_virtaddr, 0,
	    &sc->fw_map) != 0) {
		device_printf(sc->sc_dev,
		    "could not allocate firmware DMA memory\n");
		goto error;
	}
	sc->fw_flags |= IWI_FW_HAVE_MAP;
	if (bus_dmamap_load(sc->fw_dmat, sc->fw_map, sc->fw_virtaddr,
	    size, iwi_dma_map_addr, &sc->fw_physaddr, 0) != 0) {
		device_printf(sc->sc_dev, "could not load firmware DMA map\n");
		goto error;
	}
	sc->fw_flags |= IWI_FW_HAVE_PHY;
	sc->fw_dma_size = size;
	return 0;

error:
	iwi_release_fw_dma(sc);
	return 1;
}