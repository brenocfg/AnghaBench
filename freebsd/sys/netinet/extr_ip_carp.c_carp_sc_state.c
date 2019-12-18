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
struct carp_softc {int sc_suppress; int /*<<< orphan*/  sc_md6_tmo; int /*<<< orphan*/  sc_md_tmo; int /*<<< orphan*/  sc_ad_tmo; TYPE_1__* sc_carpdev; } ;
struct TYPE_2__ {scalar_t__ if_link_state; int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARP_LOCK_ASSERT (struct carp_softc*) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  INIT ; 
 scalar_t__ LINK_STATE_UP ; 
 int /*<<< orphan*/  V_carp_allow ; 
 int /*<<< orphan*/  V_carp_ifdown_adj ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carp_demote_adj (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  carp_set_state (struct carp_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  carp_setrun (struct carp_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
carp_sc_state(struct carp_softc *sc)
{

	CARP_LOCK_ASSERT(sc);

	if (sc->sc_carpdev->if_link_state != LINK_STATE_UP ||
	    !(sc->sc_carpdev->if_flags & IFF_UP) ||
	    !V_carp_allow) {
		callout_stop(&sc->sc_ad_tmo);
#ifdef INET
		callout_stop(&sc->sc_md_tmo);
#endif
#ifdef INET6
		callout_stop(&sc->sc_md6_tmo);
#endif
		carp_set_state(sc, INIT, "hardware interface down");
		carp_setrun(sc, 0);
		if (!sc->sc_suppress)
			carp_demote_adj(V_carp_ifdown_adj, "interface down");
		sc->sc_suppress = 1;
	} else {
		carp_set_state(sc, INIT, "hardware interface up");
		carp_setrun(sc, 0);
		if (sc->sc_suppress)
			carp_demote_adj(-V_carp_ifdown_adj, "interface up");
		sc->sc_suppress = 0;
	}
}