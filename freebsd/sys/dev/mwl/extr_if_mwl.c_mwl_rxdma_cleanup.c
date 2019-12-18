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
struct TYPE_2__ {scalar_t__ dd_desc_len; int /*<<< orphan*/ * dd_bufptr; } ;
struct mwl_softc {scalar_t__ sc_rxmem_paddr; TYPE_1__ sc_rxdma; int /*<<< orphan*/ * sc_rxmem; int /*<<< orphan*/  sc_rxmap; int /*<<< orphan*/  sc_rxdmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MWLDEV ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl_desc_cleanup (struct mwl_softc*,TYPE_1__*) ; 

__attribute__((used)) static void
mwl_rxdma_cleanup(struct mwl_softc *sc)
{
	if (sc->sc_rxmem_paddr != 0) {
		bus_dmamap_unload(sc->sc_rxdmat, sc->sc_rxmap);
		sc->sc_rxmem_paddr = 0;
	}
	if (sc->sc_rxmem != NULL) {
		bus_dmamem_free(sc->sc_rxdmat, sc->sc_rxmem, sc->sc_rxmap);
		sc->sc_rxmem = NULL;
	}
	if (sc->sc_rxdma.dd_bufptr != NULL) {
		free(sc->sc_rxdma.dd_bufptr, M_MWLDEV);
		sc->sc_rxdma.dd_bufptr = NULL;
	}
	if (sc->sc_rxdma.dd_desc_len != 0)
		mwl_desc_cleanup(sc, &sc->sc_rxdma);
}