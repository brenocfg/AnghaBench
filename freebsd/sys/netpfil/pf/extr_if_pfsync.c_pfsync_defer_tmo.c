#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pfsync_softc {int dummy; } ;
struct pfsync_deferral {scalar_t__ pd_refs; struct pf_state* pd_st; struct mbuf* pd_m; struct pfsync_softc* pd_sc; } ;
struct pfsync_bucket {int /*<<< orphan*/  b_deferred; int /*<<< orphan*/  b_deferrals; } ;
struct pf_state {int /*<<< orphan*/  state_flags; } ;
struct TYPE_4__ {TYPE_1__* rcvif; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PFSYNC ; 
 int /*<<< orphan*/  PFSTATE_ACK ; 
 int /*<<< orphan*/  PFSYNC_BUCKET_LOCK_ASSERT (struct pfsync_bucket*) ; 
 int /*<<< orphan*/  PFSYNC_UNLOCK (struct pfsync_softc*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pfsync_deferral*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pfsync_deferral*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_output (struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pd_entry ; 
 int /*<<< orphan*/  pf_release_state (struct pf_state*) ; 
 struct pfsync_bucket* pfsync_get_bucket (struct pfsync_softc*,struct pf_state*) ; 

__attribute__((used)) static void
pfsync_defer_tmo(void *arg)
{
	struct pfsync_deferral *pd = arg;
	struct pfsync_softc *sc = pd->pd_sc;
	struct mbuf *m = pd->pd_m;
	struct pf_state *st = pd->pd_st;
	struct pfsync_bucket *b = pfsync_get_bucket(sc, st);

	PFSYNC_BUCKET_LOCK_ASSERT(b);

	CURVNET_SET(m->m_pkthdr.rcvif->if_vnet);

	TAILQ_REMOVE(&b->b_deferrals, pd, pd_entry);
	b->b_deferred--;
	pd->pd_st->state_flags &= ~PFSTATE_ACK;	/* XXX: locking! */
	if (pd->pd_refs == 0)
		free(pd, M_PFSYNC);
	PFSYNC_UNLOCK(sc);

	ip_output(m, NULL, NULL, 0, NULL, NULL);

	pf_release_state(st);

	CURVNET_RESTORE();
}