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
struct g_journal_softc {TYPE_1__* sc_geom; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GJ_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  g_journal_destroy_event ; 
 int /*<<< orphan*/  g_post_event (int /*<<< orphan*/ ,struct g_journal_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_journal_timeout(void *arg)
{
	struct g_journal_softc *sc;

	sc = arg;
	GJ_DEBUG(0, "Timeout. Journal %s cannot be completed.",
	    sc->sc_geom->name);
	g_post_event(g_journal_destroy_event, sc, M_NOWAIT, NULL);
}