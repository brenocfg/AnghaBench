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
typedef  int /*<<< orphan*/  uint32_t ;
struct mbuf {int dummy; } ;
struct lagg_softc {scalar_t__ sc_bkt_count; scalar_t__ sc_bkt; int /*<<< orphan*/  sc_ports; int /*<<< orphan*/  sc_count; int /*<<< orphan*/  sc_seq; } ;
struct lagg_port {int /*<<< orphan*/  lp_ifp; } ;

/* Variables and functions */
 struct lagg_port* CK_SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct lagg_port* CK_SLIST_NEXT (struct lagg_port*,int /*<<< orphan*/ ) ; 
 int ENETDOWN ; 
 scalar_t__ atomic_cmpset_int (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  atomic_fetchadd_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (scalar_t__*,int) ; 
 int lagg_enqueue (int /*<<< orphan*/ ,struct mbuf*) ; 
 struct lagg_port* lagg_link_active (struct lagg_softc*,struct lagg_port*) ; 
 int /*<<< orphan*/  lp_entries ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
lagg_rr_start(struct lagg_softc *sc, struct mbuf *m)
{
	struct lagg_port *lp;
	uint32_t p;

	if (sc->sc_bkt_count == 0 && sc->sc_bkt > 0)
		sc->sc_bkt_count = sc->sc_bkt;

	if (sc->sc_bkt > 0) {
		atomic_subtract_int(&sc->sc_bkt_count, 1);
	if (atomic_cmpset_int(&sc->sc_bkt_count, 0, sc->sc_bkt))
		p = atomic_fetchadd_32(&sc->sc_seq, 1);
	else
		p = sc->sc_seq; 
	} else
		p = atomic_fetchadd_32(&sc->sc_seq, 1);

	p %= sc->sc_count;
	lp = CK_SLIST_FIRST(&sc->sc_ports);

	while (p--)
		lp = CK_SLIST_NEXT(lp, lp_entries);

	/*
	 * Check the port's link state. This will return the next active
	 * port if the link is down or the port is NULL.
	 */
	if ((lp = lagg_link_active(sc, lp)) == NULL) {
		m_freem(m);
		return (ENETDOWN);
	}

	/* Send mbuf */
	return (lagg_enqueue(lp->lp_ifp, m));
}