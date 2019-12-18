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
 int EBUSY ; 
 int /*<<< orphan*/  cpufreq_unregister_driver (int /*<<< orphan*/ ) ; 
 scalar_t__ hwp_active ; 
 int /*<<< orphan*/  intel_pstate_driver ; 
 int /*<<< orphan*/  intel_pstate_driver_cleanup () ; 

__attribute__((used)) static int intel_pstate_unregister_driver(void)
{
	if (hwp_active)
		return -EBUSY;

	cpufreq_unregister_driver(intel_pstate_driver);
	intel_pstate_driver_cleanup();

	return 0;
}