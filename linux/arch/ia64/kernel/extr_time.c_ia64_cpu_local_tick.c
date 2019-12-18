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
struct TYPE_2__ {unsigned long itm_delta; scalar_t__ itm_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_TIMER_VECTOR ; 
 unsigned long ia64_fls (int) ; 
 scalar_t__ ia64_get_itc () ; 
 int /*<<< orphan*/  ia64_set_itm (scalar_t__) ; 
 int /*<<< orphan*/  ia64_set_itv (int /*<<< orphan*/ ) ; 
 TYPE_1__* local_cpu_data ; 
 int smp_processor_id () ; 

void
ia64_cpu_local_tick (void)
{
	int cpu = smp_processor_id();
	unsigned long shift = 0, delta;

	/* arrange for the cycle counter to generate a timer interrupt: */
	ia64_set_itv(IA64_TIMER_VECTOR);

	delta = local_cpu_data->itm_delta;
	/*
	 * Stagger the timer tick for each CPU so they don't occur all at (almost) the
	 * same time:
	 */
	if (cpu) {
		unsigned long hi = 1UL << ia64_fls(cpu);
		shift = (2*(cpu - hi) + 1) * delta/hi/2;
	}
	local_cpu_data->itm_next = ia64_get_itc() + delta + shift;
	ia64_set_itm(local_cpu_data->itm_next);
}