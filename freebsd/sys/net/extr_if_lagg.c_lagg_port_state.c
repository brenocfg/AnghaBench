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
struct lagg_softc {int dummy; } ;
struct lagg_port {struct lagg_softc* lp_softc; } ;
struct ifnet {scalar_t__ if_lagg; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAGG_XLOCK (struct lagg_softc*) ; 
 int /*<<< orphan*/  LAGG_XUNLOCK (struct lagg_softc*) ; 
 int /*<<< orphan*/  lagg_linkstate (struct lagg_softc*) ; 
 int /*<<< orphan*/  lagg_proto_linkstate (struct lagg_softc*,struct lagg_port*) ; 

__attribute__((used)) static void
lagg_port_state(struct ifnet *ifp, int state)
{
	struct lagg_port *lp = (struct lagg_port *)ifp->if_lagg;
	struct lagg_softc *sc = NULL;

	if (lp != NULL)
		sc = lp->lp_softc;
	if (sc == NULL)
		return;

	LAGG_XLOCK(sc);
	lagg_linkstate(sc);
	lagg_proto_linkstate(sc, lp);
	LAGG_XUNLOCK(sc);
}