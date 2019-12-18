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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;
struct sp804_timer_softc {TYPE_1__ et; scalar_t__ et_enabled; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  SP804_TIMER1_VALUE ; 
 int /*<<< orphan*/  SP804_TIMER2_INTCLR ; 
 int /*<<< orphan*/  sp804_timer_tc_read_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp804_timer_tc_write_4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sp804_timer_intr(void *arg)
{
	struct sp804_timer_softc *sc = arg;
	static uint32_t prev = 0;
	uint32_t x = 0;

	x = sp804_timer_tc_read_4(SP804_TIMER1_VALUE);

	prev =x ;
	sp804_timer_tc_write_4(SP804_TIMER2_INTCLR, 1);
	if (sc->et_enabled) {
		if (sc->et.et_active) {
			sc->et.et_event_cb(&sc->et, sc->et.et_arg);
		}
	}

	return (FILTER_HANDLED);
}