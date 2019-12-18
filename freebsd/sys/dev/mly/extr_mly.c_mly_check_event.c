#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mly_softc {scalar_t__ mly_event_change; scalar_t__ mly_event_waiting; scalar_t__ mly_event_counter; TYPE_3__* mly_mmbox; } ;
struct TYPE_5__ {scalar_t__ change_counter; scalar_t__ next_event; } ;
struct TYPE_4__ {TYPE_2__ status; } ;
struct TYPE_6__ {TYPE_1__ mmm_health; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (int,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mly_fetch_event (struct mly_softc*) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
mly_check_event(struct mly_softc *sc)
{
    
    /*
     * The controller may have updated the health status information,
     * so check for it here.  Note that the counters are all in host memory,
     * so this check is very cheap.  Also note that we depend on checking on
     * completion 
     */
    if (sc->mly_mmbox->mmm_health.status.change_counter != sc->mly_event_change) {
	sc->mly_event_change = sc->mly_mmbox->mmm_health.status.change_counter;
	debug(1, "event change %d, event status update, %d -> %d", sc->mly_event_change,
	      sc->mly_event_waiting, sc->mly_mmbox->mmm_health.status.next_event);
	sc->mly_event_waiting = sc->mly_mmbox->mmm_health.status.next_event;

	/* wake up anyone that might be interested in this */
	wakeup(&sc->mly_event_change);
    }
    if (sc->mly_event_counter != sc->mly_event_waiting)
    mly_fetch_event(sc);
}