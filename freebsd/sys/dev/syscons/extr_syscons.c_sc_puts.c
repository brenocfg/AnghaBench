#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {TYPE_4__* sc; TYPE_1__* tsw; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_8__ {scalar_t__ delayed_next_scr; TYPE_2__* cur_scp; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* te_puts ) (TYPE_2__*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  run_scrn_saver ; 
 int /*<<< orphan*/  sc_saver_keyb_only ; 
 int /*<<< orphan*/  sc_switch_scr (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  sticky_splash ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
sc_puts(scr_stat *scp, u_char *buf, int len)
{
#ifdef DEV_SPLASH
    /* make screensaver happy */
    if (!sticky_splash && scp == scp->sc->cur_scp && !sc_saver_keyb_only)
	run_scrn_saver = FALSE;
#endif

    if (scp->tsw)
	(*scp->tsw->te_puts)(scp, buf, len);
    if (scp->sc->delayed_next_scr)
	sc_switch_scr(scp->sc, scp->sc->delayed_next_scr - 1);
}