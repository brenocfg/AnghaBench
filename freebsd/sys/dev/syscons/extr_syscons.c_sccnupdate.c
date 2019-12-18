#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sc; } ;
typedef  TYPE_1__ scr_stat ;
struct TYPE_7__ {int flags; scalar_t__ switch_in_progress; scalar_t__ blink_in_progress; TYPE_1__* cur_scp; scalar_t__ font_loading_in_progress; } ;

/* Variables and functions */
 scalar_t__ CONS_LKM_SAVER ; 
 int /*<<< orphan*/  ISGRAPHSC (TYPE_1__*) ; 
 int SC_SCRN_BLANKED ; 
 int SC_SCRN_IDLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  current_saver ; 
 scalar_t__ kdb_active ; 
 scalar_t__ panicstr ; 
 int /*<<< orphan*/  run_scrn_saver ; 
 scalar_t__ saver_mode ; 
 int /*<<< orphan*/  sc_touch_scrn_saver () ; 
 int /*<<< orphan*/  scrn_update (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ shutdown_in_progress ; 
 int /*<<< orphan*/  stop_scrn_saver (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ suspend_in_progress ; 

__attribute__((used)) static void
sccnupdate(scr_stat *scp)
{
    /* this is a cut-down version of scrn_timer()... */

    if (suspend_in_progress || scp->sc->font_loading_in_progress)
	return;

    if (kdb_active || panicstr || shutdown_in_progress) {
	sc_touch_scrn_saver();
    } else if (scp != scp->sc->cur_scp) {
	return;
    }

    if (!run_scrn_saver)
	scp->sc->flags &= ~SC_SCRN_IDLE;
#ifdef DEV_SPLASH
    if ((saver_mode != CONS_LKM_SAVER) || !(scp->sc->flags & SC_SCRN_IDLE))
	if (scp->sc->flags & SC_SCRN_BLANKED)
            stop_scrn_saver(scp->sc, current_saver);
#endif

    if (scp != scp->sc->cur_scp || scp->sc->blink_in_progress
	|| scp->sc->switch_in_progress)
	return;
    /*
     * FIXME: unlike scrn_timer(), we call scrn_update() from here even
     * when write_in_progress is non-zero.  XXX
     */

    if (!ISGRAPHSC(scp) && !(scp->sc->flags & SC_SCRN_BLANKED))
	scrn_update(scp, TRUE);
}