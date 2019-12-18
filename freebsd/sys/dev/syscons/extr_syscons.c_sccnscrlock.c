#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sc_cnstate {int kdb_locked; int mtx_locked; } ;
struct TYPE_5__ {scalar_t__ mtx_lock; } ;
struct TYPE_4__ {TYPE_3__ video_mtx; } ;
typedef  TYPE_1__ sc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 void* FALSE ; 
 int /*<<< orphan*/  MTX_QUIET ; 
 scalar_t__ MTX_UNOWNED ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int TRUE ; 
 scalar_t__ kdb_active ; 
 scalar_t__ mtx_trylock_spin_flags (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sccnscrlock(sc_softc_t *sc, struct sc_cnstate *sp)
{
    int retries;

    /**
     * Locking method:
     * - if kdb_active and video_mtx is not owned by anyone, then lock
     *   by kdb remaining active
     * - if !kdb_active, try to acquire video_mtx without blocking or
     *   recursing; if we get it then it works normally.
     * Note that video_mtx is especially unusable if we already own it,
     * since then it is protecting something and syscons is not reentrant
     * enough to ignore the protection even in the kdb_active case.
     */
    if (kdb_active) {
	sp->kdb_locked = sc->video_mtx.mtx_lock == MTX_UNOWNED ||
			 SCHEDULER_STOPPED();
	sp->mtx_locked = FALSE;
    } else {
	sp->kdb_locked = FALSE;
	for (retries = 0; retries < 1000; retries++) {
	    sp->mtx_locked = mtx_trylock_spin_flags(&sc->video_mtx,
						    MTX_QUIET) != 0;
	    if (SCHEDULER_STOPPED()) {
		sp->kdb_locked = TRUE;
		sp->mtx_locked = FALSE;
		break;
	    }
	    if (sp->mtx_locked)
		break;
	    DELAY(1);
	}
    }
}