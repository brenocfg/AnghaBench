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
struct TYPE_2__ {scalar_t__ realmode_power_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_STATE_OFF ; 
 int /*<<< orphan*/  MRR_APM ; 
 TYPE_1__ apm_info ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  machine_real_restart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_system_power_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apm_power_off(void)
{
	/* Some bioses don't like being called from CPU != 0 */
	if (apm_info.realmode_power_off) {
		set_cpus_allowed_ptr(current, cpumask_of(0));
		machine_real_restart(MRR_APM);
	} else {
		(void)set_system_power_state(APM_STATE_OFF);
	}
}