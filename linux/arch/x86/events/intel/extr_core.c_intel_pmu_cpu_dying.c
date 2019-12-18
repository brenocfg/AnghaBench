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
struct TYPE_2__ {scalar_t__ counter_freezing; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_counter_freeze () ; 
 int /*<<< orphan*/  fini_debug_store_on_cpu (int) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static void intel_pmu_cpu_dying(int cpu)
{
	fini_debug_store_on_cpu(cpu);

	if (x86_pmu.counter_freezing)
		disable_counter_freeze();
}