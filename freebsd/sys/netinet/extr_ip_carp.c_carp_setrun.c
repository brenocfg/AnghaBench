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
struct timeval {int tv_sec; int tv_usec; } ;
struct carp_softc {scalar_t__ sc_naddrs; scalar_t__ sc_naddrs6; int sc_state; int sc_advbase; int sc_advskew; int /*<<< orphan*/  sc_ad_tmo; int /*<<< orphan*/  sc_md6_tmo; int /*<<< orphan*/  sc_md_tmo; TYPE_1__* sc_carpdev; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
struct TYPE_2__ {int if_flags; scalar_t__ if_link_state; } ;

/* Variables and functions */
#define  AF_INET 132 
#define  AF_INET6 131 
#define  BACKUP 130 
 int /*<<< orphan*/  CARP_LOCK_ASSERT (struct carp_softc*) ; 
 int IFF_UP ; 
#define  INIT 129 
 scalar_t__ LINK_STATE_UP ; 
#define  MASTER 128 
 int /*<<< orphan*/  V_carp_allow ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct carp_softc*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carp_master_down ; 
 int /*<<< orphan*/  carp_send_ad ; 
 int /*<<< orphan*/  carp_set_state (struct carp_softc*,int,char*) ; 
 int /*<<< orphan*/  tvtohz (struct timeval*) ; 

__attribute__((used)) static void
carp_setrun(struct carp_softc *sc, sa_family_t af)
{
	struct timeval tv;

	CARP_LOCK_ASSERT(sc);

	if ((sc->sc_carpdev->if_flags & IFF_UP) == 0 ||
	    sc->sc_carpdev->if_link_state != LINK_STATE_UP ||
	    (sc->sc_naddrs == 0 && sc->sc_naddrs6 == 0) ||
	    !V_carp_allow)
		return;

	switch (sc->sc_state) {
	case INIT:
		carp_set_state(sc, BACKUP, "initialization complete");
		carp_setrun(sc, 0);
		break;
	case BACKUP:
		callout_stop(&sc->sc_ad_tmo);
		tv.tv_sec = 3 * sc->sc_advbase;
		tv.tv_usec = sc->sc_advskew * 1000000 / 256;
		switch (af) {
#ifdef INET
		case AF_INET:
			callout_reset(&sc->sc_md_tmo, tvtohz(&tv),
			    carp_master_down, sc);
			break;
#endif
#ifdef INET6
		case AF_INET6:
			callout_reset(&sc->sc_md6_tmo, tvtohz(&tv),
			    carp_master_down, sc);
			break;
#endif
		default:
#ifdef INET
			if (sc->sc_naddrs)
				callout_reset(&sc->sc_md_tmo, tvtohz(&tv),
				    carp_master_down, sc);
#endif
#ifdef INET6
			if (sc->sc_naddrs6)
				callout_reset(&sc->sc_md6_tmo, tvtohz(&tv),
				    carp_master_down, sc);
#endif
			break;
		}
		break;
	case MASTER:
		tv.tv_sec = sc->sc_advbase;
		tv.tv_usec = sc->sc_advskew * 1000000 / 256;
		callout_reset(&sc->sc_ad_tmo, tvtohz(&tv),
		    carp_send_ad, sc);
		break;
	}
}