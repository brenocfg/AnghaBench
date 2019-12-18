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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static u64 check_and_compute_delta(u64 prev, u64 val)
{
	u64 delta = (val - prev) & 0xfffffffful;

	/*
	 * POWER7 can roll back counter values, if the new value is smaller
	 * than the previous value it will cause the delta and the counter to
	 * have bogus values unless we rolled a counter over.  If a coutner is
	 * rolled back, it will be smaller, but within 256, which is the maximum
	 * number of events to rollback at once.  If we detect a rollback
	 * return 0.  This can lead to a small lack of precision in the
	 * counters.
	 */
	if (prev > val && (prev - val) < 256)
		delta = 0;

	return delta;
}