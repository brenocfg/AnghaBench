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
struct rt1310_timer_softc {int lt_period; TYPE_1__ lt_et; int /*<<< orphan*/  lt_oneshot; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  RT_TIMER_CONTROL ; 
 int RT_TIMER_CTRL_ENABLE ; 
 int RT_TIMER_CTRL_INTCTL ; 
 int /*<<< orphan*/  RT_TIMER_LOAD ; 
 int /*<<< orphan*/  RT_TIMER_VALUE ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int timer2_read_4 (struct rt1310_timer_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer2_write_4 (struct rt1310_timer_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
rt1310_hardclock(void *arg)
{
	struct rt1310_timer_softc *sc = (struct rt1310_timer_softc *)arg;

	/* Reset pending interrupt */
	timer2_write_4(sc, RT_TIMER_CONTROL, 
	    timer2_read_4(sc, RT_TIMER_CONTROL) | 0x08);
	timer2_write_4(sc, RT_TIMER_CONTROL, 
	    timer2_read_4(sc, RT_TIMER_CONTROL) & 0x1fb);

	/* Start timer again */
	if (!sc->lt_oneshot) {
		timer2_write_4(sc, RT_TIMER_LOAD, sc->lt_period);
		timer2_write_4(sc, RT_TIMER_VALUE, sc->lt_period);
		timer2_write_4(sc, RT_TIMER_CONTROL,
			RT_TIMER_CTRL_ENABLE | RT_TIMER_CTRL_INTCTL);
	}

	if (sc->lt_et.et_active)
		sc->lt_et.et_event_cb(&sc->lt_et, sc->lt_et.et_arg);

	return (FILTER_HANDLED);
}