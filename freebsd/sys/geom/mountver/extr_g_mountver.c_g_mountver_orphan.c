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
struct g_mountver_softc {int sc_orphaned; int /*<<< orphan*/  sc_provider_name; } ;
struct g_consumer {int /*<<< orphan*/  ace; int /*<<< orphan*/  acw; int /*<<< orphan*/  acr; TYPE_1__* geom; } ;
struct TYPE_2__ {struct g_mountver_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_MOUNTVER_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_access (struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static void
g_mountver_orphan(struct g_consumer *cp)
{
	struct g_mountver_softc *sc;

	g_topology_assert();

	sc = cp->geom->softc;
	sc->sc_orphaned = 1;
	if (cp->acr > 0 || cp->acw > 0 || cp->ace > 0)
		g_access(cp, -cp->acr, -cp->acw, -cp->ace);
	g_detach(cp);
	G_MOUNTVER_DEBUG(0, "%s is offline.  Mount verification in progress.", sc->sc_provider_name);
}