#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {TYPE_1__* config; } ;
struct TYPE_3__ {scalar_t__ soc_family; } ;

/* Variables and functions */
 int CPU_TIMER0_25MHZ_EN ; 
 int CPU_TIMER0_AUTO ; 
 int CPU_TIMER0_EN ; 
 int CPU_TIMER1_25MHZ_EN ; 
 int CPU_TIMER1_AUTO ; 
 int CPU_TIMER1_EN ; 
 int /*<<< orphan*/  INITIAL_TIMECOUNTER ; 
 scalar_t__ MV_SOC_ARMADA_XP ; 
 int mv_get_timer_control () ; 
 int /*<<< orphan*/  mv_set_timer (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_set_timer_control (int) ; 
 int /*<<< orphan*/  mv_set_timer_rel (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* timer_softc ; 
 int timers_initialized ; 

__attribute__((used)) static void
mv_setup_timers(void)
{
	uint32_t val;

	mv_set_timer_rel(1, INITIAL_TIMECOUNTER);
	mv_set_timer(1, INITIAL_TIMECOUNTER);
	val = mv_get_timer_control();
	val &= ~(CPU_TIMER0_EN | CPU_TIMER0_AUTO);
	val |= CPU_TIMER1_EN | CPU_TIMER1_AUTO;

	if (timer_softc->config->soc_family == MV_SOC_ARMADA_XP) {
		/* Enable 25MHz mode */
		val |= CPU_TIMER0_25MHZ_EN | CPU_TIMER1_25MHZ_EN;
	}

	mv_set_timer_control(val);
	timers_initialized = 1;
}