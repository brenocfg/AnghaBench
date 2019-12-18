#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ jj_offset; } ;
struct TYPE_3__ {scalar_t__ jj_offset; } ;
struct g_journal_softc {scalar_t__ sc_journal_offset; int sc_jend; int sc_jstart; int /*<<< orphan*/  sc_name; TYPE_2__ sc_inactive; TYPE_1__ sc_active; scalar_t__ sc_id; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  GJ_DEBUG (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  g_journal_cache_mtx ; 
 int g_journal_force_switch ; 
 int /*<<< orphan*/  g_journal_stats_journal_full ; 
 int /*<<< orphan*/  g_journal_switcher_state ; 
 int g_journal_switcher_wokenup ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_journal_check_overflow(struct g_journal_softc *sc)
{
	off_t length, used;

	if ((sc->sc_active.jj_offset < sc->sc_inactive.jj_offset &&
	     sc->sc_journal_offset >= sc->sc_inactive.jj_offset) ||
	    (sc->sc_active.jj_offset > sc->sc_inactive.jj_offset &&
	     sc->sc_journal_offset >= sc->sc_inactive.jj_offset &&
	     sc->sc_journal_offset < sc->sc_active.jj_offset)) {
		panic("Journal overflow "
		    "(id = %u joffset=%jd active=%jd inactive=%jd)",
		    (unsigned)sc->sc_id,
		    (intmax_t)sc->sc_journal_offset,
		    (intmax_t)sc->sc_active.jj_offset,
		    (intmax_t)sc->sc_inactive.jj_offset);
	}
	if (sc->sc_active.jj_offset < sc->sc_inactive.jj_offset) {
		length = sc->sc_inactive.jj_offset - sc->sc_active.jj_offset;
		used = sc->sc_journal_offset - sc->sc_active.jj_offset;
	} else {
		length = sc->sc_jend - sc->sc_active.jj_offset;
		length += sc->sc_inactive.jj_offset - sc->sc_jstart;
		if (sc->sc_journal_offset >= sc->sc_active.jj_offset)
			used = sc->sc_journal_offset - sc->sc_active.jj_offset;
		else {
			used = sc->sc_jend - sc->sc_active.jj_offset;
			used += sc->sc_journal_offset - sc->sc_jstart;
		}
	}
	/* Already woken up? */
	if (g_journal_switcher_wokenup)
		return;
	/*
	 * If the active journal takes more than g_journal_force_switch precent
	 * of free journal space, we force journal switch.
	 */
	KASSERT(length > 0,
	    ("length=%jd used=%jd active=%jd inactive=%jd joffset=%jd",
	    (intmax_t)length, (intmax_t)used,
	    (intmax_t)sc->sc_active.jj_offset,
	    (intmax_t)sc->sc_inactive.jj_offset,
	    (intmax_t)sc->sc_journal_offset));
	if ((used * 100) / length > g_journal_force_switch) {
		g_journal_stats_journal_full++;
		GJ_DEBUG(1, "Journal %s %jd%% full, forcing journal switch.",
		    sc->sc_name, (used * 100) / length);
		mtx_lock(&g_journal_cache_mtx);
		g_journal_switcher_wokenup = 1;
		wakeup(&g_journal_switcher_state);
		mtx_unlock(&g_journal_cache_mtx);
	}
}