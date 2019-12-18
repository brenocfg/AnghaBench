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
struct g_geom {struct g_gate_softc* softc; } ;
struct g_gate_softc {struct g_consumer* sc_readcons; } ;
struct g_consumer {TYPE_1__* provider; struct g_geom* geom; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_GATE_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  g_access (struct g_consumer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static void
g_gate_orphan(struct g_consumer *cp)
{
	struct g_gate_softc *sc;
	struct g_geom *gp;

	g_topology_assert();
	gp = cp->geom;
	sc = gp->softc;
	if (sc == NULL)
		return;
	KASSERT(cp == sc->sc_readcons, ("cp=%p sc_readcons=%p", cp,
	    sc->sc_readcons));
	sc->sc_readcons = NULL;
	G_GATE_DEBUG(1, "Destroying read consumer on provider %s orphan.",
	    cp->provider->name);
	(void)g_access(cp, -1, 0, 0);
	g_detach(cp);
	g_destroy_consumer(cp);
}