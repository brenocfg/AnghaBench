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
 int /*<<< orphan*/  cpu_spinwait () ; 
 scalar_t__ rdtsc () ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 
 int tsc_freq ; 

__attribute__((used)) static void
delay_tsc(int n)
{
	uint64_t end, now;

	/*
	 * Pin the current thread ensure correct behavior if the TSCs
	 * on different CPUs are not in sync.
	 */
	sched_pin();
	now = rdtsc();
	end = now + tsc_freq * n / 1000000;
	do {
		cpu_spinwait();
		now = rdtsc();
	} while (now < end);
	sched_unpin();
}