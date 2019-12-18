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
struct g_raid_softc {int sc_stopping; int /*<<< orphan*/  sc_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,struct g_raid_softc*,char*,...) ; 
#define  G_RAID_DESTROY_DELAYED 130 
#define  G_RAID_DESTROY_HARD 129 
#define  G_RAID_DESTROY_SOFT 128 
 int /*<<< orphan*/  G_RAID_NODE_E_WAKE ; 
 int PDROP ; 
 int PRIBIO ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  g_raid_event_send (struct g_raid_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_raid_nopens (struct g_raid_softc*) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int hz ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sx_sleep (int*,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
g_raid_destroy(struct g_raid_softc *sc, int how)
{
	int error, opens;

	g_topology_assert_not();
	if (sc == NULL)
		return (ENXIO);
	sx_assert(&sc->sc_lock, SX_XLOCKED);

	/* Count open volumes. */
	opens = g_raid_nopens(sc);

	/* React on some opened volumes. */
	if (opens > 0) {
		switch (how) {
		case G_RAID_DESTROY_SOFT:
			G_RAID_DEBUG1(1, sc,
			    "%d volumes are still open.",
			    opens);
			sx_xunlock(&sc->sc_lock);
			return (EBUSY);
		case G_RAID_DESTROY_DELAYED:
			G_RAID_DEBUG1(1, sc,
			    "Array will be destroyed on last close.");
			sc->sc_stopping = G_RAID_DESTROY_DELAYED;
			sx_xunlock(&sc->sc_lock);
			return (EBUSY);
		case G_RAID_DESTROY_HARD:
			G_RAID_DEBUG1(1, sc,
			    "%d volumes are still open.",
			    opens);
		}
	}

	/* Mark node for destruction. */
	sc->sc_stopping = G_RAID_DESTROY_HARD;
	/* Wake up worker to let it selfdestruct. */
	g_raid_event_send(sc, G_RAID_NODE_E_WAKE, 0);
	/* Sleep until node destroyed. */
	error = sx_sleep(&sc->sc_stopping, &sc->sc_lock,
	    PRIBIO | PDROP, "r:destroy", hz * 3);
	return (error == EWOULDBLOCK ? EBUSY : 0);
}