#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* sc; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_5__ {int flags; int blink_in_progress; TYPE_2__* cur_scp; } ;

/* Variables and functions */
 int SC_QUIET_BELL ; 
 int SC_VISUAL_BELL ; 
 int /*<<< orphan*/  blink_screen (TYPE_2__*) ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  enable_bell ; 
 scalar_t__ kdb_active ; 
 scalar_t__ shutdown_in_progress ; 
 int /*<<< orphan*/  sysbeep (int,int) ; 

void
sc_bell(scr_stat *scp, int pitch, int duration)
{
    if (cold || kdb_active || shutdown_in_progress || !enable_bell)
	return;

    if (scp != scp->sc->cur_scp && (scp->sc->flags & SC_QUIET_BELL))
	return;

    if (scp->sc->flags & SC_VISUAL_BELL) {
	if (scp->sc->blink_in_progress)
	    return;
	scp->sc->blink_in_progress = 3;
	if (scp != scp->sc->cur_scp)
	    scp->sc->blink_in_progress += 2;
	blink_screen(scp->sc->cur_scp);
    } else if (duration != 0 && pitch != 0) {
	if (scp != scp->sc->cur_scp)
	    pitch *= 2;
	sysbeep(1193182 / pitch, duration);
    }
}