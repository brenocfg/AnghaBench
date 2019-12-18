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
struct g_raid_softc {int /*<<< orphan*/  sc_geom; } ;
struct g_provider {int dummy; } ;
struct g_consumer {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_CF_DIRECT_RECEIVE ; 
 scalar_t__ g_access (struct g_consumer*,int,int,int) ; 
 scalar_t__ g_attach (struct g_consumer*,struct g_provider*) ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 struct g_consumer* g_new_consumer (int /*<<< orphan*/ ) ; 
 struct g_provider* g_provider_by_name (char const*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

struct g_consumer *
g_raid_open_consumer(struct g_raid_softc *sc, const char *name)
{
	struct g_consumer *cp;
	struct g_provider *pp;

	g_topology_assert();

	if (strncmp(name, "/dev/", 5) == 0)
		name += 5;
	pp = g_provider_by_name(name);
	if (pp == NULL)
		return (NULL);
	cp = g_new_consumer(sc->sc_geom);
	cp->flags |= G_CF_DIRECT_RECEIVE;
	if (g_attach(cp, pp) != 0) {
		g_destroy_consumer(cp);
		return (NULL);
	}
	if (g_access(cp, 1, 1, 1) != 0) {
		g_detach(cp);
		g_destroy_consumer(cp);
		return (NULL);
	}
	return (cp);
}