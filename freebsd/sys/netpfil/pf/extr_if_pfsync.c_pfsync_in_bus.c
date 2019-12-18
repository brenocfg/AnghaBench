#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pfsync_state {int dummy; } ;
struct pfsync_softc {scalar_t__ sc_ureq_sent; int sc_flags; int /*<<< orphan*/  sc_bulkfail_tmo; int /*<<< orphan*/  sc_bulk_tries; TYPE_1__* sc_ifp; } ;
struct pfsync_pkt {int dummy; } ;
struct pfsync_bus {int status; int /*<<< orphan*/  endtime; } ;
struct mbuf {scalar_t__ m_data; } ;
struct TYPE_8__ {int limit; } ;
struct TYPE_7__ {int /*<<< orphan*/  debug; } ;
struct TYPE_6__ {int /*<<< orphan*/  pfsyncs_badlen; } ;
struct TYPE_5__ {int if_mtu; } ;

/* Variables and functions */
 int PFSYNCF_OK ; 
 int /*<<< orphan*/  PFSYNC_BLOCK (struct pfsync_softc*) ; 
 int /*<<< orphan*/  PFSYNC_BUNLOCK (struct pfsync_softc*) ; 
#define  PFSYNC_BUS_END 129 
#define  PFSYNC_BUS_START 128 
 int PFSYNC_MINPKT ; 
 int /*<<< orphan*/  PF_DEBUG_MISC ; 
 size_t PF_LIMIT_STATES ; 
 TYPE_4__* V_pf_limits ; 
 TYPE_3__ V_pf_status ; 
 int /*<<< orphan*/  V_pfsync_carp_adj ; 
 struct pfsync_softc* V_pfsyncif ; 
 TYPE_2__ V_pfsyncstats ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct pfsync_softc*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carp_demote_adj_p (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 struct mbuf* m_pulldown (struct mbuf*,int,int,int*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfsync_bulk_fail ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static int
pfsync_in_bus(struct pfsync_pkt *pkt, struct mbuf *m, int offset, int count)
{
	struct pfsync_softc *sc = V_pfsyncif;
	struct pfsync_bus *bus;
	struct mbuf *mp;
	int len = count * sizeof(*bus);
	int offp;

	PFSYNC_BLOCK(sc);

	/* If we're not waiting for a bulk update, who cares. */
	if (sc->sc_ureq_sent == 0) {
		PFSYNC_BUNLOCK(sc);
		return (len);
	}

	mp = m_pulldown(m, offset, len, &offp);
	if (mp == NULL) {
		PFSYNC_BUNLOCK(sc);
		V_pfsyncstats.pfsyncs_badlen++;
		return (-1);
	}
	bus = (struct pfsync_bus *)(mp->m_data + offp);

	switch (bus->status) {
	case PFSYNC_BUS_START:
		callout_reset(&sc->sc_bulkfail_tmo, 4 * hz +
		    V_pf_limits[PF_LIMIT_STATES].limit /
		    ((sc->sc_ifp->if_mtu - PFSYNC_MINPKT) /
		    sizeof(struct pfsync_state)),
		    pfsync_bulk_fail, sc);
		if (V_pf_status.debug >= PF_DEBUG_MISC)
			printf("pfsync: received bulk update start\n");
		break;

	case PFSYNC_BUS_END:
		if (time_uptime - ntohl(bus->endtime) >=
		    sc->sc_ureq_sent) {
			/* that's it, we're happy */
			sc->sc_ureq_sent = 0;
			sc->sc_bulk_tries = 0;
			callout_stop(&sc->sc_bulkfail_tmo);
			if (!(sc->sc_flags & PFSYNCF_OK) && carp_demote_adj_p)
				(*carp_demote_adj_p)(-V_pfsync_carp_adj,
				    "pfsync bulk done");
			sc->sc_flags |= PFSYNCF_OK;
			if (V_pf_status.debug >= PF_DEBUG_MISC)
				printf("pfsync: received valid "
				    "bulk update end\n");
		} else {
			if (V_pf_status.debug >= PF_DEBUG_MISC)
				printf("pfsync: received invalid "
				    "bulk update end: bad timestamp\n");
		}
		break;
	}
	PFSYNC_BUNLOCK(sc);

	return (len);
}