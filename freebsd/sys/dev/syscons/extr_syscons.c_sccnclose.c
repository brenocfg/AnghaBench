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
struct sc_cnstate {void* kbd_opened; void* scr_opened; } ;
struct TYPE_7__ {scalar_t__ kbd_open_level; int /*<<< orphan*/  kbd; TYPE_1__* cur_scp; } ;
typedef  TYPE_2__ sc_softc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  kbd_mode; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  KDSKBMODE ; 
 int /*<<< orphan*/  kbdd_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdd_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdd_poll (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sccnkbdunlock (TYPE_2__*,struct sc_cnstate*) ; 
 int /*<<< orphan*/  sccnscrunlock (TYPE_2__*,struct sc_cnstate*) ; 

__attribute__((used)) static void
sccnclose(sc_softc_t *sc, struct sc_cnstate *sp)
{
    sp->scr_opened = FALSE;
    sccnscrunlock(sc, sp);

    if (!sp->kbd_opened)
	return;

    /* Restore keyboard mode (for the current, possibly-changed scp). */
    kbdd_poll(sc->kbd, FALSE);
    if (--sc->kbd_open_level == 0)
	(void)kbdd_ioctl(sc->kbd, KDSKBMODE, (caddr_t)&sc->cur_scp->kbd_mode);

    kbdd_disable(sc->kbd);
    sp->kbd_opened = FALSE;
    sccnkbdunlock(sc, sp);
}