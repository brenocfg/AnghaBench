#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sc_cnstate {void* scr_opened; int /*<<< orphan*/  mtx_locked; int /*<<< orphan*/  kdb_locked; void* kbd_opened; void* kbd_locked; } ;
struct TYPE_13__ {TYPE_2__* cur_scp; int /*<<< orphan*/ * kbd; int /*<<< orphan*/  kbd_open_level; } ;
typedef  TYPE_4__ sc_softc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_12__ {scalar_t__ mode; } ;
struct TYPE_14__ {scalar_t__ index; TYPE_3__ smode; } ;
struct TYPE_10__ {scalar_t__ mode; } ;
struct TYPE_11__ {scalar_t__ index; TYPE_1__ smode; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  KDSKBMODE ; 
 int K_XLATE ; 
 void* TRUE ; 
 scalar_t__ VT_AUTO ; 
 int /*<<< orphan*/  cold ; 
 int /*<<< orphan*/  kbdd_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kbdd_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdd_poll (int /*<<< orphan*/ *,void*) ; 
 TYPE_9__* sc_console ; 
 int /*<<< orphan*/  sc_switch_scr (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  sccnkbdlock (TYPE_4__*,struct sc_cnstate*) ; 
 int /*<<< orphan*/  sccnscrlock (TYPE_4__*,struct sc_cnstate*) ; 

__attribute__((used)) static void
sccnopen(sc_softc_t *sc, struct sc_cnstate *sp, int flags)
{
    int kbd_mode;

    /* assert(sc_console_unit >= 0) */

    sp->kbd_opened = FALSE;
    sp->scr_opened = FALSE;
    sp->kbd_locked = FALSE;

    /* Opening the keyboard is optional. */
    if (!(flags & 1) || sc->kbd == NULL)
	goto over_keyboard;

    sccnkbdlock(sc, sp);

    /*
     * Make sure the keyboard is accessible even when the kbd device
     * driver is disabled.
     */
    kbdd_enable(sc->kbd);

    /* Switch the keyboard to console mode (K_XLATE, polled) on all scp's. */
    kbd_mode = K_XLATE;
    (void)kbdd_ioctl(sc->kbd, KDSKBMODE, (caddr_t)&kbd_mode);
    sc->kbd_open_level++;
    kbdd_poll(sc->kbd, TRUE);

    sp->kbd_opened = TRUE;
over_keyboard: ;

    /* The screen is opened iff locking it succeeds. */
    sccnscrlock(sc, sp);
    if (!sp->kdb_locked && !sp->mtx_locked)
	return;
    sp->scr_opened = TRUE;

    /* The screen switch is optional. */
    if (!(flags & 2))
	return;

    /* try to switch to the kernel console screen */
    if (!cold &&
	sc->cur_scp->index != sc_console->index &&
	sc->cur_scp->smode.mode == VT_AUTO &&
	sc_console->smode.mode == VT_AUTO)
	    sc_switch_scr(sc, sc_console->index);
}