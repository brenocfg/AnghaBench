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
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  time; } ;

/* Variables and functions */
 scalar_t__ APERFMPERF_CACHE_THRESHOLD_MS ; 
 scalar_t__ APERFMPERF_STALE_THRESHOLD_MS ; 
 int /*<<< orphan*/  aperfmperf_snapshot_khz ; 
 scalar_t__ ktime_ms_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ samples ; 
 int /*<<< orphan*/  smp_call_function_single (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool aperfmperf_snapshot_cpu(int cpu, ktime_t now, bool wait)
{
	s64 time_delta = ktime_ms_delta(now, per_cpu(samples.time, cpu));

	/* Don't bother re-computing within the cache threshold time. */
	if (time_delta < APERFMPERF_CACHE_THRESHOLD_MS)
		return true;

	smp_call_function_single(cpu, aperfmperf_snapshot_khz, NULL, wait);

	/* Return false if the previous iteration was too long ago. */
	return time_delta <= APERFMPERF_STALE_THRESHOLD_MS;
}