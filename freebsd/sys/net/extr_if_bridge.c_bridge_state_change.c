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
struct ifnet {int /*<<< orphan*/  if_xname; int /*<<< orphan*/  if_vnet; struct bridge_softc* if_bridge; } ;
struct bridge_softc {TYPE_1__* sc_ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 scalar_t__ V_log_stp ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bridge_state_change(struct ifnet *ifp, int state)
{
	struct bridge_softc *sc = ifp->if_bridge;
	static const char *stpstates[] = {
		"disabled",
		"listening",
		"learning",
		"forwarding",
		"blocking",
		"discarding"
	};

	CURVNET_SET(ifp->if_vnet);
	if (V_log_stp)
		log(LOG_NOTICE, "%s: state changed to %s on %s\n",
		    sc->sc_ifp->if_xname, stpstates[state], ifp->if_xname);
	CURVNET_RESTORE();
}