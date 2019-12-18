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
struct TYPE_2__ {int /*<<< orphan*/  microcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  __reload_late ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  late_cpus_in ; 
 int /*<<< orphan*/  late_cpus_out ; 
 int /*<<< orphan*/  microcode_check () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int stop_machine_cpuslocked (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int microcode_reload_late(void)
{
	int ret;

	atomic_set(&late_cpus_in,  0);
	atomic_set(&late_cpus_out, 0);

	ret = stop_machine_cpuslocked(__reload_late, NULL, cpu_online_mask);
	if (ret > 0)
		microcode_check();

	pr_info("Reload completed, microcode revision: 0x%x\n", boot_cpu_data.microcode);

	return ret;
}