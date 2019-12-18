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
 int /*<<< orphan*/  HK_FLAG_MISC ; 
 int /*<<< orphan*/  X86_FEATURE_APERFMPERF ; 
 int /*<<< orphan*/  aperfmperf_snapshot_cpu (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_khz ; 
 int /*<<< orphan*/  housekeeping_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 unsigned int per_cpu (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ samples ; 

unsigned int aperfmperf_get_khz(int cpu)
{
	if (!cpu_khz)
		return 0;

	if (!boot_cpu_has(X86_FEATURE_APERFMPERF))
		return 0;

	if (!housekeeping_cpu(cpu, HK_FLAG_MISC))
		return 0;

	aperfmperf_snapshot_cpu(cpu, ktime_get(), true);
	return per_cpu(samples.khz, cpu);
}