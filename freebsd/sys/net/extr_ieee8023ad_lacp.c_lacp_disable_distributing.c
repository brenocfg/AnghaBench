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
struct lagg_softc {scalar_t__ sc_active; int /*<<< orphan*/  sc_ifp; } ;
struct lacp_softc {struct lacp_aggregator* lsc_active_aggregator; struct lagg_softc* lsc_softc; } ;
struct lacp_port {int lp_state; struct lacp_softc* lp_lsc; struct lacp_aggregator* lp_aggregator; } ;
struct lacp_aggregator {scalar_t__ la_nports; scalar_t__ la_refcnt; int /*<<< orphan*/  la_ports; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LACP_DPRINTF (struct lacp_port*) ; 
 int /*<<< orphan*/  LACP_LAGIDSTR_MAX ; 
 int /*<<< orphan*/  LACP_LOCK_ASSERT (struct lacp_softc*) ; 
 int LACP_STATE_DISTRIBUTING ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct lacp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lacp_format_lagid_aggregator (struct lacp_aggregator*,char*,int) ; 
 int /*<<< orphan*/  lacp_select_active_aggregator (struct lacp_softc*) ; 
 int /*<<< orphan*/  lacp_suppress_distributing (struct lacp_softc*,struct lacp_aggregator*) ; 
 int /*<<< orphan*/  lacp_update_portmap (struct lacp_softc*) ; 
 int /*<<< orphan*/  lp_dist_q ; 

__attribute__((used)) static void
lacp_disable_distributing(struct lacp_port *lp)
{
	struct lacp_aggregator *la = lp->lp_aggregator;
	struct lacp_softc *lsc = lp->lp_lsc;
	struct lagg_softc *sc = lsc->lsc_softc;
	char buf[LACP_LAGIDSTR_MAX+1];

	LACP_LOCK_ASSERT(lsc);

	if (la == NULL || (lp->lp_state & LACP_STATE_DISTRIBUTING) == 0) {
		return;
	}

	KASSERT(!TAILQ_EMPTY(&la->la_ports), ("no aggregator ports"));
	KASSERT(la->la_nports > 0, ("nports invalid (%d)", la->la_nports));
	KASSERT(la->la_refcnt >= la->la_nports, ("aggregator refcnt invalid"));

	LACP_DPRINTF((lp, "disable distributing on aggregator %s, "
	    "nports %d -> %d\n",
	    lacp_format_lagid_aggregator(la, buf, sizeof(buf)),
	    la->la_nports, la->la_nports - 1));

	TAILQ_REMOVE(&la->la_ports, lp, lp_dist_q);
	la->la_nports--;
	sc->sc_active = la->la_nports;

	if (lsc->lsc_active_aggregator == la) {
		lacp_suppress_distributing(lsc, la);
		lacp_select_active_aggregator(lsc);
		/* regenerate the port map, the active aggregator has changed */
		lacp_update_portmap(lsc);
	}

	lp->lp_state &= ~LACP_STATE_DISTRIBUTING;
	if_link_state_change(sc->sc_ifp,
	    sc->sc_active ? LINK_STATE_UP : LINK_STATE_DOWN);
}