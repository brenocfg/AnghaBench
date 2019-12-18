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
struct pfsync_softc {int sc_bulk_hashid; scalar_t__ sc_ureq_received; int /*<<< orphan*/  sc_bulk_tmo; int /*<<< orphan*/  sc_bulk_creatorid; int /*<<< orphan*/  sc_bulk_stateid; TYPE_1__* sc_ifp; } ;
struct pf_state {scalar_t__ sync_state; scalar_t__ timeout; scalar_t__ pfsync_time; int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; } ;
struct pf_idhash {int /*<<< orphan*/  states; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 struct pf_state* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct pf_state* LIST_NEXT (struct pf_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PFSYNC_BLOCK_ASSERT (struct pfsync_softc*) ; 
 int /*<<< orphan*/  PFSYNC_BUS_END ; 
 scalar_t__ PFSYNC_S_NONE ; 
 scalar_t__ PFTM_MAX ; 
 int /*<<< orphan*/  PF_HASHROW_ASSERT (struct pf_idhash*) ; 
 int /*<<< orphan*/  PF_HASHROW_LOCK (struct pf_idhash*) ; 
 int /*<<< orphan*/  PF_HASHROW_UNLOCK (struct pf_idhash*) ; 
 int PF_IDHASH (struct pf_state*) ; 
 struct pf_idhash* V_pf_idhash ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct pfsync_softc*) ; 
 int /*<<< orphan*/  entry ; 
 struct pf_state* pf_find_state_byid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pf_hashmask ; 
 int /*<<< orphan*/  pfsync_bulk_status (int /*<<< orphan*/ ) ; 
 scalar_t__ pfsync_update_state_req (struct pf_state*) ; 

__attribute__((used)) static void
pfsync_bulk_update(void *arg)
{
	struct pfsync_softc *sc = arg;
	struct pf_state *s;
	int i, sent = 0;

	PFSYNC_BLOCK_ASSERT(sc);
	CURVNET_SET(sc->sc_ifp->if_vnet);

	/*
	 * Start with last state from previous invocation.
	 * It may had gone, in this case start from the
	 * hash slot.
	 */
	s = pf_find_state_byid(sc->sc_bulk_stateid, sc->sc_bulk_creatorid);

	if (s != NULL)
		i = PF_IDHASH(s);
	else
		i = sc->sc_bulk_hashid;

	for (; i <= pf_hashmask; i++) {
		struct pf_idhash *ih = &V_pf_idhash[i];

		if (s != NULL)
			PF_HASHROW_ASSERT(ih);
		else {
			PF_HASHROW_LOCK(ih);
			s = LIST_FIRST(&ih->states);
		}

		for (; s; s = LIST_NEXT(s, entry)) {
			if (s->sync_state == PFSYNC_S_NONE &&
			    s->timeout < PFTM_MAX &&
			    s->pfsync_time <= sc->sc_ureq_received) {
				if (pfsync_update_state_req(s)) {
					/* We've filled a packet. */
					sc->sc_bulk_hashid = i;
					sc->sc_bulk_stateid = s->id;
					sc->sc_bulk_creatorid = s->creatorid;
					PF_HASHROW_UNLOCK(ih);
					callout_reset(&sc->sc_bulk_tmo, 1,
					    pfsync_bulk_update, sc);
					goto full;
				}
				sent++;
			}
		}
		PF_HASHROW_UNLOCK(ih);
	}

	/* We're done. */
	pfsync_bulk_status(PFSYNC_BUS_END);
full:
	CURVNET_RESTORE();
}