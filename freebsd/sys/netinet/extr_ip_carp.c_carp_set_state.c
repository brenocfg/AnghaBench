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
struct carp_softc {int sc_state; int sc_vhid; TYPE_1__* sc_carpdev; } ;
struct TYPE_2__ {char* if_xname; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARP_LOCK_ASSERT (struct carp_softc*) ; 
 int /*<<< orphan*/  CARP_LOG (char*,char*,char const*,char const*,char const*) ; 
 char const* CARP_STATES ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  devctl_notify (char*,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 

__attribute__((used)) static void
carp_set_state(struct carp_softc *sc, int state, const char *reason)
{

	CARP_LOCK_ASSERT(sc);

	if (sc->sc_state != state) {
		const char *carp_states[] = { CARP_STATES };
		char subsys[IFNAMSIZ+5];

		snprintf(subsys, IFNAMSIZ+5, "%u@%s", sc->sc_vhid,
		    sc->sc_carpdev->if_xname);

		CARP_LOG("%s: %s -> %s (%s)\n", subsys,
		    carp_states[sc->sc_state], carp_states[state], reason);

		sc->sc_state = state;

		devctl_notify("CARP", subsys, carp_states[state], NULL);
	}
}