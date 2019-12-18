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
typedef  long u_long ;
struct trapframe {int dummy; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 long PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  adjust_edges ; 
 int /*<<< orphan*/  adjust_excess ; 
 int adjust_missed ; 
 int /*<<< orphan*/  adjust_ticks ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 long rd_tick () ; 
 int /*<<< orphan*/  tick_process (struct trapframe*) ; 
 int /*<<< orphan*/  tickadj ; 
 int /*<<< orphan*/  tickincrement ; 
 int /*<<< orphan*/  tickref ; 
 int /*<<< orphan*/  wr_tick_cmpr (long) ; 

__attribute__((used)) static void
tick_intr(struct trapframe *tf)
{
	u_long adj, ref, tick, tick_increment;
	long delta;
	register_t s;
	int count;

	tick_increment = PCPU_GET(tickincrement);
	if (tick_increment != 0) {
		/*
		 * NB: the sequence of reading the (S)TICK register,
		 * calculating the value of the next tick and writing it to
		 * the (S)TICK_COMPARE register must not be interrupted, not
		 * even by an IPI, otherwise a value that is in the past could
		 * be written in the worst case and thus causing the periodic
		 * timer to stop.
		 */
		s = intr_disable();
		adj = PCPU_GET(tickadj);
		tick = rd_tick();
		wr_tick_cmpr(tick + tick_increment - adj);
		intr_restore(s);
		ref = PCPU_GET(tickref);
		delta = tick - ref;
		count = 0;
		while (delta >= tick_increment) {
			tick_process(tf);
			delta -= tick_increment;
			ref += tick_increment;
			if (adj != 0)
				adjust_ticks++;
			count++;
		}
		if (count > 0) {
			adjust_missed += count - 1;
			if (delta > (tick_increment >> 3)) {
				if (adj == 0)
					adjust_edges++;
				adj = tick_increment >> 4;
			} else
				adj = 0;
		} else {
			adj = 0;
			adjust_excess++;
		}
		PCPU_SET(tickref, ref);
		PCPU_SET(tickadj, adj);
	} else
		tick_process(tf);
}