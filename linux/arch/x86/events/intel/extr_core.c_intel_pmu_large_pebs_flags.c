#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sample_regs_user; int /*<<< orphan*/  exclude_kernel; scalar_t__ use_clockid; } ;
struct perf_event {TYPE_1__ attr; } ;
struct TYPE_4__ {unsigned long large_pebs_flags; } ;

/* Variables and functions */
 int PEBS_GP_REGS ; 
 unsigned long PERF_SAMPLE_REGS_INTR ; 
 unsigned long PERF_SAMPLE_REGS_USER ; 
 unsigned long PERF_SAMPLE_TIME ; 
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static unsigned long intel_pmu_large_pebs_flags(struct perf_event *event)
{
	unsigned long flags = x86_pmu.large_pebs_flags;

	if (event->attr.use_clockid)
		flags &= ~PERF_SAMPLE_TIME;
	if (!event->attr.exclude_kernel)
		flags &= ~PERF_SAMPLE_REGS_USER;
	if (event->attr.sample_regs_user & ~PEBS_GP_REGS)
		flags &= ~(PERF_SAMPLE_REGS_USER | PERF_SAMPLE_REGS_INTR);
	return flags;
}