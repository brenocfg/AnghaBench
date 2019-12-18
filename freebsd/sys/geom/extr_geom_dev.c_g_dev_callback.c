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
struct g_dev_softc {int /*<<< orphan*/  sc_active; int /*<<< orphan*/ * sc_alias; int /*<<< orphan*/ * sc_dev; } ;
struct g_consumer {TYPE_1__* geom; struct g_dev_softc* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int SC_A_ACTIVE ; 
 int /*<<< orphan*/  SC_A_DESTROY ; 
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_dev_destroy ; 
 int /*<<< orphan*/  g_post_event (int /*<<< orphan*/ ,struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,struct g_consumer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_dev_callback(void *arg)
{
	struct g_consumer *cp;
	struct g_dev_softc *sc;
	int active;

	cp = arg;
	sc = cp->private;
	g_trace(G_T_TOPOLOGY, "g_dev_callback(%p(%s))", cp, cp->geom->name);

	sc->sc_dev = NULL;
	sc->sc_alias = NULL;
	active = atomic_fetchadd_int(&sc->sc_active, SC_A_DESTROY);
	if ((active & SC_A_ACTIVE) == 0)
		g_post_event(g_dev_destroy, cp, M_WAITOK, NULL);
}