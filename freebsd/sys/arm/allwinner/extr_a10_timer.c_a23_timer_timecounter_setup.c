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
struct a10_timer_softc {int /*<<< orphan*/  timer0_freq; } ;
struct TYPE_3__ {int /*<<< orphan*/  tc_frequency; struct a10_timer_softc* tc_priv; } ;

/* Variables and functions */
 int TIMER_CTRL_AUTORELOAD ; 
 int TIMER_CTRL_CLKSRC_MASK ; 
 int TIMER_CTRL_MODE_MASK ; 
 int TIMER_CTRL_OSC24M ; 
 int TIMER_CTRL_PRESCALAR (int) ; 
 int TIMER_CTRL_PRESCALAR_MASK ; 
 int /*<<< orphan*/  TIMER_CTRL_REG (int /*<<< orphan*/ ) ; 
 int TIMER_CTRL_START ; 
 int /*<<< orphan*/  TIMER_CURV_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_INTV_REG (int /*<<< orphan*/ ) ; 
 TYPE_1__ a23_timer_timecounter ; 
 int /*<<< orphan*/  tc_init (TYPE_1__*) ; 
 int timer_read_4 (struct a10_timer_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_write_4 (struct a10_timer_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
a23_timer_timecounter_setup(struct a10_timer_softc *sc)
{
	uint32_t val;

	/* Set clock source to OSC24M, 1 pre-division, continuous mode */
	val = timer_read_4(sc, TIMER_CTRL_REG(0));
	val &= ~TIMER_CTRL_PRESCALAR_MASK | ~TIMER_CTRL_MODE_MASK | ~TIMER_CTRL_CLKSRC_MASK;
	val |= TIMER_CTRL_PRESCALAR(1) | TIMER_CTRL_OSC24M;
	timer_write_4(sc, TIMER_CTRL_REG(0), val);

	/* Set reload value */
	timer_write_4(sc, TIMER_INTV_REG(0), ~0);
	val = timer_read_4(sc, TIMER_INTV_REG(0));

	/* Enable timer0 */
	val = timer_read_4(sc, TIMER_CTRL_REG(0));
	val |= TIMER_CTRL_AUTORELOAD | TIMER_CTRL_START;
	timer_write_4(sc, TIMER_CTRL_REG(0), val);

	val = timer_read_4(sc, TIMER_CURV_REG(0));

	a23_timer_timecounter.tc_priv = sc;
	a23_timer_timecounter.tc_frequency = sc->timer0_freq;
	tc_init(&a23_timer_timecounter);
}