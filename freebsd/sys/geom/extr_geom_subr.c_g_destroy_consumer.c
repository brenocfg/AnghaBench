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
struct g_geom {int flags; } ;
struct g_consumer {scalar_t__ acr; scalar_t__ acw; scalar_t__ ace; int /*<<< orphan*/  stat; struct g_geom* geom; int /*<<< orphan*/ * provider; } ;

/* Variables and functions */
 int G_GEOM_WITHER ; 
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  G_VALID_CONSUMER (struct g_consumer*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_consumer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consumer ; 
 int /*<<< orphan*/  devstat_remove_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cancel_event (struct g_consumer*) ; 
 int /*<<< orphan*/  g_do_wither () ; 
 int /*<<< orphan*/  g_free (struct g_consumer*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,struct g_consumer*) ; 

void
g_destroy_consumer(struct g_consumer *cp)
{
	struct g_geom *gp;

	g_topology_assert();
	G_VALID_CONSUMER(cp);
	g_trace(G_T_TOPOLOGY, "g_destroy_consumer(%p)", cp);
	KASSERT (cp->provider == NULL, ("g_destroy_consumer but attached"));
	KASSERT (cp->acr == 0, ("g_destroy_consumer with acr"));
	KASSERT (cp->acw == 0, ("g_destroy_consumer with acw"));
	KASSERT (cp->ace == 0, ("g_destroy_consumer with ace"));
	g_cancel_event(cp);
	gp = cp->geom;
	LIST_REMOVE(cp, consumer);
	devstat_remove_entry(cp->stat);
	g_free(cp);
	if (gp->flags & G_GEOM_WITHER)
		g_do_wither();
}