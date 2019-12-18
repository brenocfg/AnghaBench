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
struct iwi_softc {int fw_flags; int /*<<< orphan*/ * fw_virtaddr; scalar_t__ fw_physaddr; int /*<<< orphan*/ * fw_map; int /*<<< orphan*/ * fw_dmat; scalar_t__ fw_dma_size; } ;

/* Variables and functions */
 int IWI_FW_HAVE_DMAT ; 
 int IWI_FW_HAVE_MAP ; 
 int IWI_FW_HAVE_PHY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iwi_release_fw_dma(struct iwi_softc *sc)
{
	if (sc->fw_flags & IWI_FW_HAVE_PHY)
		bus_dmamap_unload(sc->fw_dmat, sc->fw_map);
	if (sc->fw_flags & IWI_FW_HAVE_MAP)
		bus_dmamem_free(sc->fw_dmat, sc->fw_virtaddr, sc->fw_map);
	if (sc->fw_flags & IWI_FW_HAVE_DMAT)
		bus_dma_tag_destroy(sc->fw_dmat);

	sc->fw_flags = 0;
	sc->fw_dma_size = 0;
	sc->fw_dmat = NULL;
	sc->fw_map = NULL;
	sc->fw_physaddr = 0;
	sc->fw_virtaddr = NULL;
}