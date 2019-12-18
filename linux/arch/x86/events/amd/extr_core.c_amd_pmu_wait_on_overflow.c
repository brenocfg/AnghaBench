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
typedef  unsigned long long u64 ;
struct TYPE_2__ {int cntval_bits; } ;

/* Variables and functions */
 unsigned int OVERFLOW_WAIT_COUNT ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 TYPE_1__ x86_pmu ; 
 int /*<<< orphan*/  x86_pmu_event_addr (int) ; 

__attribute__((used)) static void amd_pmu_wait_on_overflow(int idx)
{
	unsigned int i;
	u64 counter;

	/*
	 * Wait for the counter to be reset if it has overflowed. This loop
	 * should exit very, very quickly, but just in case, don't wait
	 * forever...
	 */
	for (i = 0; i < OVERFLOW_WAIT_COUNT; i++) {
		rdmsrl(x86_pmu_event_addr(idx), counter);
		if (counter & (1ULL << (x86_pmu.cntval_bits - 1)))
			break;

		/* Might be in IRQ context, so can't sleep */
		udelay(1);
	}
}