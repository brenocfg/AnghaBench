#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;
struct clock_softc {TYPE_1__ et; } ;

/* Variables and functions */
 int DPCPU_GET (int) ; 
 int /*<<< orphan*/  DPCPU_SET (int,int) ; 
 int FILTER_HANDLED ; 
 int compare_ticks ; 
 int counter_lower_last ; 
 int counter_upper ; 
 int mips_rd_count () ; 
 int /*<<< orphan*/  mips_wr_compare (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
clock_intr(void *arg)
{
	struct clock_softc *sc = (struct clock_softc *)arg;
	uint32_t cycles_per_tick;
	uint32_t count, compare_last, compare_next, lost_ticks;

	cycles_per_tick = DPCPU_GET(cycles_per_tick);
	/*
	 * Set next clock edge.
	 */
	count = mips_rd_count();
	compare_last = DPCPU_GET(compare_ticks);
	if (cycles_per_tick > 0) {
		compare_next = count + cycles_per_tick;
		DPCPU_SET(compare_ticks, compare_next);
		mips_wr_compare(compare_next);
	} else	/* In one-shot mode timer should be stopped after the event. */
		mips_wr_compare(0xffffffff);

	/* COUNT register wrapped around */
	if (count < DPCPU_GET(counter_lower_last)) {
		DPCPU_SET(counter_upper, DPCPU_GET(counter_upper) + 1);
	}
	DPCPU_SET(counter_lower_last, count);

	if (cycles_per_tick > 0) {

		/*
		 * Account for the "lost time" between when the timer interrupt
		 * fired and when 'clock_intr' actually started executing.
		 */
		lost_ticks = DPCPU_GET(lost_ticks);
		lost_ticks += count - compare_last;
	
		/*
		 * If the COUNT and COMPARE registers are no longer in sync
		 * then make up some reasonable value for the 'lost_ticks'.
		 *
		 * This could happen, for e.g., after we resume normal
		 * operations after exiting the debugger.
		 */
		if (lost_ticks > 2 * cycles_per_tick)
			lost_ticks = cycles_per_tick;

		while (lost_ticks >= cycles_per_tick) {
			if (sc->et.et_active)
				sc->et.et_event_cb(&sc->et, sc->et.et_arg);
			lost_ticks -= cycles_per_tick;
		}
		DPCPU_SET(lost_ticks, lost_ticks);
	}
	if (sc->et.et_active)
		sc->et.et_event_cb(&sc->et, sc->et.et_arg);
	return (FILTER_HANDLED);
}