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
typedef  int u_long ;
struct eventtimer {int dummy; } ;
typedef  int sbintime_t ;
typedef  int /*<<< orphan*/  register_t ;
struct TYPE_2__ {int et_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int rd_tick () ; 
 int roundup (int,int) ; 
 TYPE_1__ tick_et ; 
 int /*<<< orphan*/  tickadj ; 
 int /*<<< orphan*/  tickincrement ; 
 int /*<<< orphan*/  tickref ; 
 int /*<<< orphan*/  wr_tick_cmpr (int) ; 

__attribute__((used)) static int
tick_et_start(struct eventtimer *et, sbintime_t first, sbintime_t period)
{
	u_long base, div, fdiv;
	register_t s;

	if (period != 0)
		div = (tick_et.et_frequency * period) >> 32;
	else
		div = 0;
	if (first != 0)
		fdiv = (tick_et.et_frequency * first) >> 32;
	else
		fdiv = div;
	PCPU_SET(tickincrement, div);

	/*
	 * Try to make the (S)TICK interrupts as synchronously as possible
	 * on all CPUs to avoid inaccuracies for migrating processes.  Leave
	 * out one tick to make sure that it is not missed.
	 */
	s = intr_disable();
	base = rd_tick();
	if (div != 0) {
		PCPU_SET(tickadj, 0);
		base = roundup(base, div);
	}
	PCPU_SET(tickref, base);
	wr_tick_cmpr(base + fdiv);
	intr_restore(s);
	return (0);
}