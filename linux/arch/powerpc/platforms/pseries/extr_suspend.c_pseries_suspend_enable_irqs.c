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

/* Variables and functions */
 int /*<<< orphan*/  cacheinfo_cpu_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cacheinfo_cpu_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_mobility_fixup () ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void pseries_suspend_enable_irqs(void)
{
	/*
	 * Update configuration which can be modified based on device tree
	 * changes during resume.
	 */
	cacheinfo_cpu_offline(smp_processor_id());
	post_mobility_fixup();
	cacheinfo_cpu_online(smp_processor_id());
}