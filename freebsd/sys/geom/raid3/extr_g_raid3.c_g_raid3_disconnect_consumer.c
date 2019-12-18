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
struct g_raid3_softc {int dummy; } ;
struct g_consumer {int /*<<< orphan*/ * provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_raid3_kill_consumer (struct g_raid3_softc*,struct g_consumer*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static void
g_raid3_disconnect_consumer(struct g_raid3_softc *sc, struct g_consumer *cp)
{

	g_topology_assert();

	if (cp == NULL)
		return;
	if (cp->provider != NULL)
		g_raid3_kill_consumer(sc, cp);
	else
		g_destroy_consumer(cp);
}