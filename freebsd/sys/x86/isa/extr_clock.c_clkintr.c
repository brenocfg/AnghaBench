#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;
struct attimer_softc {scalar_t__ period; scalar_t__ mode; TYPE_1__ et; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 scalar_t__ MODE_STOP ; 
 scalar_t__ clkintr_pending ; 
 int /*<<< orphan*/  clock_lock ; 
 scalar_t__ i8254_lastcount ; 
 scalar_t__ i8254_max_count ; 
 int /*<<< orphan*/  i8254_offset ; 
 scalar_t__ i8254_ticked ; 
 scalar_t__ i8254_timecounter ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
clkintr(void *arg)
{
	struct attimer_softc *sc = (struct attimer_softc *)arg;

	if (i8254_timecounter && sc->period != 0) {
		mtx_lock_spin(&clock_lock);
		if (i8254_ticked)
			i8254_ticked = 0;
		else {
			i8254_offset += i8254_max_count;
			i8254_lastcount = 0;
		}
		clkintr_pending = 0;
		mtx_unlock_spin(&clock_lock);
	}

	if (sc->et.et_active && sc->mode != MODE_STOP)
		sc->et.et_event_cb(&sc->et, sc->et.et_arg);

	return (FILTER_HANDLED);
}