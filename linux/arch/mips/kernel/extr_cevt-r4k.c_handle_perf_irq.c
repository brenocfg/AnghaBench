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

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ cp0_perfcount_irq ; 
 scalar_t__ perf_irq () ; 

__attribute__((used)) static inline int handle_perf_irq(int r2)
{
	/*
	 * The performance counter overflow interrupt may be shared with the
	 * timer interrupt (cp0_perfcount_irq < 0). If it is and a
	 * performance counter has overflowed (perf_irq() == IRQ_HANDLED)
	 * and we can't reliably determine if a counter interrupt has also
	 * happened (!r2) then don't check for a timer interrupt.
	 */
	return (cp0_perfcount_irq < 0) &&
		perf_irq() == IRQ_HANDLED &&
		!r2;
}