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
struct g_provider {scalar_t__ acr; scalar_t__ acw; scalar_t__ ace; int /*<<< orphan*/  stat; struct g_geom* geom; int /*<<< orphan*/  consumers; } ;
struct g_geom {int flags; int /*<<< orphan*/  (* providergone ) (struct g_provider*) ;} ;

/* Variables and functions */
 int G_GEOM_WITHER ; 
 int /*<<< orphan*/  G_VALID_PROVIDER (struct g_provider*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devstat_remove_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cancel_event (struct g_provider*) ; 
 int /*<<< orphan*/  g_do_wither () ; 
 int /*<<< orphan*/  g_free (struct g_provider*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  provider ; 
 int /*<<< orphan*/  stub1 (struct g_provider*) ; 

void
g_destroy_provider(struct g_provider *pp)
{
	struct g_geom *gp;

	g_topology_assert();
	G_VALID_PROVIDER(pp);
	KASSERT(LIST_EMPTY(&pp->consumers),
	    ("g_destroy_provider but attached"));
	KASSERT (pp->acr == 0, ("g_destroy_provider with acr"));
	KASSERT (pp->acw == 0, ("g_destroy_provider with acw"));
	KASSERT (pp->ace == 0, ("g_destroy_provider with ace"));
	g_cancel_event(pp);
	LIST_REMOVE(pp, provider);
	gp = pp->geom;
	devstat_remove_entry(pp->stat);
	/*
	 * If a callback was provided, send notification that the provider
	 * is now gone.
	 */
	if (gp->providergone != NULL)
		gp->providergone(pp);

	g_free(pp);
	if ((gp->flags & G_GEOM_WITHER))
		g_do_wither();
}