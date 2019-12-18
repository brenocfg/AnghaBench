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
typedef  int u_int ;
typedef  enum scan_mode { ____Placeholder_scan_mode } scan_mode ;

/* Variables and functions */
 int CMCI ; 
 int POLLED ; 
 int cmc_throttle ; 
 int min (int,int) ; 
 int time_uptime ; 

__attribute__((used)) static int
update_threshold(enum scan_mode mode, int valid, int last_intr, int count,
    int cur_threshold, int max_threshold)
{
	u_int delta;
	int limit;

	delta = (u_int)(time_uptime - last_intr);
	limit = cur_threshold;

	/*
	 * If an interrupt was received less than cmc_throttle seconds
	 * since the previous interrupt and the count from the current
	 * event is greater than or equal to the current threshold,
	 * double the threshold up to the max.
	 */
	if (mode == CMCI && valid) {
		if (delta < cmc_throttle && count >= limit &&
		    limit < max_threshold) {
			limit = min(limit << 1, max_threshold);
		}
		return (limit);
	}

	/*
	 * When the banks are polled, check to see if the threshold
	 * should be lowered.
	 */
	if (mode != POLLED)
		return (limit);

	/* If a CMCI occured recently, do nothing for now. */
	if (delta < cmc_throttle)
		return (limit);

	/*
	 * Compute a new limit based on the average rate of events per
	 * cmc_throttle seconds since the last interrupt.
	 */
	if (valid) {
		limit = count * cmc_throttle / delta;
		if (limit <= 0)
			limit = 1;
		else if (limit > max_threshold)
			limit = max_threshold;
	} else {
		limit = 1;
	}
	return (limit);
}