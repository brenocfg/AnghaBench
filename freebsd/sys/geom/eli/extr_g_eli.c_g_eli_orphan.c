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
struct g_eli_softc {int dummy; } ;
struct g_consumer {TYPE_1__* geom; } ;
struct TYPE_2__ {struct g_eli_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_eli_destroy (struct g_eli_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static void
g_eli_orphan(struct g_consumer *cp)
{
	struct g_eli_softc *sc;

	g_topology_assert();
	sc = cp->geom->softc;
	if (sc == NULL)
		return;
	g_eli_destroy(sc, TRUE);
}