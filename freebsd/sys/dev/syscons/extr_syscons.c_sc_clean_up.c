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
struct TYPE_6__ {int /*<<< orphan*/  status; TYPE_2__* sc; } ;
typedef  TYPE_1__ scr_stat ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOUSE_HIDDEN ; 
 int SC_SCRN_BLANKED ; 
 int /*<<< orphan*/  sc_remove_cutmarking (TYPE_1__*) ; 
 int /*<<< orphan*/  sc_remove_mouse_image (TYPE_1__*) ; 
 int /*<<< orphan*/  sc_touch_scrn_saver () ; 
 int wait_scrn_saver_stop (TYPE_2__*) ; 

int
sc_clean_up(scr_stat *scp)
{
#ifdef DEV_SPLASH
    int error;
#endif

    if (scp->sc->flags & SC_SCRN_BLANKED) {
	sc_touch_scrn_saver();
#ifdef DEV_SPLASH
	if ((error = wait_scrn_saver_stop(scp->sc)))
	    return error;
#endif
    }
    scp->status |= MOUSE_HIDDEN;
    sc_remove_mouse_image(scp);
    sc_remove_cutmarking(scp);
    return 0;
}