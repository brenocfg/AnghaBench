#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct sp804_timer_softc {int et_enabled; } ;
struct eventtimer {scalar_t__ et_frequency; struct sp804_timer_softc* et_priv; } ;
typedef  int sbintime_t ;

/* Variables and functions */
 int DEFAULT_CONTROL_DIV ; 
 int EINVAL ; 
 int /*<<< orphan*/  SP804_TIMER2_CONTROL ; 
 int /*<<< orphan*/  SP804_TIMER2_LOAD ; 
 int TIMER_CONTROL_32BIT ; 
 int TIMER_CONTROL_EN ; 
 int TIMER_CONTROL_INTREN ; 
 int TIMER_CONTROL_PERIODIC ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sp804_timer_tc_write_4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sp804_timer_start(struct eventtimer *et, sbintime_t first, sbintime_t period)
{
	struct sp804_timer_softc *sc = et->et_priv;
	uint32_t count, reg;

	if (first != 0) {
		sc->et_enabled = 1;

		count = ((uint32_t)et->et_frequency * first) >> 32;

		sp804_timer_tc_write_4(SP804_TIMER2_LOAD, count);
		reg = TIMER_CONTROL_32BIT | TIMER_CONTROL_INTREN |
		    TIMER_CONTROL_PERIODIC | DEFAULT_CONTROL_DIV |
		    TIMER_CONTROL_EN;
		sp804_timer_tc_write_4(SP804_TIMER2_CONTROL, reg);

		return (0);
	} 

	if (period != 0) {
		panic("period");
	}

	return (EINVAL);
}