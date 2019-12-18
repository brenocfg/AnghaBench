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
struct g_geom {struct g_concat_softc* softc; } ;
struct g_consumer {struct g_concat_disk* private; struct g_geom* geom; } ;
struct g_concat_softc {int dummy; } ;
struct g_concat_disk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_concat_remove_disk (struct g_concat_disk*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static void
g_concat_orphan(struct g_consumer *cp)
{
	struct g_concat_softc *sc;
	struct g_concat_disk *disk;
	struct g_geom *gp;

	g_topology_assert();
	gp = cp->geom;
	sc = gp->softc;
	if (sc == NULL)
		return;

	disk = cp->private;
	if (disk == NULL)	/* Possible? */
		return;
	g_concat_remove_disk(disk);
}