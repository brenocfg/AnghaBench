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
struct ifnet {int dummy; } ;
struct hn_softc {int /*<<< orphan*/  hn_ifp; struct ifnet* hn_vf_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hn_ifnet_lnkevent(void *xsc, struct ifnet *ifp, int link_state)
{
	struct hn_softc *sc = xsc;

	if (sc->hn_vf_ifp == ifp)
		if_link_state_change(sc->hn_ifp, link_state);
}