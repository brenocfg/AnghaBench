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
struct cesa_softc {int /*<<< orphan*/  sc_data_dtag; int /*<<< orphan*/  sc_free_sdesc; int /*<<< orphan*/  sc_free_tdesc; } ;
struct cesa_request {scalar_t__ cr_dmap_loaded; int /*<<< orphan*/  cr_dmap; int /*<<< orphan*/  cr_sdesc; int /*<<< orphan*/  cr_tdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_GENERIC_FREE_LOCKED (struct cesa_softc*,struct cesa_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CESA_LOCK (struct cesa_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CESA_UNLOCK (struct cesa_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_CONCAT (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  requests ; 
 int /*<<< orphan*/  sdesc ; 
 int /*<<< orphan*/  tdesc ; 

__attribute__((used)) static void
cesa_free_request(struct cesa_softc *sc, struct cesa_request *cr)
{

	/* Free TDMA descriptors assigned to this request */
	CESA_LOCK(sc, tdesc);
	STAILQ_CONCAT(&sc->sc_free_tdesc, &cr->cr_tdesc);
	CESA_UNLOCK(sc, tdesc);

	/* Free SA descriptors assigned to this request */
	CESA_LOCK(sc, sdesc);
	STAILQ_CONCAT(&sc->sc_free_sdesc, &cr->cr_sdesc);
	CESA_UNLOCK(sc, sdesc);

	/* Unload DMA memory associated with request */
	if (cr->cr_dmap_loaded) {
		bus_dmamap_unload(sc->sc_data_dtag, cr->cr_dmap);
		cr->cr_dmap_loaded = 0;
	}

	CESA_GENERIC_FREE_LOCKED(sc, cr, requests);
}