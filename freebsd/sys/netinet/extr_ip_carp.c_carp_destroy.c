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
struct ifnet {struct carp_if* if_carp; } ;
struct carp_softc {struct carp_softc* sc_ifas; int /*<<< orphan*/  sc_md6_tmo; int /*<<< orphan*/  sc_md_tmo; int /*<<< orphan*/  sc_ad_tmo; scalar_t__ sc_suppress; struct ifnet* sc_carpdev; } ;
struct carp_if {int /*<<< orphan*/  cif_vrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARP_LOCK_DESTROY (struct carp_softc*) ; 
 int /*<<< orphan*/  CARP_UNLOCK (struct carp_softc*) ; 
 int /*<<< orphan*/  CIF_LOCK (struct carp_if*) ; 
 int /*<<< orphan*/  CIF_UNLOCK (struct carp_if*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct carp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_CARP ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct carp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_carp_ifdown_adj ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carp_demote_adj (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  carp_mtx ; 
 int /*<<< orphan*/  carp_sx ; 
 int /*<<< orphan*/  free (struct carp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc_list ; 
 int /*<<< orphan*/  sc_next ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
carp_destroy(struct carp_softc *sc)
{
	struct ifnet *ifp = sc->sc_carpdev;
	struct carp_if *cif = ifp->if_carp;

	sx_assert(&carp_sx, SA_XLOCKED);

	if (sc->sc_suppress)
		carp_demote_adj(-V_carp_ifdown_adj, "vhid removed");
	CARP_UNLOCK(sc);

	CIF_LOCK(cif);
	TAILQ_REMOVE(&cif->cif_vrs, sc, sc_list);
	CIF_UNLOCK(cif);

	mtx_lock(&carp_mtx);
	LIST_REMOVE(sc, sc_next);
	mtx_unlock(&carp_mtx);

	callout_drain(&sc->sc_ad_tmo);
#ifdef INET
	callout_drain(&sc->sc_md_tmo);
#endif
#ifdef INET6
	callout_drain(&sc->sc_md6_tmo);
#endif
	CARP_LOCK_DESTROY(sc);

	free(sc->sc_ifas, M_CARP);
	free(sc, M_CARP);
}