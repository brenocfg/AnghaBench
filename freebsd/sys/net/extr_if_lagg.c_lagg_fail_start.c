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
struct mbuf {int dummy; } ;
struct lagg_softc {int /*<<< orphan*/  sc_primary; } ;
struct lagg_port {int /*<<< orphan*/  lp_ifp; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int lagg_enqueue (int /*<<< orphan*/ ,struct mbuf*) ; 
 struct lagg_port* lagg_link_active (struct lagg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
lagg_fail_start(struct lagg_softc *sc, struct mbuf *m)
{
	struct lagg_port *lp;

	/* Use the master port if active or the next available port */
	if ((lp = lagg_link_active(sc, sc->sc_primary)) == NULL) {
		m_freem(m);
		return (ENETDOWN);
	}

	/* Send mbuf */
	return (lagg_enqueue(lp->lp_ifp, m));
}