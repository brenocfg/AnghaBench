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
struct pfsync_softc {int dummy; } ;
struct pfsync_deferral {struct pf_state* pd_st; struct mbuf* pd_m; struct pfsync_softc* pd_sc; } ;
struct pfsync_bucket {int /*<<< orphan*/  b_snd; int /*<<< orphan*/  b_deferred; int /*<<< orphan*/  b_deferrals; } ;
struct pf_state {int /*<<< orphan*/  state_flags; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PFSYNC ; 
 int /*<<< orphan*/  PFSTATE_ACK ; 
 int /*<<< orphan*/  PFSYNC_BUCKET_LOCK_ASSERT (struct pfsync_bucket*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pfsync_deferral*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _IF_ENQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  free (struct pfsync_deferral*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  pd_entry ; 
 int /*<<< orphan*/  pf_release_state (struct pf_state*) ; 
 struct pfsync_bucket* pfsync_get_bucket (struct pfsync_softc*,struct pf_state*) ; 
 int /*<<< orphan*/  pfsync_push (struct pfsync_bucket*) ; 

__attribute__((used)) static void
pfsync_undefer(struct pfsync_deferral *pd, int drop)
{
	struct pfsync_softc *sc = pd->pd_sc;
	struct mbuf *m = pd->pd_m;
	struct pf_state *st = pd->pd_st;
	struct pfsync_bucket *b = pfsync_get_bucket(sc, st);

	PFSYNC_BUCKET_LOCK_ASSERT(b);

	TAILQ_REMOVE(&b->b_deferrals, pd, pd_entry);
	b->b_deferred--;
	pd->pd_st->state_flags &= ~PFSTATE_ACK;	/* XXX: locking! */
	free(pd, M_PFSYNC);
	pf_release_state(st);

	if (drop)
		m_freem(m);
	else {
		_IF_ENQUEUE(&b->b_snd, m);
		pfsync_push(b);
	}
}