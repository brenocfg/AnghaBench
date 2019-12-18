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
struct lagg_softc {int sc_proto; struct lagg_port* sc_primary; int /*<<< orphan*/  sc_ifname; } ;
struct lagg_reqport {int /*<<< orphan*/  rp_flags; int /*<<< orphan*/  rp_psc; int /*<<< orphan*/  rp_prio; int /*<<< orphan*/  rp_portname; int /*<<< orphan*/  rp_ifname; } ;
struct lagg_port {int /*<<< orphan*/  lp_flags; int /*<<< orphan*/  lp_prio; TYPE_1__* lp_ifp; struct lagg_softc* lp_softc; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAGG_PORTACTIVE (struct lagg_port*) ; 
 int /*<<< orphan*/  LAGG_PORT_ACTIVE ; 
 int /*<<< orphan*/  LAGG_PORT_COLLECTING ; 
 int /*<<< orphan*/  LAGG_PORT_DISTRIBUTING ; 
 int /*<<< orphan*/  LAGG_PORT_MASTER ; 
#define  LAGG_PROTO_BROADCAST 132 
#define  LAGG_PROTO_FAILOVER 131 
#define  LAGG_PROTO_LACP 130 
#define  LAGG_PROTO_LOADBALANCE 129 
#define  LAGG_PROTO_ROUNDROBIN 128 
 int /*<<< orphan*/  lacp_isactive (struct lagg_port*) ; 
 int /*<<< orphan*/  lacp_iscollecting (struct lagg_port*) ; 
 int /*<<< orphan*/  lacp_isdistributing (struct lagg_port*) ; 
 struct lagg_port* lagg_link_active (struct lagg_softc*,struct lagg_port*) ; 
 int /*<<< orphan*/  lagg_proto_portreq (struct lagg_softc*,struct lagg_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lagg_port2req(struct lagg_port *lp, struct lagg_reqport *rp)
{
	struct lagg_softc *sc = lp->lp_softc;

	strlcpy(rp->rp_ifname, sc->sc_ifname, sizeof(rp->rp_ifname));
	strlcpy(rp->rp_portname, lp->lp_ifp->if_xname, sizeof(rp->rp_portname));
	rp->rp_prio = lp->lp_prio;
	rp->rp_flags = lp->lp_flags;
	lagg_proto_portreq(sc, lp, &rp->rp_psc);

	/* Add protocol specific flags */
	switch (sc->sc_proto) {
		case LAGG_PROTO_FAILOVER:
			if (lp == sc->sc_primary)
				rp->rp_flags |= LAGG_PORT_MASTER;
			if (lp == lagg_link_active(sc, sc->sc_primary))
				rp->rp_flags |= LAGG_PORT_ACTIVE;
			break;

		case LAGG_PROTO_ROUNDROBIN:
		case LAGG_PROTO_LOADBALANCE:
		case LAGG_PROTO_BROADCAST:
			if (LAGG_PORTACTIVE(lp))
				rp->rp_flags |= LAGG_PORT_ACTIVE;
			break;

		case LAGG_PROTO_LACP:
			/* LACP has a different definition of active */
			if (lacp_isactive(lp))
				rp->rp_flags |= LAGG_PORT_ACTIVE;
			if (lacp_iscollecting(lp))
				rp->rp_flags |= LAGG_PORT_COLLECTING;
			if (lacp_isdistributing(lp))
				rp->rp_flags |= LAGG_PORT_DISTRIBUTING;
			break;
	}

}