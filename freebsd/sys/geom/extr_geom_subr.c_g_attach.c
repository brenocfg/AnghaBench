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
struct g_provider {int /*<<< orphan*/  consumers; } ;
struct g_consumer {int /*<<< orphan*/  geom; struct g_provider* provider; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_CF_ORPHAN ; 
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  G_VALID_CONSUMER (struct g_consumer*) ; 
 int /*<<< orphan*/  G_VALID_PROVIDER (struct g_provider*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct g_consumer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_consumer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consumers ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,struct g_consumer*,struct g_provider*) ; 
 int redo_rank (int /*<<< orphan*/ ) ; 

int
g_attach(struct g_consumer *cp, struct g_provider *pp)
{
	int error;

	g_topology_assert();
	G_VALID_CONSUMER(cp);
	G_VALID_PROVIDER(pp);
	g_trace(G_T_TOPOLOGY, "g_attach(%p, %p)", cp, pp);
	KASSERT(cp->provider == NULL, ("attach but attached"));
	cp->provider = pp;
	cp->flags &= ~G_CF_ORPHAN;
	LIST_INSERT_HEAD(&pp->consumers, cp, consumers);
	error = redo_rank(cp->geom);
	if (error) {
		LIST_REMOVE(cp, consumers);
		cp->provider = NULL;
		redo_rank(cp->geom);
	}
	return (error);
}