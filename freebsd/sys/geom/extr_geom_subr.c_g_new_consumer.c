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
struct g_geom {int flags; int /*<<< orphan*/  consumer; TYPE_1__* class; int /*<<< orphan*/  name; int /*<<< orphan*/ * orphan; } ;
struct g_consumer {int /*<<< orphan*/  stat; struct g_geom* geom; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVSTAT_ALL_SUPPORTED ; 
 int /*<<< orphan*/  DEVSTAT_PRIORITY_MAX ; 
 int /*<<< orphan*/  DEVSTAT_TYPE_DIRECT ; 
 int G_GEOM_WITHER ; 
 int /*<<< orphan*/  G_VALID_GEOM (struct g_geom*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct g_consumer*,int /*<<< orphan*/ ) ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  consumer ; 
 int /*<<< orphan*/  devstat_new_entry (struct g_consumer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct g_consumer* g_malloc (int,int) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

struct g_consumer *
g_new_consumer(struct g_geom *gp)
{
	struct g_consumer *cp;

	g_topology_assert();
	G_VALID_GEOM(gp);
	KASSERT(!(gp->flags & G_GEOM_WITHER),
	    ("g_new_consumer on WITHERing geom(%s) (class %s)",
	    gp->name, gp->class->name));
	KASSERT(gp->orphan != NULL,
	    ("g_new_consumer on geom(%s) (class %s) without orphan",
	    gp->name, gp->class->name));

	cp = g_malloc(sizeof *cp, M_WAITOK | M_ZERO);
	cp->geom = gp;
	cp->stat = devstat_new_entry(cp, -1, 0, DEVSTAT_ALL_SUPPORTED,
	    DEVSTAT_TYPE_DIRECT, DEVSTAT_PRIORITY_MAX);
	LIST_INSERT_HEAD(&gp->consumer, cp, consumer);
	return(cp);
}