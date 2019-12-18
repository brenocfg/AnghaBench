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
struct pfsync_softc {scalar_t__ b_deferred; int sc_flags; struct pfsync_softc* sc_buckets; int /*<<< orphan*/  sc_bulk_mtx; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_bulk_tmo; int /*<<< orphan*/  sc_bulkfail_tmo; int /*<<< orphan*/  b_tmo; int /*<<< orphan*/  pd_tmo; int /*<<< orphan*/  pd_refs; int /*<<< orphan*/  pd_m; int /*<<< orphan*/  pd_st; int /*<<< orphan*/  b_deferrals; } ;
struct pfsync_deferral {scalar_t__ b_deferred; int sc_flags; struct pfsync_deferral* sc_buckets; int /*<<< orphan*/  sc_bulk_mtx; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_bulk_tmo; int /*<<< orphan*/  sc_bulkfail_tmo; int /*<<< orphan*/  b_tmo; int /*<<< orphan*/  pd_tmo; int /*<<< orphan*/  pd_refs; int /*<<< orphan*/  pd_m; int /*<<< orphan*/  pd_st; int /*<<< orphan*/  b_deferrals; } ;
struct pfsync_bucket {scalar_t__ b_deferred; int sc_flags; struct pfsync_bucket* sc_buckets; int /*<<< orphan*/  sc_bulk_mtx; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_bulk_tmo; int /*<<< orphan*/  sc_bulkfail_tmo; int /*<<< orphan*/  b_tmo; int /*<<< orphan*/  pd_tmo; int /*<<< orphan*/  pd_refs; int /*<<< orphan*/  pd_m; int /*<<< orphan*/  pd_st; int /*<<< orphan*/  b_deferrals; } ;
struct ifnet {struct pfsync_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PFSYNC ; 
 int PFSYNCF_OK ; 
 struct pfsync_softc* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pfsync_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pfsync_carp_adj ; 
 int /*<<< orphan*/ * V_pfsyncif ; 
 int /*<<< orphan*/  bpfdetach (struct ifnet*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carp_demote_adj_p (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct pfsync_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pd_entry ; 
 int /*<<< orphan*/  pf_release_state (int /*<<< orphan*/ ) ; 
 int pfsync_buckets ; 
 int /*<<< orphan*/  pfsync_drop (struct pfsync_softc*) ; 
 int /*<<< orphan*/  pfsync_multicast_cleanup (struct pfsync_softc*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
pfsync_clone_destroy(struct ifnet *ifp)
{
	struct pfsync_softc *sc = ifp->if_softc;
	struct pfsync_bucket *b;
	int c;

	for (c = 0; c < pfsync_buckets; c++) {
		b = &sc->sc_buckets[c];
		/*
		 * At this stage, everything should have already been
		 * cleared by pfsync_uninit(), and we have only to
		 * drain callouts.
		 */
		while (b->b_deferred > 0) {
			struct pfsync_deferral *pd =
			    TAILQ_FIRST(&b->b_deferrals);

			TAILQ_REMOVE(&b->b_deferrals, pd, pd_entry);
			b->b_deferred--;
			if (callout_stop(&pd->pd_tmo) > 0) {
				pf_release_state(pd->pd_st);
				m_freem(pd->pd_m);
				free(pd, M_PFSYNC);
			} else {
				pd->pd_refs++;
				callout_drain(&pd->pd_tmo);
				free(pd, M_PFSYNC);
			}
		}

		callout_drain(&b->b_tmo);
	}

	callout_drain(&sc->sc_bulkfail_tmo);
	callout_drain(&sc->sc_bulk_tmo);

	if (!(sc->sc_flags & PFSYNCF_OK) && carp_demote_adj_p)
		(*carp_demote_adj_p)(-V_pfsync_carp_adj, "pfsync destroy");
	bpfdetach(ifp);
	if_detach(ifp);

	pfsync_drop(sc);

	if_free(ifp);
	pfsync_multicast_cleanup(sc);
	mtx_destroy(&sc->sc_mtx);
	mtx_destroy(&sc->sc_bulk_mtx);

	free(sc->sc_buckets, M_PFSYNC);
	free(sc, M_PFSYNC);

	V_pfsyncif = NULL;
}