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
typedef  int /*<<< orphan*/  uint32_t ;
struct sp804_timer_softc {scalar_t__ et_enabled; } ;
struct eventtimer {struct sp804_timer_softc* et_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SP804_TIMER2_CONTROL ; 
 int /*<<< orphan*/  TIMER_CONTROL_EN ; 
 int /*<<< orphan*/  sp804_timer_tc_read_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp804_timer_tc_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sp804_timer_stop(struct eventtimer *et)
{
	struct sp804_timer_softc *sc = et->et_priv;
	uint32_t reg;

	sc->et_enabled = 0;
	reg = sp804_timer_tc_read_4(SP804_TIMER2_CONTROL);
	reg &= ~(TIMER_CONTROL_EN);
	sp804_timer_tc_write_4(SP804_TIMER2_CONTROL, reg);

	return (0);
}