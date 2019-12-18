#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_multipath_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ndisks; } ;
struct g_consumer {int index; int /*<<< orphan*/  private; TYPE_2__* geom; TYPE_1__* provider; } ;
struct TYPE_4__ {char* name; struct g_multipath_softc* softc; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_LOST ; 
 int MP_POSTED ; 
 int /*<<< orphan*/  g_mpd (struct g_consumer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_multipath_fault (struct g_consumer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static void
g_multipath_orphan(struct g_consumer *cp)
{
	struct g_multipath_softc *sc;
	uintptr_t *cnt;

	g_topology_assert();
	printf("GEOM_MULTIPATH: %s in %s was disconnected\n",
	    cp->provider->name, cp->geom->name);
	sc = cp->geom->softc;
	cnt = (uintptr_t *)&cp->private;
	mtx_lock(&sc->sc_mtx);
	sc->sc_ndisks--;
	g_multipath_fault(cp, MP_LOST);
	if (*cnt == 0 && (cp->index & MP_POSTED) == 0) {
		cp->index |= MP_POSTED;
		mtx_unlock(&sc->sc_mtx);
		g_mpd(cp, 0);
	} else
		mtx_unlock(&sc->sc_mtx);
}