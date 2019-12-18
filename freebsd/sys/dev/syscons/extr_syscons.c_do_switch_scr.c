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
struct TYPE_6__ {scalar_t__ unit; scalar_t__ switch_in_progress; TYPE_2__* cur_scp; int /*<<< orphan*/  new_scp; } ;
typedef  TYPE_1__ sc_softc_t ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VTY_WCHAN (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnavailable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exchange_scr (TYPE_1__*) ; 
 scalar_t__ sc_console_unit ; 
 int /*<<< orphan*/  sc_consptr ; 
 int /*<<< orphan*/  signal_vt_acq (TYPE_2__*) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  vt_proc_alive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_switch_scr(sc_softc_t *sc, int s)
{
    vt_proc_alive(sc->new_scp);

    splx(s);
    exchange_scr(sc);
    s = spltty();
    /* sc->cur_scp == sc->new_scp */
    wakeup(VTY_WCHAN(sc,sc->cur_scp->index));

    /* wait for the controlling process to acknowledge, if necessary */
    if (!signal_vt_acq(sc->cur_scp)) {
	sc->switch_in_progress = 0;
	if (sc->unit == sc_console_unit)
	    cnavailable(sc_consptr,  TRUE);
    }

    return s;
}