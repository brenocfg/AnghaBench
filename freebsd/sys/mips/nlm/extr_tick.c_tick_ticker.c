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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ DPCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_lower_last ; 
 int /*<<< orphan*/  counter_upper ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 scalar_t__ mips_rd_count () ; 

__attribute__((used)) static uint64_t
tick_ticker(void)
{
	uint64_t ret;
	uint32_t ticktock;
	uint32_t t_lower_last, t_upper;

	/*
	 * Disable preemption because we are working with cpu specific data.
	 */
	critical_enter();

	/*
	 * Note that even though preemption is disabled, interrupts are
	 * still enabled. In particular there is a race with clock_intr()
	 * reading the values of 'counter_upper' and 'counter_lower_last'.
	 *
	 * XXX this depends on clock_intr() being executed periodically
	 * so that 'counter_upper' and 'counter_lower_last' are not stale.
	 */
	do {
		t_upper = DPCPU_GET(counter_upper);
		t_lower_last = DPCPU_GET(counter_lower_last);
	} while (t_upper != DPCPU_GET(counter_upper));

	ticktock = mips_rd_count();

	critical_exit();

	/* COUNT register wrapped around */
	if (ticktock < t_lower_last)
		t_upper++;

	ret = ((uint64_t)t_upper << 32) | ticktock;
	return (ret);
}