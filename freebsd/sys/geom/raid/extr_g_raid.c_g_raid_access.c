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
struct g_raid_volume {scalar_t__ v_provider_open; scalar_t__ v_stopping; scalar_t__ v_read_only; } ;
struct g_raid_softc {scalar_t__ sc_stopping; int /*<<< orphan*/  sc_lock; } ;
struct g_provider {int acw; int /*<<< orphan*/  name; struct g_raid_volume* private; TYPE_1__* geom; } ;
struct TYPE_2__ {struct g_raid_softc* softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int EROFS ; 
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,struct g_raid_softc*,char*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ G_RAID_DESTROY_DELAYED ; 
 scalar_t__ G_RAID_DESTROY_HARD ; 
 int /*<<< orphan*/  G_RAID_NODE_E_WAKE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_raid_clean (struct g_raid_volume*,int) ; 
 int /*<<< orphan*/  g_raid_destroy_volume (struct g_raid_volume*) ; 
 int /*<<< orphan*/  g_raid_event_send (struct g_raid_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_raid_nopens (struct g_raid_softc*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_raid_access(struct g_provider *pp, int acr, int acw, int ace)
{
	struct g_raid_volume *vol;
	struct g_raid_softc *sc;
	int dcw, opens, error = 0;

	g_topology_assert();
	sc = pp->geom->softc;
	vol = pp->private;
	KASSERT(sc != NULL, ("NULL softc (provider=%s).", pp->name));
	KASSERT(vol != NULL, ("NULL volume (provider=%s).", pp->name));

	G_RAID_DEBUG1(2, sc, "Access request for %s: r%dw%de%d.", pp->name,
	    acr, acw, ace);
	dcw = pp->acw + acw;

	g_topology_unlock();
	sx_xlock(&sc->sc_lock);
	/* Deny new opens while dying. */
	if (sc->sc_stopping != 0 && (acr > 0 || acw > 0 || ace > 0)) {
		error = ENXIO;
		goto out;
	}
	/* Deny write opens for read-only volumes. */
	if (vol->v_read_only && acw > 0) {
		error = EROFS;
		goto out;
	}
	if (dcw == 0)
		g_raid_clean(vol, dcw);
	vol->v_provider_open += acr + acw + ace;
	/* Handle delayed node destruction. */
	if (sc->sc_stopping == G_RAID_DESTROY_DELAYED &&
	    vol->v_provider_open == 0) {
		/* Count open volumes. */
		opens = g_raid_nopens(sc);
		if (opens == 0) {
			sc->sc_stopping = G_RAID_DESTROY_HARD;
			/* Wake up worker to make it selfdestruct. */
			g_raid_event_send(sc, G_RAID_NODE_E_WAKE, 0);
		}
	}
	/* Handle open volume destruction. */
	if (vol->v_stopping && vol->v_provider_open == 0)
		g_raid_destroy_volume(vol);
out:
	sx_xunlock(&sc->sc_lock);
	g_topology_lock();
	return (error);
}