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
struct pfsync_softc {int sc_flags; TYPE_1__* sc_ifp; } ;
struct pfsync_deferral {int /*<<< orphan*/  pd_tmo; struct mbuf* pd_m; struct pf_state* pd_st; scalar_t__ pd_refs; struct pfsync_softc* pd_sc; } ;
struct pfsync_bucket {int b_deferred; int /*<<< orphan*/  b_mtx; int /*<<< orphan*/  b_deferrals; } ;
struct pf_state {int /*<<< orphan*/  state_flags; } ;
struct mbuf {int m_flags; } ;
struct TYPE_2__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLOUT_RETURNUNLOCKED ; 
 int IFF_DRV_RUNNING ; 
 int M_BCAST ; 
 int M_MCAST ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PFSYNC ; 
 int M_SKIP_FIREWALL ; 
 int /*<<< orphan*/  PFSTATE_ACK ; 
 int PFSYNCF_DEFER ; 
 int /*<<< orphan*/  PFSYNC_LOCK (struct pfsync_softc*) ; 
 int /*<<< orphan*/  PFSYNC_UNLOCK (struct pfsync_softc*) ; 
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pfsync_deferral*,int /*<<< orphan*/ ) ; 
 struct pfsync_softc* V_pfsyncif ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct pfsync_deferral*) ; 
 struct pfsync_deferral* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pd_entry ; 
 int /*<<< orphan*/  pf_ref_state (struct pf_state*) ; 
 int /*<<< orphan*/  pfsync_defer_tmo ; 
 struct pfsync_bucket* pfsync_get_bucket (struct pfsync_softc*,struct pf_state*) ; 
 int /*<<< orphan*/  pfsync_push (struct pfsync_bucket*) ; 
 int /*<<< orphan*/  pfsync_undefer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfsync_defer(struct pf_state *st, struct mbuf *m)
{
	struct pfsync_softc *sc = V_pfsyncif;
	struct pfsync_deferral *pd;
	struct pfsync_bucket *b = pfsync_get_bucket(sc, st);

	if (m->m_flags & (M_BCAST|M_MCAST))
		return (0);

	PFSYNC_LOCK(sc);

	if (sc == NULL || !(sc->sc_ifp->if_flags & IFF_DRV_RUNNING) ||
	    !(sc->sc_flags & PFSYNCF_DEFER)) {
		PFSYNC_UNLOCK(sc);
		return (0);
	}

	if (b->b_deferred >= 128)
		pfsync_undefer(TAILQ_FIRST(&b->b_deferrals), 0);

	pd = malloc(sizeof(*pd), M_PFSYNC, M_NOWAIT);
	if (pd == NULL)
		return (0);
	b->b_deferred++;

	m->m_flags |= M_SKIP_FIREWALL;
	st->state_flags |= PFSTATE_ACK;

	pd->pd_sc = sc;
	pd->pd_refs = 0;
	pd->pd_st = st;
	pf_ref_state(st);
	pd->pd_m = m;

	TAILQ_INSERT_TAIL(&b->b_deferrals, pd, pd_entry);
	callout_init_mtx(&pd->pd_tmo, &b->b_mtx, CALLOUT_RETURNUNLOCKED);
	callout_reset(&pd->pd_tmo, 10, pfsync_defer_tmo, pd);

	pfsync_push(b);

	return (1);
}