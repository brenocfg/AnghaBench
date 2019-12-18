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
struct g_geom {char* name; int /*<<< orphan*/  consumer; } ;
struct g_consumer {scalar_t__ acr; scalar_t__ ace; TYPE_1__* provider; int /*<<< orphan*/  acw; struct g_geom* geom; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_LOG (int,char*,char*) ; 
 int /*<<< orphan*/  g_access (struct g_consumer*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_wither_geom (struct g_geom*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vdev_geom_detach(struct g_consumer *cp, boolean_t open_for_read)
{
	struct g_geom *gp;

	g_topology_assert();

	ZFS_LOG(1, "Detaching from %s.",
	    cp->provider && cp->provider->name ? cp->provider->name : "NULL");

	gp = cp->geom;
	if (open_for_read)
		g_access(cp, -1, 0, -1);
	/* Destroy consumer on last close. */
	if (cp->acr == 0 && cp->ace == 0) {
		if (cp->acw > 0)
			g_access(cp, 0, -cp->acw, 0);
		if (cp->provider != NULL) {
			ZFS_LOG(1, "Destroying consumer for %s.",
			    cp->provider->name ? cp->provider->name : "NULL");
			g_detach(cp);
		}
		g_destroy_consumer(cp);
	}
	/* Destroy geom if there are no consumers left. */
	if (LIST_EMPTY(&gp->consumer)) {
		ZFS_LOG(1, "Destroyed geom %s.", gp->name);
		g_wither_geom(gp, ENXIO);
	}
}