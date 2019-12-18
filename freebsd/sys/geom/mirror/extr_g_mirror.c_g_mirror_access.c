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
struct g_provider {scalar_t__ acw; int /*<<< orphan*/  name; struct g_mirror_softc* private; } ;
struct g_mirror_softc {int sc_flags; scalar_t__ sc_provider_open; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_disks; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  G_MIRROR_DEBUG (int,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int G_MIRROR_DEVICE_FLAG_CLOSEWAIT ; 
 int G_MIRROR_DEVICE_FLAG_DESTROY ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  g_mirror_destroy_delayed ; 
 int /*<<< orphan*/  g_mirror_idle (struct g_mirror_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_post_event (int /*<<< orphan*/ ,struct g_mirror_softc*,int /*<<< orphan*/ ,struct g_mirror_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_mirror_access(struct g_provider *pp, int acr, int acw, int ace)
{
	struct g_mirror_softc *sc;
	int error = 0;

	g_topology_assert();
	G_MIRROR_DEBUG(2, "Access request for %s: r%dw%de%d.", pp->name, acr,
	    acw, ace);

	sc = pp->private;
	KASSERT(sc != NULL, ("NULL softc (provider=%s).", pp->name));

	g_topology_unlock();
	sx_xlock(&sc->sc_lock);
	if ((sc->sc_flags & G_MIRROR_DEVICE_FLAG_DESTROY) != 0 ||
	    (sc->sc_flags & G_MIRROR_DEVICE_FLAG_CLOSEWAIT) != 0 ||
	    LIST_EMPTY(&sc->sc_disks)) {
		if (acr > 0 || acw > 0 || ace > 0)
			error = ENXIO;
		goto end;
	}
	sc->sc_provider_open += acr + acw + ace;
	if (pp->acw + acw == 0)
		g_mirror_idle(sc, 0);
	if ((sc->sc_flags & G_MIRROR_DEVICE_FLAG_CLOSEWAIT) != 0 &&
	    sc->sc_provider_open == 0)
		g_post_event(g_mirror_destroy_delayed, sc, M_WAITOK, sc, NULL);
end:
	sx_xunlock(&sc->sc_lock);
	g_topology_lock();
	return (error);
}