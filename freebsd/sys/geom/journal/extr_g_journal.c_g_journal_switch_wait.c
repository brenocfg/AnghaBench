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
struct g_journal_softc {scalar_t__ sc_flush_in_progress; scalar_t__ sc_copy_in_progress; scalar_t__ sc_flush_count; scalar_t__ sc_delayed_count; int sc_flags; int /*<<< orphan*/  sc_name; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_journal_copying; } ;
struct bintime {int dummy; } ;

/* Variables and functions */
 int GJF_DEVICE_BEFORE_SWITCH ; 
 int GJF_DEVICE_SWITCH ; 
 int /*<<< orphan*/  GJ_DEBUG (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  GJ_TIMER_START (int,struct bintime*) ; 
 int /*<<< orphan*/  GJ_TIMER_STOP (int,struct bintime*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PRIBIO ; 
 int g_journal_debug ; 
 int /*<<< orphan*/  g_journal_stats_switches ; 
 int /*<<< orphan*/  g_journal_stats_wait_for_copy ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct g_journal_softc*) ; 

__attribute__((used)) static void
g_journal_switch_wait(struct g_journal_softc *sc)
{
	struct bintime bt;

	mtx_assert(&sc->sc_mtx, MA_OWNED);
	if (g_journal_debug >= 2) {
		if (sc->sc_flush_in_progress > 0) {
			GJ_DEBUG(2, "%d requests flushing.",
			    sc->sc_flush_in_progress);
		}
		if (sc->sc_copy_in_progress > 0) {
			GJ_DEBUG(2, "%d requests copying.",
			    sc->sc_copy_in_progress);
		}
		if (sc->sc_flush_count > 0) {
			GJ_DEBUG(2, "%d requests to flush.",
			    sc->sc_flush_count);
		}
		if (sc->sc_delayed_count > 0) {
			GJ_DEBUG(2, "%d requests delayed.",
			    sc->sc_delayed_count);
		}
	}
	g_journal_stats_switches++;
	if (sc->sc_copy_in_progress > 0)
		g_journal_stats_wait_for_copy++;
	GJ_TIMER_START(1, &bt);
	sc->sc_flags &= ~GJF_DEVICE_BEFORE_SWITCH;
	sc->sc_flags |= GJF_DEVICE_SWITCH;
	wakeup(sc);
	while (sc->sc_flags & GJF_DEVICE_SWITCH) {
		msleep(&sc->sc_journal_copying, &sc->sc_mtx, PRIBIO,
		    "gj:switch", 0);
	}
	GJ_TIMER_STOP(1, &bt, "Switch time of %s", sc->sc_name);
}