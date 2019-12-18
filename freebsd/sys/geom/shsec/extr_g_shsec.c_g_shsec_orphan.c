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
struct g_shsec_softc {int dummy; } ;
struct g_geom {struct g_shsec_softc* softc; } ;
struct g_consumer {struct g_geom* geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_shsec_destroy (struct g_shsec_softc*,int) ; 
 scalar_t__ g_shsec_nvalid (struct g_shsec_softc*) ; 
 int /*<<< orphan*/  g_shsec_remove_disk (struct g_consumer*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static void
g_shsec_orphan(struct g_consumer *cp)
{
	struct g_shsec_softc *sc;
	struct g_geom *gp;

	g_topology_assert();
	gp = cp->geom;
	sc = gp->softc;
	if (sc == NULL)
		return;

	g_shsec_remove_disk(cp);
	/* If there are no valid disks anymore, remove device. */
	if (g_shsec_nvalid(sc) == 0)
		g_shsec_destroy(sc, 1);
}