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
struct timecounter {struct sp804_timer_softc* tc_priv; } ;
struct sp804_timer_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SP804_TIMER1_VALUE ; 
 int sp804_timer_tc_read_4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
sp804_timer_tc_get_timecount(struct timecounter *tc)
{
	struct sp804_timer_softc *sc = tc->tc_priv;
	return 0xffffffff - sp804_timer_tc_read_4(SP804_TIMER1_VALUE);
}