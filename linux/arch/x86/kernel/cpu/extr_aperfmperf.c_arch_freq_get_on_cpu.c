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
struct TYPE_2__ {int /*<<< orphan*/  khz; } ;

/* Variables and functions */
 int /*<<< orphan*/  APERFMPERF_REFRESH_DELAY_MS ; 
 int /*<<< orphan*/  HK_FLAG_MISC ; 
 int /*<<< orphan*/  X86_FEATURE_APERFMPERF ; 
 scalar_t__ aperfmperf_snapshot_cpu (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aperfmperf_snapshot_khz ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_khz ; 
 int /*<<< orphan*/  housekeeping_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 unsigned int per_cpu (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ samples ; 
 int /*<<< orphan*/  smp_call_function_single (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

unsigned int arch_freq_get_on_cpu(int cpu)
{
	if (!cpu_khz)
		return 0;

	if (!boot_cpu_has(X86_FEATURE_APERFMPERF))
		return 0;

	if (!housekeeping_cpu(cpu, HK_FLAG_MISC))
		return 0;

	if (aperfmperf_snapshot_cpu(cpu, ktime_get(), true))
		return per_cpu(samples.khz, cpu);

	msleep(APERFMPERF_REFRESH_DELAY_MS);
	smp_call_function_single(cpu, aperfmperf_snapshot_khz, NULL, 1);

	return per_cpu(samples.khz, cpu);
}