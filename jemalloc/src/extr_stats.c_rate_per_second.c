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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t
rate_per_second(uint64_t value, uint64_t uptime_ns) {
	uint64_t billion = 1000000000;
	if (uptime_ns == 0 || value == 0) {
		return 0;
	}
	if (uptime_ns < billion) {
		return value;
	} else {
		uint64_t uptime_s = uptime_ns / billion;
		return value / uptime_s;
	}
}