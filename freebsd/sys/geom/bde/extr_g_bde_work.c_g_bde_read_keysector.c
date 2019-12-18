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
struct g_bde_work {int dummy; } ;
struct g_bde_softc {int dummy; } ;
struct g_bde_sector {scalar_t__ state; struct g_bde_work* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 scalar_t__ VALID ; 
 struct g_bde_sector* g_bde_get_keysector (struct g_bde_work*) ; 
 int /*<<< orphan*/  g_bde_purge_sector (struct g_bde_softc*,int) ; 
 int /*<<< orphan*/  g_bde_release_keysector (struct g_bde_work*) ; 
 scalar_t__ g_bde_start_read (struct g_bde_sector*) ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,struct g_bde_work*) ; 

__attribute__((used)) static struct g_bde_sector *
g_bde_read_keysector(struct g_bde_softc *sc, struct g_bde_work *wp)
{
	struct g_bde_sector *sp;

	g_trace(G_T_TOPOLOGY, "g_bde_read_keysector(%p)", wp);
	sp = g_bde_get_keysector(wp);
	if (sp == NULL) {
		g_bde_purge_sector(sc, -1);
		sp = g_bde_get_keysector(wp);
	}
	if (sp == NULL)
		return (sp);
	if (sp->owner != wp)
		return (sp);
	if (sp->state == VALID)
		return (sp);
	if (g_bde_start_read(sp) == 0)
		return (sp);
	g_bde_release_keysector(wp);
	return (NULL);
}